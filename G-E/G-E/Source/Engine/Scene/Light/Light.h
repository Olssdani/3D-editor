#pragma once
#include "Render/shader.h"
#include "GUI/gui.h"

class light : public gui {
public:
	virtual void send2Gpu(const shader* shader, const unsigned int nr = 0) const = 0;
	virtual void guiRender() = 0;

	light();
	void setAmbient(glm::vec3 a);
	void setDiffuse(glm::vec3 d);
	void setSpecular(glm::vec3 s);
	void setName(std::string name);
	std::string getName();
	int getID();
	glm::vec3 getDiffuse();
	glm::vec3 getAmbient();
	glm::vec3 getSpecular();

protected:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 lightColor;
	float ambientIntensity;
	float diffuseIntensity;
	float specularIntensity;
	std::string name;
	int id;
	static int counter;
};
