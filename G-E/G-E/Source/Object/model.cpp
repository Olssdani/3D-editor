#include "model.h"
#include <shader.h>
#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>




model::model(std::string const& path, bool gamma)
	: gammaCorrection(gamma) {
	texturesLoaded = new textureHolder();
	loadModel(path);

}

model::~model() {
	delete texturesLoaded;
}

void model::Draw(Shader *shader) {
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].Draw(shader);
}


void model::loadModel(std::string const& path) {

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
	// process ASSIMP's root node recursively
	this->processNode(scene->mRootNode, scene);
}

// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
void model::processNode(aiNode* node, const aiScene* scene) {
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh model::processMesh(aiMesh* mesh, const aiScene* scene) {
	// data to fill
	std::vector<vertex> vertices;
	std::vector<unsigned int> indices;
	textureHolder textures;

	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		vertex vert;

		vert.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vert.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

		// texture coordinates
		if (mesh->mTextureCoords[0]) {
			vert.TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		else {
			vert.TexCoords = glm::vec2(0.0f, 0.0f);
		}

		vert.Tangent = glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
		vert.Bitangent = glm::vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);

		vertices.push_back(vert);
	}
	// Faces
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	// 1. diffuse maps
	textures.loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", directory, texturesLoaded);
	// 2. specular maps
	textures.loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", directory, texturesLoaded);
	// 3. normal maps
	textures.loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal", directory, texturesLoaded);
	// 4. height maps
	textures.loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height", directory, texturesLoaded);

	// return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures);
}
