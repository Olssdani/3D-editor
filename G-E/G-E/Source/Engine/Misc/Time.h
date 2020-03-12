#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class time {
private:
	float timeLastFrame;
	float currentTime;
	float deltaTime;

	void calculateDeltaTime() {
		currentTime = glfwGetTime();
		deltaTime = currentTime - timeLastFrame;
		timeLastFrame = currentTime;
	}

public:
	//Constructor
	time() {
		timeLastFrame = currentTime = glfwGetTime();
		deltaTime = 0;
	}

	float getDeltaTime() {
		return deltaTime;
	}

	void update() {
		calculateDeltaTime();
	}
};
