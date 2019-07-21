#pragma once
//#define WINDOW_MODE_EXPLICIT
//#define WINDOW_MODE_FULLSCREEN
#define WINDOW_MODE_FULLSCREEN_WINDOWED
#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "GUI/GUI.h"
#include "Camera/Camera.h"
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
	Camera *editorCamera;
	std::vector<Object> objects;
	DirectionalLight DL;
	std::vector<PointLight> PL;
	Input *input;
	Time time;

	/*
		Methods
	*/
	bool Init();
	void InitCallbackFunctions();



	//Callback function for errors in glfw
	static void glfw_error_callback(int error, const char* description){
		fprintf(stderr, "Glfw Error %d: %s\n", error, description);
	}

	// glfw: whenever the window size changed (by OS or user resize) this callback function executes
	// ---------------------------------------------------------------------------------------------
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height){
		glViewport(0, 0, width, height);
	}

	void processEditorInputs(GLFWwindow *window);
};