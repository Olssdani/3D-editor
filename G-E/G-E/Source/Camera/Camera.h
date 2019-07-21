#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
class Camera
{
protected:
	Camera() {

	}



	glm::mat4 perspective;
	glm::vec3 position;
	glm::mat4 view;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 worldUp;

public:
	//Return the view matrix
	glm::mat4 View() {
		return glm::lookAt(position, position + forward, up);
	}

	glm::vec3 GetPosition() {
		return position;
	}
};
