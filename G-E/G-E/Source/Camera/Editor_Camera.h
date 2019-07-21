#pragma once
#include "Camera/Camera.h"
class Editor_Camera:Camera {

	Editor_Camera(glm::vec3 _position) {
		position = _position;
		worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	}




};