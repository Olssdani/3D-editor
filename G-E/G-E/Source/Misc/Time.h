#pragma once
#include <GLFW/glfw3.h>

class Time {
public:
	//Constructor
	Time() {
		timeLastFrame = currentTime = glfwGetTime();
	}

	//Get time from last read
	float deltaTime() {
		currentTime = glfwGetTime();
		float deltaTime = currentTime - timeLastFrame;
		timeLastFrame = currentTime;
		return deltaTime;
	}

private:
	float timeLastFrame;
	float currentTime;
};