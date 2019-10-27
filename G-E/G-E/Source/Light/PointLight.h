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
	PointLight(glm::vec3 _Position, float _Constant = 1.0f, float _Linear = 0.09f, float _Quadratic = 0.032f);

	Box* getBox();

	void Send2GPU(Shader *shader, unsigned int nr) override;

	void setConstant(float _constant);
	void setLinear(float _linear);
	void setQuadratic(float _quadratic);
	float getConstant();
	float getLinear();
	float getQuadratic();
};