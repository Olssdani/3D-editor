#pragma once
#include "Render/Shader.h"
#include "GUI/gui.h"

class Light : public gui {
public:
	static int counter;
	virtual void send2Gpu(const Shader* shader, const unsigned int nr = 0) const = 0;
	virtual void guiRender() = 0;
	Light() {
		ID = ++counter;
		lightColor = glm::vec3(1.0f);
	}

	void setAmbient(glm::vec3 a) {
		ambient = a;
	}

	void setDiffuse(glm::vec3 d) {
		diffuse = d;
	}

	void setSpecular(glm::vec3 s) {
		specular = s;
	}

	void setName(std::string _name) {
		name = _name;
	}

	std::string getName() {
		return name;
	}
	int getID() {
		return ID;
	}

	glm::vec3 getDiffuse() {
		return diffuse;
	}

	glm::vec3 getAmbient() {
		return ambient;
	}

	glm::vec3 getSpecular() {
		return specular;
	}

protected:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 lightColor;
	float ambientIntensity;
	float diffuseIntensity;
	float specularIntensity;
	std::string name;
	int ID;
};
