#include "Material.h"
#include "imgui.h"
#include "Misc/WindowsUtil.h"
#include "Texture/texture.h"
#include "Render/shader.h"

material::material(shader* shader) {
	this->shaderObject = shader;
	color[0] = color[1] = color[2] = 1.0f;
	ambient = glm::vec3(1.0f);
	diffuse = glm::vec3(1.0f);
	specular = glm::vec3(1.0f);
	shininess = 32;
	textureEnable = false;
}

material::material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) {
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
	this->textureEnable = false;
}

material::material(glm::vec3 color, float shininess) {
	this->ambient = color;
	this->diffuse = color;
	this->specular = color;
	this->color[0] = color.x;
	this->color[1] = color.y;
	this->color[2] = color.z;
	this->shininess = shininess;
	this->textureEnable = false;
}

void material::setColor(glm::vec3 color) {
	this->ambient = color;
	this->diffuse = color;
	this->specular = color;
	this->color[0] = color.x;
	this->color[1] = color.y;
	this->color[2] = color.z;
}

void material::setColor(float color[]) {
	glm::vec3 temp = {color[0], color[1], color[2]};
	this->ambient = temp;
	this->diffuse = temp;
	this->specular = temp;
	this->color[0] = color[0];
	this->color[1] = color[1];
	this->color[2] = color[2];
}

void material::setAmbient(glm::vec3 ambient) {
	this->ambient = ambient;
}

void material::setAmbient(float ambient[]) {
	this->ambient.x = ambient[0];
	this->ambient.y = ambient[1];
	this->ambient.z = ambient[2];
}

void material::setDiffuse(glm::vec3 diffuse) {
	this->diffuse = diffuse;
}
void material::setSpecular(glm::vec3 specular) {
	this->specular = specular;
}

void material::setShininess(float shininess) {
	this->shininess = shininess;
}

glm::vec3 material::getAmbient() {
	return this->ambient;
}

glm::vec3 material::getDiffuse() {
	return this->diffuse;
}
glm::vec3 material::getSpecular() {
	return this->specular;
}

float material::getShininess() {
	return this->shininess;
}

bool material::isTextureSet() {
	return textureEnable;
}

void material::setTexture(const char* url) {
	textureObject = new texture(url, "texture_diffuse");
	textureEnable = true;
	glDeleteProgram(shaderObject->ID);
	shaderObject = new shader("Shaders/Vert.glsl", "Shaders/textureFrag.fs", "Shaders/Geo.glsl");
	shaderObject->setInt("material.diffuse", 0);
}

void material::deleteTexture() {
	textureEnable = false;
	glDeleteProgram(shaderObject->ID);
	shaderObject = new shader("Shaders/Vert.glsl", "Shaders/Frag.glsl", "Shaders/Geo.glsl");
}

void material::send2GPU(shader* shaderIn) {
	if(textureEnable) {
		glBindTexture(GL_TEXTURE_2D, textureObject->getId());
		shaderIn->setFloat("material.shininess", this->shininess);
	} else {
		shaderIn->setVec3("material.ambient", this->ambient);
		shaderIn->setVec3("material.diffuse", this->diffuse);
		shaderIn->setVec3("material.specular", this->specular);
		shaderIn->setFloat("material.shininess", this->shininess);
	}
}

void material::renderGui() {
	ImGui::Text("Color");
	ImGui::SameLine();
	ImGui::ColorEdit3("", color);
	for(int i = 0; i < 3; ++i) {
		ambient[i] = color[i];
		diffuse[i] = color[i];
		specular[i] = color[i];
	}
	ImGui::Text("Shininess:");
	ImGui::SameLine();
	ImGui::DragFloat("", &shininess, 0.01f, 0.00f, 100.0f);

	if(textureEnable) {
		ImGui::Text("Texture is set");
		ImGui::SameLine();
		if(ImGui::Button("Delete Texture")) {
			deleteTexture();
		}
	} else {
		if(ImGui::Button("Add Texture")) {
			std::string fileName = wUtil::openFileExplorer();
			if(!fileName.compare(""))
				setTexture(fileName.c_str());
		}
	}
}
