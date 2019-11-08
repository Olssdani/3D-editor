#pragma once
#ifndef Utilities_H
#define Utilities_H
#include "Utilities.h"
#endif
#include "Shader.h"

class Light
{
public:
	static int counter;
	Light(){
		ID = ++counter;
	}
	virtual void Send2GPU(Shader *shader,unsigned int nr =0) =0;

	void SetAmbient(glm::vec3 A)
	{
		Ambient = A;
	}
	void SetDiffuse(glm::vec3 D)
	{
		Diffuse = D;
	}
	void SetSpecular(glm::vec3 S)
	{
		Specular = S;
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
		return Diffuse;
	}
	glm::vec3 getAmbient() {
		return Ambient;
	}
	glm::vec3 getSpecular() {
		return Specular;
	}

protected:
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	std::string name;
	int ID;
	


};

