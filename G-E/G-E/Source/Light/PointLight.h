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
	PointLight(glm::vec3 _Position, float _Constant, float _Linear, float _Quadratic);

	Box* getBox();

	void Send2GPU(Shader *shader, unsigned int nr) override;
};