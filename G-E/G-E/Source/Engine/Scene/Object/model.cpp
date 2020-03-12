#include <glad/glad.h>
#include "model.h"
#include <Render/shader.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <Object/Mesh.h>
#include "Material/material.h"

model::model(std::string const& path, bool gamma)
	: gammaCorrection(gamma) {
	texturesLoaded = new textureHolder();
	shaderObject = new shader("Shaders/Vert.glsl", "Shaders/textureFrag.fs", "Shaders/Geo.glsl");
	loadModel(path);
}

model::~model() {
	delete texturesLoaded;
}

void model::Draw(shader* shaderIn) {
	for(unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].Draw(shaderIn);
}

void model::loadModel(std::string const& path) {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(
		path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));
	this->processNode(scene->mRootNode, scene);
}

void model::processNode(aiNode* node, const aiScene* scene) {
	for(unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	for(unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

mesh model::processMesh(aiMesh* aimesh, const aiScene* scene) {
	std::vector<vertex> vertices;
	std::vector<unsigned int> indices;
	textureHolder textures;

	// Walk through each of the mesh's vertices
	for(unsigned int i = 0; i < aimesh->mNumVertices; i++) {
		vertex vert;

		vert.Position =
			glm::vec3(aimesh->mVertices[i].x, aimesh->mVertices[i].y, aimesh->mVertices[i].z);
		vert.Normal =
			glm::vec3(aimesh->mNormals[i].x, aimesh->mNormals[i].y, aimesh->mNormals[i].z);

		if(aimesh->mTextureCoords[0]) {
			vert.TexCoords =
				glm::vec2(aimesh->mTextureCoords[0][i].x, aimesh->mTextureCoords[0][i].y);
		} else {
			vert.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		if(aimesh->mTangents != nullptr)
			vert.Tangent =
				glm::vec3(aimesh->mTangents[i].x, aimesh->mTangents[i].y, aimesh->mTangents[i].z);
		if(aimesh->mBitangents != nullptr)
			vert.Bitangent = glm::vec3(
				aimesh->mBitangents[i].x, aimesh->mBitangents[i].y, aimesh->mBitangents[i].z);

		vertices.push_back(vert);
	}

	for(unsigned int i = 0; i < aimesh->mNumFaces; i++) {
		aiFace face = aimesh->mFaces[i];
		for(unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	aiMaterial* material = scene->mMaterials[aimesh->mMaterialIndex];

	// 1. diffuse maps
	textures.loadMaterialTextures(
		material, aiTextureType_DIFFUSE, "texture_diffuse", directory, texturesLoaded);
	// 2. specular maps
	textures.loadMaterialTextures(
		material, aiTextureType_SPECULAR, "texture_specular", directory, texturesLoaded);
	// 3. normal maps
	textures.loadMaterialTextures(
		material, aiTextureType_HEIGHT, "texture_normal", directory, texturesLoaded);
	// 4. height maps
	textures.loadMaterialTextures(
		material, aiTextureType_AMBIENT, "texture_height", directory, texturesLoaded);

	return mesh(vertices, indices, textures);
}
