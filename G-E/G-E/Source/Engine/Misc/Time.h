#pragma once
#include <GLFW/glfw3.h>

class Time {
private:
	float timeLastFrame;
	float currentTime;
	float deltaTime;
public:
	//Constructor
	Time() {
		timeLastFrame = currentTime = glfwGetTime();
		deltaTime = 0;
	}

	float getDeltaTime() {
		return deltaTime;
	}
private:
	//Get time from last read
	void calculateDeltaTime() {
		currentTime = glfwGetTime();
		deltaTime = currentTime - timeLastFrame;
		timeLastFrame = currentTime;
	}

public:
	//Update variables.
	void update() {
		calculateDeltaTime();
	}

};