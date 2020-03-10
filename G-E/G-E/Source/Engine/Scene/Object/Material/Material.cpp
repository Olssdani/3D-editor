#include "Material.h"
#include "Misc/WindowsUtil.h"
#include "imgui.h"
#include "Scene/Object/Material/Texture/texture.h"

Material::Material(Shader *_shader) {
	shader = _shader;
	color[0] = color[1] = color[2] = 1.0f;
	ambient = glm::vec3(1.0f);
	diffuse = glm::vec3(1.0f);
	specular = glm::vec3(1.0f);
	shininess = 32;
	textureEnable = false;
}

Material::Material(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _shininess) {
	this->ambient = _ambient;
	this->diffuse = _diffuse;
	this->specular = _specular;
	this->shininess = _shininess;
	this->textureEnable = false;
}

Material::Material(glm::vec3 _color, float _shininess) {
	this->ambient = _color;
	this->diffuse = _color;
	this->specular = _color;
	this->color[0] = _color.x;
	this->color[1] = _color.y;
	this->color[2] = _color.z;
	this->shininess = _shininess;
	this->textureEnable = false;
}

void Material::setColor(glm::vec3 _color) {
	this->ambient = _color;
	this->diffuse = _color;
	this->specular = _color;
	this->color[0] = _color.x;
	this->color[1] = _color.y;
	this->color[2] = _color.z;
}

void Material::setColor(float _color[]) {
	glm::vec3 temp = { _color[0],_color[1],_color[2] };
	this->ambient = temp;
	this->diffuse = temp;
	this->specular = temp;
	this->color[0] = _color[0];
	this->color[1] = _color[1];
	this->color[2] = _color[2];
}

void Material::setAmbient(glm::vec3 _ambient) {
	this->ambient = _ambient;
}

void Material::setAmbient(float _ambient[]) {
	this->ambient.x = _ambient[0];
	this->ambient.y = _ambient[1];
	this->ambient.z = _ambient[2];
}

void Material::setDiffuse(glm::vec3 _diffuse) {
	this->diffuse = _diffuse;
}
void Material::setSpecular(glm::vec3 _specular) {
	this->specular = _specular;
}

void Material::setShininess(float _shininess) {
	this->shininess = _shininess;
}

glm::vec3 Material::getAmbient() {
	return this->ambient;
}

glm::vec3 Material::getDiffuse() {
	return this->diffuse;
}
glm::vec3 Material::getSpecular() {
	return this->specular;
}

float Material::getShininess() {
	return this->shininess;
}

bool Material::isTextureSet() {
	return textureEnable;
}

void Material::setTexture(const char* url) {
	textureObject = new texture(url, "texture_diffuse");
	textureEnable = true;
	glDeleteProgram(shader->ID);
	shader = new Shader("Shaders/Vert.glsl", "Shaders/textureFrag.fs", "Shaders/Geo.glsl");
	shader->setInt("material.diffuse", 0);
}

void Material::deleteTexture() {
	textureEnable = false;
	glDeleteProgram(shader->ID);
	shader = new Shader("Shaders/Vert.glsl", "Shaders/Frag.glsl", "Shaders/Geo.glsl");
}



void Material::send2GPU(Shader *shader) {
	if (textureEnable) {
		glBindTexture(GL_TEXTURE_2D, textureObject->getId());
		shader->setFloat("material.shininess", this->shininess);
	}else {
		shader->setVec3("material.ambient", this->ambient);
		shader->setVec3("material.diffuse", this->diffuse);
		shader->setVec3("material.specular", this->specular);
		shader->setFloat("material.shininess", this->shininess);
	}
}

void Material::renderGui() {
	ImGui::Text("Color");
	ImGui::SameLine();
	ImGui::ColorEdit3("", color);
	for (int i = 0; i < 3; ++i) {
		ambient[i] = color[i];
		diffuse[i] = color[i];
		specular[i] = color[i];
	}
	ImGui::Text("Shininess:");
	ImGui::SameLine();
	ImGui::DragFloat("", &shininess, 0.01f, 0.00f, 100.0f);

	if (textureEnable){
		ImGui::Text("Texture is set");
		ImGui::SameLine();
		if (ImGui::Button("Delete Texture")){
			deleteTexture();
		}
	} else {
		if (ImGui::Button("Add Texture")){
			std::string fileName = wUtil::openFileExplorer();
			if(!fileName.compare(""))
				setTexture(fileName.c_str());
		}
	}
}