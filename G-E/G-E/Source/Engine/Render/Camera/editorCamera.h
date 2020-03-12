#pragma once

#include "Camera/camera.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class input;

class editorCamera : public camera {
private:
	float movementSpeed = 0.01f;
	glm::vec3 lookPosition;
	glm::fquat rotationX, rotationY;
	glm::vec3 startPosition;
	float scrollOffset;
	glm::vec3 positionOffset;

public:
	editorCamera(const glm::vec3 position);
	void moveCamera(const double xpos, const double ypos);
	void rotateCamera(const double xpos, const double ypos);
	void rotatelookPosition(const double xpos, const double ypos);
	void processInput(const input* inputObject, const float xoffset, const float yoffset);
	void processMouseScroll(float yoffset);

private:
	void update();
	glm::fquat rotationBetweenVectors(glm::vec3 start, glm::vec3 dest);
};
