#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include "Camera.h"
//Class for handling the camera. This class is more or less taken from https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h
class FPS_Camera: public Camera
{
public:
	//Variables
	// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};
	FPS_Camera(glm::vec3 _position);
	FPS_Camera(glm::vec3 _position, glm::vec3 _up, float _yaw, float _pitch);

	float Zoom();

	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch);
	void ProcessMouseScroll(float yoffset);


private:
	float yaw;
	float pitch;
	float movementSpeed = 10.0f;
	float mouseSensitivity = 0.1f;
	float zoom = 45.0f;

	//Functions
	//Updates all variables before rendering
	void Update();
};