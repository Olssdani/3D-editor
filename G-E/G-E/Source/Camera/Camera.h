#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include "Input/Input.h"

class Camera
{
protected:
	Camera() {

	}

	//glm::mat4 perspective;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 worldUp;
	glm::vec3 right;

	glm::mat4 view;

	float fov;
public:
	//Return the view matrix
	glm::mat4 View() {
		return glm::lookAt(position, position +forward, up);
	}

	glm::vec3 GetPosition() {
		return position;
	}

	float getFov(){
		return fov;
	}


};
