#pragma once
//#define WINDOW_MODE_EXPLICIT
//#define WINDOW_MODE_FULLSCREEN
#define WINDOW_MODE_FULLSCREEN_WINDOWED

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <cstdio>
#include "Camera/Camera.h"

class GUI;
class Input;
class FBO;
class Scene;
class FPS_Camera;
class Editor_Camera;

class Render{
public:
	Render();
	void Rendering();
	Camera* getCamera();

	Scene* getScene() {
		return scene;
	}

private:
	/*
		Variables 
	*/
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 800;
	const unsigned int editorWidth = 1080;
	const unsigned int editorHeight = 720;
	GLFWmonitor* primaryMonitor;
	const GLFWvidmode * primaryVidMode;
	GLFWwindow* window;
	GUI *gui;
	int width, height;
	Editor_Camera *editorCamera;
	FPS_Camera *mainCamera;
	Input *input;



	Scene *scene;
	//Mouse
	bool firstMouse = true;
	float lastX = SCREEN_WIDTH / 2.0f;
	float lastY = SCREEN_HEIGHT / 2.0f;
	float scroll_Yoffset = 0;
	float scroll_Xoffset = 0;
	float xoffset, yoffset;

	/*
		Methods
	*/
	bool Init();
	void InitCallbackFunctions();
	void processEditorInputs(GLFWwindow *window);
	void mouse_callback();
	
	/*
		Static callbacks Functions
	*/

	//Callback function for errors in glfw
	static void glfw_error_callback(int error, const char* description){
		fprintf(stderr, "Glfw Error %d: %s\n", error, description);
	}

	// glfw: whenever the window size changed (by OS or user resize) this callback function executes
	// ---------------------------------------------------------------------------------------------
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height){
		glViewport(0, 0, width, height);
	}
	
	//scroll input
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
		Render* handler = reinterpret_cast<Render *>(glfwGetWindowUserPointer(window));
		handler->getCamera()->ProcessMouseScroll(yoffset);
	}
};