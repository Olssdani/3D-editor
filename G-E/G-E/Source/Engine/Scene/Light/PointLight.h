#pragma once
#include "Light.h"
class Box;

class PointLight : public Light {
private:
	float constant;
	float linear;
	float quadratic;
	glm::vec3 position;
	Box* box;

public:
	PointLight(glm::vec3 _position = glm::vec3(0, 0, 0),
			   float _constant = 1.0f,
			   float _linear = 0.09f,
			   float _quadratic = 0.032f);

	Box* getBox();
	void send2Gpu(const Shader* shader, const unsigned int nr) const override;
	void setConstant(float _constant);
	void setLinear(float _linear);
	void setQuadratic(float _quadratic);
	float getConstant();
	float getLinear();
	float getQuadratic();
	void renderGui();
	void renderVisualization(const glm::mat4& projection,
							 const glm::mat4& view,
							 const glm::vec3& cameraPosition);
};
