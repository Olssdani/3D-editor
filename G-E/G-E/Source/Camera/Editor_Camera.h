#pragma once
#include "Camera/Camera.h"
class Editor_Camera: public Camera {
public:
	Editor_Camera(glm::vec3 _position) {
		position = _position;
		//Forward is toward origo
		forward = glm::vec3(0.0f, 0.0f, 0.0f) - position;
		worldUp = glm::vec3(0.0f, 1.0f, 0.0f); 
		up = glm::vec3(0.0f, 1.0f, 0.0f);
		right = glm::vec3(1.0f, 0.0f, 0.0f);
		fov = 45.0f;
	}




};