#pragma once
//#define WINDOW_MODE_EXPLICIT
//#define WINDOW_MODE_FULLSCREEN
#define WINDOW_MODE_FULLSCREEN_WINDOWED
#include <glad/glad.h>
#include "Camera/camera.h"
#include <GLFW/glfw3.h>
#include <cstdio>

class guiEntity;
class input;
class FBO;
class scene;
class fpsCamera;
class editorCamera;

class render {
public:
	render();
	void renderScene();
	camera* getCamera();
	scene* getScene();

private:
	//For explicit window size
	const unsigned int SCREENWIDTH = 800;
	const unsigned int SCREENHEIGHT = 800;

	//Editor Variables
	const unsigned int EDITORWIDTH = 1080;
	const unsigned int EDITORHEIGHT = 720;

	//GLFW variable
	GLFWmonitor* primaryMonitor;
	const GLFWvidmode* primaryVidMode;
	GLFWwindow* window;

	editorCamera* editorCam;
	fpsCamera* mainCamera;
	input* inputObject;
	guiEntity* gui;
	int viewportWidth = 0, viewportHeight = 0;
	scene* sceneObject;

	//Mouse
	bool firstMouse = true;
	float lastX = SCREENWIDTH / 2.0f;
	float lastY = SCREENHEIGHT / 2.0f;
	float scroll_Yoffset = 0;
	float scroll_Xoffset = 0;
	float xoffset, yoffset;

	bool init();
	void initCallbackFunctions();
	void processEditorInputs(GLFWwindow* window);
	void mouseCallback();

	/*
		Static callbacks Functions
	*/
	static void glfwErrorCallback(int error, const char* description) {
		fprintf(stderr, "Glfw Error %d: %s\n", error, description);
	}

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
		render* handler = reinterpret_cast<render*>(glfwGetWindowUserPointer(window));
		handler->getCamera()->processMouseScroll(yoffset);
	}
};
