#pragma once
#include "Camera/Camera.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtx/quaternion.hpp>
class Editor_Camera: public Camera {
private: 
	float movementSpeed = 0.01f;
	glm::vec3 lookPosition;

public:
	Editor_Camera(glm::vec3 _position) {
		position = _position;
		lookPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		//Forward is toward origo
		forward = lookPosition - position;
		worldUp = glm::vec3(0.0f, 1.0f, 0.0f); 
		up = glm::vec3(0.0f, 1.0f, 0.0f);
		right = glm::vec3(1.0f, 0.0f, 0.0f);
		fov = 45.0f;
		worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
		
	}

	void moveCamera(const double xpos, const double ypos) {
		position = position - movementSpeed * (float)xpos * right;
		position = position - movementSpeed * (float)ypos * up;
		
		lookPosition = lookPosition - movementSpeed * (float)xpos * right;
		lookPosition = lookPosition - movementSpeed * (float)ypos * up;
	}


	void rotateCamera(const double xpos, const double ypos) {
		glm::fquat rotation;
		float angleX = ypos * 0.005;
		float angleY = xpos * 0.005;
		glm::vec3 angle = glm::vec3(angleX, angleY, 0);
		rotation = glm::fquat(angle);

		position = rotation * position * glm::conjugate(rotation);

		//Update variabels.
		update();
	}
	
	void ProcessMouseScroll(float yoffset){
		position = position + yoffset * 0.05f * forward;

	}

private:
	void update() {
		forward = lookPosition - position;
		right = glm::normalize(glm::cross(up, forward));
		up = glm::normalize(glm::cross(forward, right));	
	}



};

		/*std::cout << " Start" << std::endl;
		std::cout  << "Right: " << right.x << " " << right.y << " " << right.z << std::endl;
		std::cout << "Up: " << up.x << " " << up.y << " " << up.z << std::endl << std::endl;*/