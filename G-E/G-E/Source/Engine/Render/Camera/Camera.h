#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class camera {
protected:
	camera() {}

	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 worldUp;
	glm::vec3 right;
	glm::mat4 view;
	float fov = 0;

public:
	glm::mat4 getView() {
		return glm::lookAt(position, position + forward, up);
	}

	glm::vec3 getPosition() {
		return position;
	}

	float getFov() {
		return fov;
	}

	virtual void processMouseScroll(float yoffset) = 0;
};
