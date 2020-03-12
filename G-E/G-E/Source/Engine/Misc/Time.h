#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class time {
private:
	float timeLastFrame;
	float currentTime;
	float deltaTime;

	void calculateDeltaTime() {
		currentTime = static_cast<float>(glfwGetTime());
		deltaTime = currentTime - timeLastFrame;
		timeLastFrame = currentTime;
	}

public:
	//Constructor
	time() {
		timeLastFrame = currentTime = static_cast<float>(glfwGetTime());
		deltaTime = 0;
	}

	float getDeltaTime() {
		return deltaTime;
	}

	void update() {
		calculateDeltaTime();
	}
};
