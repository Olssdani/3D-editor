#include "editorCamera.h"
#include "Input/input.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
//Constructor:
editorCamera::editorCamera(const glm::vec3 position) {
	this->position = position;
	this->lookPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	//Forward is toward origo
	this->forward = glm::normalize(position - lookPosition);
	this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->right = glm::normalize(glm::cross(worldUp, forward));
	this->up = glm::cross(forward, right);
	this->fov = 45.0f;
	this->startPosition = position;
	this->rotationX = glm::fquat(1.0f, 0, 0, 0);
	this->rotationY = glm::fquat(1.0f, 0, 0, 0);
	this->scrollOffset = 0;
	this->positionOffset = glm::vec3(0.0f, 1.0f, 0.0f);
	update();
}

void editorCamera::moveCamera(const double xpos, const double ypos) {

	//Move the position
	positionOffset = positionOffset - movementSpeed * (float)-xpos * right;
	positionOffset = positionOffset - movementSpeed * (float)ypos * up;

	//Move the positon that the camera is looking at
	lookPosition = lookPosition - movementSpeed * (float)-xpos * right;
	lookPosition = lookPosition - movementSpeed * (float)ypos * up;

	update();
}

void editorCamera::rotateCamera(const double xpos, const double ypos) {

	float angleX = 0;
	float angleY = 0;

	if(abs(ypos) > abs(xpos)) {
		angleX = ypos * 0.005f;
	} else {
		angleY = xpos * 0.005f;
	}

	glm::vec3 angle = glm::vec3(angleX, 0, 0);
	rotationX = rotationX * glm::fquat(angle);

	angle = glm::vec3(0, angleY, 0);
	rotationY = rotationY * glm::fquat(angle);

	update();
}

void editorCamera::rotatelookPosition(const double xpos, const double ypos) {
	float angleX = 0;
	float angleY = 0;
	if(abs(ypos) > abs(xpos)) {
		angleX = ypos * 0.005;
	} else {
		angleY = xpos * 0.005;
	}

	glm::vec3 lookDirection = glm::normalize(lookPosition - position);
	float length = glm::length(lookPosition - position);

	glm::vec3 angle = glm::vec3(angleX, 0, 0);
	lookDirection = lookDirection * glm::fquat(angle);

	angle = glm::vec3(0, angleY, 0);
	lookDirection = lookDirection * glm::fquat(angle);

	lookPosition = position + length * lookDirection;

	update();
}

void editorCamera::processInput(const input* inputObject,
								const float xoffset,
								const float yoffset) {
	//Mouse buttons
	if(inputObject->getMouseStatus(MOUSE_MIDDLE)) {
		moveCamera(xoffset, yoffset);
	}
	if(inputObject->getKeyStatus(KEY_LEFT_ALT)) {

		if(inputObject->getMouseStatus(MOUSE_LEFT)) {
			rotateCamera(xoffset, yoffset);
		} else if(inputObject->getMouseStatus(MOUSE_RIGHT)) {
			rotatelookPosition(xoffset, yoffset);
		}
	}
}

void editorCamera::processMouseScroll(float yoffset) {
	glm::vec3 lengthVector = position - lookPosition;
	float length = sqrt(glm::dot(lengthVector, lengthVector));
	scrollOffset = scrollOffset + yoffset * (length * 0.01f);
	update();
}

void editorCamera::update() {
	//Rotate
	position = rotationX * (startPosition)*glm::conjugate(rotationX);
	position = rotationY * position * glm::conjugate(rotationY);

	//translation
	position = glm::translate(positionOffset) * glm::vec4(position, 1.0f);

	//Calculate forward
	forward = glm::normalize(lookPosition - position);

	//zoom
	position = position + scrollOffset * forward;

	//Calculate new right and up vector
	glm::vec3 newRight = glm::normalize(glm::cross(worldUp, forward));
	if(glm::l2Norm(newRight - right) > 1.0) {
		right = glm::normalize(glm::cross(-worldUp, forward));
	} else {
		right = newRight;
	}
	up = glm::normalize(glm::cross(forward, right));
}

glm::fquat editorCamera::rotationBetweenVectors(glm::vec3 start, glm::vec3 dest) {
	start = glm::normalize(start);
	dest = glm::normalize(dest);

	float cosTheta = glm::dot(start, dest);
	glm::vec3 rotationAxis;

	if(cosTheta < -1 + 0.001f) {
		// special case when vectors in opposite directions :
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		// This implementation favors a rotation around the Up axis,
		// since it's often what you want to do.
		rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
		if(length2(rotationAxis) < 0.01) // bad luck, they were parallel, try again!
			rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);

		rotationAxis = normalize(rotationAxis);
		return glm::angleAxis(glm::radians(180.0f), rotationAxis);
	}

	rotationAxis = glm::cross(start, dest);

	float s = sqrt((1 + cosTheta) * 2);
	float invs = 1 / s;

	return glm::fquat(
		s * 0.5f, rotationAxis.x * invs, rotationAxis.y * invs, rotationAxis.z * invs);
}
