#include "render.h"
#include "Misc/Time.h"
#include <vector>
#include "GUI/guiEntity.h"
#include "Input/input.h"
#include "FBO/colorFbo.h"
#include <iostream>
#include "Object/box.h"
#include "Object/object.h"
#include "Object/plane.h"
#include "Scene/scene.h"
#include "Camera/editorCamera.h"
#include "Camera/fpsCamera.h"
#include "imgui.h"

render::render() {}

bool render::init() {

	// glfw: initialize and configure
	glfwSetErrorCallback(glfwErrorCallback);

	if(!glfwInit())
		return false;

	// OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//Compatibility for apple computers
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//Get primary monitor information
	primaryMonitor = glfwGetPrimaryMonitor();
	primaryVidMode = glfwGetVideoMode(primaryMonitor);

// glfw window creation
#if defined(WINDOW_MODE_EXPLICIT)
	window = glfwCreateWindow(SCREENWIDTH, SCREENWIDTH, "Engine", NULL, NULL);
#elif defined(WINDOW_MODE_FULLSCREEN)
	window = glfwCreateWindow(
		primaryVidMode->width, primaryVidMode->width, "Engine", primaryMonitor, NULL);
#elif defined(WINDOW_MODE_FULLSCREEN_WINDOWED)
	window = glfwCreateWindow(primaryVidMode->width, primaryVidMode->width, "Engine", NULL, NULL);
#endif

	if(window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	initCallbackFunctions();

	// glad: load all OpenGL function pointers
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	//Initialize Cameras
	editorCam = new editorCamera(glm::vec3(0.0f, 0.0f, 10.0f));
	mainCamera =
		new fpsCamera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, -1.0f, 0.0f), 90.0f, 0.0f);

	//Attach the render to the window pointer for the scroll wheel callback
	glfwSetWindowUserPointer(window, reinterpret_cast<void*>(this));

	gui = new guiEntity(window, this);
	inputObject = new input(window);
	sceneObject = new scene();
}

void render::initCallbackFunctions() {
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetScrollCallback(window, scrollCallback);
}

void render::renderScene() {

	ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
	time timeObject;

	glfwGetWindowSize(window, &viewportWidth, &viewportHeight);
	fbo* frameBuffer = new colorFbo(EDITORWIDTH, EDITORHEIGHT);
	//fbo depthMapFbo(1024, 1024);

	while(!glfwWindowShouldClose(window)) {

		//Update critical classes first
		inputObject->update();
		timeObject.update();
		mouseCallback();
		glfwGetWindowSize(window, &viewportWidth, &viewportHeight);

		//Evaluate inputs, must be done after input update!!!!
		processEditorInputs(window);

		if(gui->activeCamera() == guiEntity::cameraType::EDITOR) {
			editorCam->processInput(inputObject, xoffset, yoffset);
		} else if(gui->activeCamera() == guiEntity::cameraType::MAIN) {
			mainCamera->processKeyboard(inputObject, timeObject.getDeltaTime());
			mainCamera->processMouseMovement(xoffset, yoffset, true);
		}

		/*
			RENDERING
		*/
		frameBuffer->bind();

		//Clear screen
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if(gui->activeCamera() == guiEntity::cameraType::EDITOR) {
			glm::mat4 projection = glm::perspective(glm::radians(editorCam->getFov()),
													(float)EDITORWIDTH / (float)EDITORHEIGHT,
													0.1f,
													1000.0f);
			glm::mat4 view = editorCam->getView();
			glViewport(0, 0, EDITORWIDTH, EDITORHEIGHT);
			glEnable(GL_DEPTH_TEST);
			sceneObject->renderScene(projection, view, editorCam->getPosition());
		} else if(gui->activeCamera() == guiEntity::cameraType::MAIN) {
			glm::mat4 projection = glm::perspective(glm::radians(mainCamera->getFov()),
													(float)EDITORWIDTH / (float)EDITORHEIGHT,
													0.1f,
													1000.0f);
			glm::mat4 view = mainCamera->getView();
			glViewport(0, 0, EDITORWIDTH, EDITORHEIGHT);
			glEnable(GL_DEPTH_TEST);
			sceneObject->renderScene(projection, view, mainCamera->getPosition());

			if(inputObject->getKeyStatus(KEY_R))
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			if(inputObject->getKeyStatus(KEY_N))
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		glViewport(0, 0, viewportWidth, viewportHeight);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		gui->guiRender(frameBuffer->getTexture(),
					   frameBuffer->getTexture(),
					   viewportWidth,
					   viewportHeight,
					   EDITORWIDTH,
					   EDITORHEIGHT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

void render::processEditorInputs(GLFWwindow* window) {
	//Toggle wireframe or solid
	if(inputObject->getKeyStatus(KEY_1))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if(inputObject->getKeyStatus(KEY_2))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(inputObject->getKeyStatus(KEY_SPACE)) {
		sceneObject->updateShaders();
	}
}

void render::mouseCallback() {

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	if(firstMouse) {
		lastX = static_cast<float>(xpos);
		lastY = static_cast<float>(ypos);
		firstMouse = false;
	}

	xoffset = xpos - lastX;
	yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;
}

camera* render::getCamera() {
	if(gui->activeCamera() == guiEntity::cameraType::EDITOR) {
		return editorCam;
	} else if(gui->activeCamera() == guiEntity::cameraType::MAIN) {
		return mainCamera;
	}
	return editorCam;
}

scene* render::getScene() {
	return sceneObject;
}
