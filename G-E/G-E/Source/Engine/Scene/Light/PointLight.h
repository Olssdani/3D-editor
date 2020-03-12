#pragma once
#include "light.h"

class box;

class pointLight : public light {
private:
	float constant;
	float linear;
	float quadratic;
	glm::vec3 position;
	box* b;

public:
	pointLight(glm::vec3 position = glm::vec3(0, 0, 0),
			   float constant = 1.0f,
			   float linear = 0.09f,
			   float quadratic = 0.032f);

	box* getBox();
	void send2Gpu(const shader* shader, const unsigned int nr) const override;
	void setConstant(float constant);
	void setLinear(float linear);
	void setQuadratic(float quadratic);
	float getConstant();
	float getLinear();
	float getQuadratic();
	void guiRender();
	void renderVisualization(const glm::mat4& projection,
							 const glm::mat4& view,
							 const glm::vec3& cameraPosition);
};
