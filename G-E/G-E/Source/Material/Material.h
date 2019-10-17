#pragma once
#include "glm/glm.hpp"
#include "shader.h"

class Material {

private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

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
		this->shininess = -shininess;
	}

	void setAmbient(glm::vec3 _ambient) {
		this->ambient = _ambient;
	}

	void setDiffuse(glm::vec3 _diffuse) {
		this->diffuse = _diffuse;
	}
	void setSpecular(glm::vec3 _specular) {
		this->specular = _specular;
	}

	void setShininess(glm::vec3 _ambient) {
		this->ambient = _ambient;
	}

	void send2GPU(Shader *shader) {
		shader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
		shader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
		shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		shader->setFloat("material.shininess", 32.0f);
	}



};
