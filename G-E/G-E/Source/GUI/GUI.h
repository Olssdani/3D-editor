#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include "Render/Render.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif
class Render;

class GUI{
public:
	GUI(GLFWwindow *w,Render *r);
	void guiRender();

private:
	void Intialize();

	const char* glsl_version = "#version 330";
	GLFWwindow* window;
	Render* render;
	float addPosition[3];

	float my_color[4];
};