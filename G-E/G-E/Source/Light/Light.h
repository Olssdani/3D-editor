#pragma once
#include "Utilities.h"
#include "Shader.h"

class Light
{
public:
	Light()
	{

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


protected:
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	

};

