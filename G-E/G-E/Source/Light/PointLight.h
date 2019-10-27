#pragma once
#include "Light.h"


class Box;

class PointLight: public Light
{
private:
	float Constant;
	float Linear;
	float Quadratic;
	glm::vec3 Position;
	Box *box;

public:

	glm::vec3 getDiffuse();
	PointLight(glm::vec3 _Position, float _Constant = 1.0f, float _Linear = 0.09f, float _Quadratic = 0.032f);

	Box* getBox();

	void Send2GPU(Shader *shader, unsigned int nr) override;
};