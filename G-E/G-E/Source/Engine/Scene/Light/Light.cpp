#include "Light.h"

int light::counter = 0;

light::light() {
	this->id = ++counter;
	this->lightColor = glm::vec3(1.0f);
}

void light::setAmbient(glm::vec3 a) {
	this->ambient = a;
}

void light::setDiffuse(glm::vec3 d) {
	this->diffuse = d;
}

void light::setSpecular(glm::vec3 s) {
	this->specular = s;
}

void light::setName(std::string name) {
	this->name = name;
}

std::string light::getName() {
	return name;
}
int light::getID() {
	return id;
}

glm::vec3 light::getDiffuse() {
	return diffuse;
}

glm::vec3 light::getAmbient() {
	return ambient;
}

glm::vec3 light::getSpecular() {
	return specular;
}
