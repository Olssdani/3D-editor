#pragma once
#include "Camera/Camera.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtx/quaternion.hpp>
#ifndef Utilities_H
#define Utilities_H
#include "Utilities.h"
#endif
class Editor_Camera: public Camera {
private: 
	float movementSpeed = 0.01f;
	glm::vec3 lookPosition;
	glm::fquat rotationX, rotationY;
	glm::vec3 startPosition;
	float scrollOffset;
	glm::vec3 positionOffset;
public:
	//Constructor:
	//Mostly just set the variables to its inital state
	Editor_Camera(glm::vec3 _position) {
		position = _position;
		lookPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		//Forward is toward origo
		forward = glm::normalize(position - lookPosition);
		worldUp = glm::vec3(0.0f, 1.0f, 0.0f); 
		
		right = glm::normalize(glm::cross(worldUp, forward));
		up = glm::cross(forward, right);
		fov = 45.0f;
		startPosition = position;
		rotationX = glm::fquat(1.0f, 0, 0, 0);
		rotationY = glm::fquat(1.0f, 0, 0, 0);
		scrollOffset = 0;
		positionOffset = glm::vec3(0.0f, 1.0f, 0.0f);
		update();
	}

	//Move the camera in a 2d plane where the forward vector is orthogonal against the plane.
	void moveCamera(const double xpos, const double ypos) {
		
		//Move the position
		positionOffset = positionOffset - movementSpeed * (float)-xpos * right;
		positionOffset = positionOffset - movementSpeed * (float)ypos * up;
		//Move the positon that the camera is looking at
		lookPosition = lookPosition - movementSpeed * (float)-xpos * right;
		lookPosition = lookPosition - movementSpeed * (float)ypos * up;
		
		update();
	}

	//Rotate the camera around the lookPosition
	void rotateCamera(const double xpos, const double ypos) {

		float angleX = 0;
		float angleY = 0;
		if (abs(ypos) > abs(xpos)) {
			angleX = ypos * 0.005;
		}
		else {
			angleY = xpos * 0.005;
		}

		glm::vec3 angle = glm::vec3(angleX, 0, 0);
		rotationX = rotationX * glm::fquat(angle);

		angle = glm::vec3(0, angleY, 0);
		rotationY = rotationY * glm::fquat(angle);


		update();
	}

	void rotatelookPosition(const double xpos, const double ypos) {
		float angleX = 0;
		float angleY = 0;
		if (abs(ypos) > abs(xpos)) {
			angleX = ypos * 0.005;
		}else {
			angleY = xpos * 0.005;
		}


		glm::vec3 lookDirection = glm::normalize(lookPosition - position);
		float length = glm::length(lookPosition - position);

		
		//std::cout << "Look direction before: " << lookDirection.x << " " << lookDirection.y << " " << lookDirection.z << " ";
		glm::vec3 angle = glm::vec3(angleX, 0, 0);
		lookDirection = lookDirection * glm::fquat(angle);

		angle = glm::vec3(0, angleY, 0);
		lookDirection = lookDirection * glm::fquat(angle);

		lookPosition = position + length * lookDirection;
		//std::cout << "Look direction After: " << lookDirection.x << " " << lookDirection.y << " " << lookDirection.z << " " << std::endl;

		update();
	}

	void processInput(Input *input, const float xoffset, const float yoffset) {
		//Mouse buttons
		if (input->getMouseStatus(MOUSE_MIDDLE)) {
			moveCamera(xoffset, yoffset);
		}
		if (input->getKeyStatus(KEY_LEFT_ALT)) {

			if (input->getMouseStatus(MOUSE_LEFT)) {
				rotateCamera(xoffset, yoffset);
			}else if (input->getMouseStatus(MOUSE_RIGHT)) {
				rotatelookPosition(xoffset, yoffset);
			}
		}
	}
	
	//Move camera closer or further away from lookPosition
	void ProcessMouseScroll(float yoffset){
		//Get the vector between camera Position and lookPositon
		glm::vec3 lengthVector = position - lookPosition;
		//Get the root of magnitude of the vector.
		float length = sqrt(glm::dot(lengthVector, lengthVector));
		//Add it to the offset
		scrollOffset = scrollOffset + yoffset * (length*0.01f) ;

		update();
	}

private:
	void update() {
		//Rotate
		position = rotationX * (startPosition) *glm::conjugate(rotationX);
		position = rotationY * position *glm::conjugate(rotationY);

		//translation
		position =  glm::translate(positionOffset)*glm::vec4(position, 1.0f);

		//Calculate forward 
		forward = glm::normalize(lookPosition - position);

		//zoom
		position = position + scrollOffset * forward;

		//Calculate new right and up vector
		glm::vec3 newRight = glm::normalize(glm::cross(worldUp, forward));
		if (glm::l2Norm(newRight-right )>1.0) {
			right = glm::normalize(glm::cross(-worldUp, forward));
		}
		else {
			right = newRight;
		}
		up = glm::normalize(glm::cross(forward, right));	
	}

	glm::fquat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest) {
		start = glm::normalize(start);
		dest = glm::normalize(dest);

		float cosTheta = glm::dot(start, dest);
		glm::vec3 rotationAxis;

		if (cosTheta < -1 + 0.001f) {
			// special case when vectors in opposite directions :
			// there is no "ideal" rotation axis
			// So guess one; any will do as long as it's perpendicular to start
			// This implementation favors a rotation around the Up axis,
			// since it's often what you want to do.
			rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
			if (length2(rotationAxis) < 0.01) // bad luck, they were parallel, try again!
				rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);

			rotationAxis = normalize(rotationAxis);
			return glm::angleAxis(glm::radians(180.0f), rotationAxis);
		}

		// Implementation from Stan Melax's Game Programming Gems 1 article
		rotationAxis = glm::cross(start, dest);

		float s = sqrt((1 + cosTheta) * 2);
		float invs = 1 / s;

		return glm::fquat(
			s * 0.5f,
			rotationAxis.x * invs,
			rotationAxis.y * invs,
			rotationAxis.z * invs
		);
	}
};
