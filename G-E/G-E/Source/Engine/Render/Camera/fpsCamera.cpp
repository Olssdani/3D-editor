#include "fpsCamera.h"
#include "Input/Input.h"
fpsCamera::fpsCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
					 glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
					 float yaw = -90.f,
					 float _pitch = 0.0f) {
	this->position = position;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->fov = 45.0f;
	update();
}

fpsCamera::fpsCamera(glm::vec3 position) {
	this->position = position;
	this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->yaw = -90.f;
	this->pitch = 0.0f;
	this->fov = 45.0f;
	update();
}

float fpsCamera::zoom() {
	return zoomValue;
}

void fpsCamera::update() {
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = glm::normalize(front);

	// Also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(
		forward,
		worldUp)); // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, forward));
}

void fpsCamera::processKeyboard(input* inputObject, float deltaTime) {
	float velocity = movementSpeed * deltaTime;

	if(inputObject->getKeyStatus(KEY_W))
		position += forward * velocity;
	if(inputObject->getKeyStatus(KEY_S))
		position -= forward * velocity;
	if(inputObject->getKeyStatus(KEY_D))
		position += right * velocity;
	if(inputObject->getKeyStatus(KEY_A))
		position -= right * velocity;
}

void fpsCamera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) {
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;
	yaw -= xoffset;
	pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if(constrainPitch) {
		if(pitch > 89.0f)
			pitch = 89.0f;
		if(pitch < -89.0f)
			pitch = -89.0f;
	}

	update();
}

void fpsCamera::processMouseScroll(float yoffset) {
	if(zoomValue >= 1.0f && zoomValue <= 45.0f)
		zoomValue -= yoffset;
	if(zoomValue <= 1.0f)
		zoomValue = 1.0f;
	if(zoomValue >= 45.0f)
		zoomValue = 45.0f;
}
