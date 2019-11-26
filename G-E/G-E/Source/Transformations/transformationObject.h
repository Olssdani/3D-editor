#pragma once
#include "glm/glm.hpp"
#include <cmath>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtx/quaternion.hpp>
class transformationObject {
public:
	transformationObject() {
		position = glm::vec4(0.0f);
		rotationX = glm::fquat(1.0f, 0, 0, 0);
		rotationY = glm::fquat(1.0f, 0, 0, 0);
		glm::vec3 direction = glm::vec3(0.0f);
	}
	//TODO Implement setup for initial position
	transformationObject(glm::vec3 startPosition) {
		position2Components(startPosition);
	}


	void rotate(float angleX, float angleY) {
		
		glm::vec3 angle = glm::vec3(angleX, 0, 0);
		rotationX = rotationX * glm::fquat(angle);

		angle = glm::vec3(0, angleY, 0);
		rotationY = rotationY * glm::fquat(angle);
	}

	void translate() {

	}

	glm::vec3 getPosition() {
		return glm::vec3(position);
	}

	

private:
	glm::vec4 position;
	glm::fquat rotationX, rotationY;
	float offset;
	glm::vec3 direction;


	void update() {

	}

	//Allocate the correct value for all components from a startposition.
	void position2Components(glm::vec3 startPosition) {
		offset = glm::length(startPosition);
		direction = glm::normalize(startPosition);
		float theta = atan(startPosition.y / startPosition.x);
		float phi = acos(startPosition.z / startPosition.r);
		
		glm::vec3 angle = glm::vec3(theta, 0, 0);
		rotationX = rotationX * glm::fquat(angle);

		angle = glm::vec3(0, phi, 0);
		rotationY = rotationY * glm::fquat(angle);
		
	}
};
