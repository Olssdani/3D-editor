#pragma once
#include "gui.h"

#include <string>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#	pragma comment(lib, "legacy_stdio_definitions")
#endif

class render;

class guiEntity : public gui {
public:
	enum class cameraType { MAIN = 0, EDITOR };

	guiEntity(GLFWwindow* w, render* r);
	void guiRender(const unsigned int editorTexture,
				   const unsigned int gameTexture,
				   const unsigned int viewportWidth,
				   const unsigned int viewportHeight,
				   const unsigned int textureWidth,
				   const unsigned int textureHeight);

	cameraType activeCamera();
	void changeEditor(cameraType c);

private:
	void intialize();
	void guiRender();
	const char* glsl_version = "#version 330";
	GLFWwindow* window;
	render* renderObject;
	float addPosition[3];
	float myColor[4];
	std::string fileName;
	int selectedClass = -1;
	int selectedItem = -1;
	cameraType cameraActiv;
};
