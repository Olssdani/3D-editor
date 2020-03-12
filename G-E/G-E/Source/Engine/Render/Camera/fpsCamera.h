#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include "camera.h"

class input;

//Class for handling the camera. This class is more or less
//taken from https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h
class fpsCamera : public camera {
public:
	// Defines several possible options for camera movement.
	//Used as abstraction to stay away from window-system specific input methods
	enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };

	fpsCamera(glm::vec3 position);
	fpsCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);

	float zoom();
	void processKeyboard(input* inputObject, float deltaTime);
	void processMouseMovement(float xoffset, float yoffset, bool constrainPitch);
	void processMouseScroll(float yoffset);

private:
	float yaw;
	float pitch;
	float movementSpeed = 10.0f;
	float mouseSensitivity = 0.1f;
	float zoomValue = 45.0f;
	//Updates all variables before rendering
	void update();
};
