#pragma once
#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtx/quaternion.hpp>
class transformationObject {
public:
	transformationObject() {

	}


	void rotate(float angleX, float angleY, float angleZ) {

	}

	void translate() {

	}

	glm::vec3 getPosition() {
		return glm::vec3(position);
	}


private:
	glm::vec4 position;u
	glm::fquat rotationX, rotationY;
	float offset;
	glm::vec3 direction;
};
