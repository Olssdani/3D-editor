#pragma once
//#define WINDOW_MODE_EXPLICIT
//#define WINDOW_MODE_FULLSCREEN
#define WINDOW_MODE_FULLSCREEN_WINDOWED
#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "GUI/GUI.h"
#include "Camera/Editor_Camera.h"
#include "Object/Box.h"
#include "Object/Object.h"
#include "Object/Plane.h"
#include <vector>
#include "Input/Input.h"
#include "Misc/Time.h"


class Render{
public:
	Render();
	void Rendering();
	Editor_Camera* getCamera();

private:
	/*
		Variables 
	*/
	unsigned int SCREEN_WIDTH = 800;
	unsigned int SCREEN_HEIGHT = 800;
	GLFWmonitor* primaryMonitor;
	const GLFWvidmode * primaryVidMode;
	GLFWwindow* window;
	GUI *gui;
	int width, height;
	Editor_Camera *editorCamera;
	std::vector<Object> objects;
	DirectionalLight DL;
	std::vector<PointLight> PL;
	Input *input;
	Time time;
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
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Render* handler = reinterpret_cast<Render *>(glfwGetWindowUserPointer(window));
		handler->getCamera()->ProcessMouseScroll(yoffset);
	}
};