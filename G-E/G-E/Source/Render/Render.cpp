#include "Render.h"


Render::Render() {
	Init();
}


bool Render::Init() {
	
	// glfw: initialize and configure
	// ------------------------------
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return false;

	// OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Compatibility for apple computers
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
	#endif


	primaryMonitor = glfwGetPrimaryMonitor();
	primaryVidMode = glfwGetVideoMode(primaryMonitor);
	// glfw window creation
	// --------------------
	#if defined(WINDOW_MODE_EXPLICIT)
		window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_WIDTH, "Engine", NULL, NULL);
	#elif defined(WINDOW_MODE_FULLSCREEN)
		window = glfwCreateWindow(primaryVidMode->width, primaryVidMode->width, "Engine", primaryMonitor, NULL);
	#elif defined(WINDOW_MODE_FULLSCREEN_WINDOWED)
		window = glfwCreateWindow(primaryVidMode->width, primaryVidMode->width, "Engine", NULL, NULL);
	#endif 
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	InitCallbackFunctions();


	// Disable the mouse and capture it
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}



	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	//Intialize GUI
	gui = new GUI(window);

}

void Render::InitCallbackFunctions() {
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetScrollCallback(window, scroll_callback);
}



void Render::Rendering() {

	while (!glfwWindowShouldClose(window))
	{
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		//updateTime();
		//
		glfwGetWindowSize(window, &width, &height);
		// input
		// -----
		//processInput(window);

		//render
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		gui->Render();
		//Get the current projection matrix
		//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom()), (float)width / (float)height, 0.1f, 1000.0f);
		//Get the current view matrix;
		//glm::mat4 view = camera.View();

		/*for each (Object o in objects)
		{
			o.Render(projection, view, camera.GetPosition(), DL, PL);
		}

		for each (PointLight p in PL)
		{
			p.getBox()->RenderNoLight(projection, view, camera.GetPosition());
		}*/

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();


}


/*
	CallbackFunctions
*/


