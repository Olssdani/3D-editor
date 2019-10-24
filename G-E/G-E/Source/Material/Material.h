#pragma once
#include "glm/glm.hpp"
#include "shader.h"

class Material {

private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
	glm::vec3 Color;

public:
	Material() {
		ambient = glm::vec3();
		diffuse = glm::vec3();
		specular = glm::vec3();
		shininess = 0;
	}

	Material(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _shininess) {
		this->ambient = _ambient;
		this->diffuse = _diffuse;
		this->specular = _specular;
		this->shininess = _shininess;
	}
	Material(glm::vec3 _color, float _shininess) {
		this->ambient = _color;
		this->diffuse = _color;
		this->specular = _color;
		this->Color = _color;
		this->shininess = _shininess;
	}
	glm::vec3 getColor() {
		return Color;
	}

	void setColor(glm::vec3 _color) {
		this->Color = _color;
		this->ambient = _color;
		this->diffuse = _color;
		this->specular = _color;
	}
	void setColor(float _color[]) {
		glm::vec3 temp;
		temp.x = _color[0];
		temp.y = _color[1];
		temp.z = _color[2];
		this->Color = temp;
		this->ambient = temp;
		this->diffuse = temp;
		this->specular = temp;
	}

	void setAmbient(glm::vec3 _ambient) {
		this->ambient = _ambient;
	}
	void setAmbient(float _ambient []) {
		this->ambient.x = _ambient[0];
		this->ambient.y = _ambient[1];
		this->ambient.z = _ambient[2];
	}

	void setDiffuse(glm::vec3 _diffuse) {
		this->diffuse = _diffuse;
	}
	void setSpecular(glm::vec3 _specular) {
		this->specular = _specular;
	}

	void setShininess(float _shininess) {
		this->shininess = _shininess;
	}

	//Get functions
	glm::vec3 getAmbient() {
		return this->ambient;
	}

	glm::vec3 getDiffuse() {
		return this->diffuse;
	}
	glm::vec3 getSpecular() {
		return this->specular;
	}

	float getShininess() {
		return this->shininess;
	}

	void send2GPU(Shader *shader) {
		shader->setVec3("material.ambient", this->ambient);
		shader->setVec3("material.diffuse", this->diffuse);
		shader->setVec3("material.specular", this->specular);
		shader->setFloat("material.shininess", this->shininess);
	}
};
