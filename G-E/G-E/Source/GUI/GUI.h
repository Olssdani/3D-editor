#pragma once
#include <stdio.h>
#include "Render/Render.h"
#ifndef Utilities_H
#define Utilities_H
#include "Utilities.h"
#endif
#include <stdlib.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif
class Render;

class GUI{
public:
	GUI(GLFWwindow *w,Render *r);
	void guiRender(const unsigned int editorTexture, const unsigned int gameTexture,
		const unsigned int viewportWidth, const unsigned int viewportHeight,
		const unsigned int textureWidth, const unsigned int textureHeight);

private:
	void Intialize();

	const char* glsl_version = "#version 330";
	GLFWwindow* window;
	Render* render;
	float addPosition[3];
	float my_color[4];
	std::string fileName;
	int selectedClass = -1;
	int selectedItem = -1;
};