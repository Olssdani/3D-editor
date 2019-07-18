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

	//Initialize Camera
	editorCamera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f));
	//Intialize GUI
	gui = new GUI(window);

	//Initalize Input
	input = new Input(window);


	/***************************
		MODELS
	*******************************/
	//Plane
	Plane plane = Plane(glm::vec3(0,-5,0),100.0f, 100.0f, 1);

	//Boxes
	const char* url = "D:/Programmering/G-E/G-E/G-E/Textures/container.jpg";
	Box b1 = Box(1, 1, 1);
	b1.RotateX(20.0f * D2R);
	b1.setTexture(url);
	Box b2 = Box(1, 1, 1);
	b2.Translate(glm::vec3(2.0, -1.0, -0.3));
	b2.RotateY(20.0f * D2R);
	Box b3 = Box(1, 1, 1);
	b3.Translate(glm::vec3(6.0, 0.0, 0.0));
	b3.RotateY(20.0f * D2R);
	Box b4 = Box(1, 1, 1);
	b4.Translate(glm::vec3(0.0, -2.0, -2.3));
	b4.RotateY(45.0f * D2R);
	b4.RotateX(45.0f * D2R);
	b4.RotateZ(45.0f * D2R);


	objects.push_back(b1);
	objects.push_back(b2);
	objects.push_back(b3);
	objects.push_back(b4);
	objects.push_back(plane);
	DL = DirectionalLight(glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f));

	PointLight p1 = PointLight(glm::vec3(0.0, 0.0, 3.0), 1.0f, 0.09f, 0.032f);
	p1.SetAmbient(glm::vec3(0.01f, 0.01f, 0.01f));
	p1.SetDiffuse(glm::vec3(0.8f, 0.8f, 0.8f));
	p1.SetSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
	PL.push_back(p1);
	PointLight p2 = PointLight(glm::vec3(7.0, 0.0, 0.0), 1.0f, 0.09f, 0.032f);
	p2.SetAmbient(glm::vec3(0.0f, 0.0f, 0.0f));
	p2.SetDiffuse(glm::vec3(0.8f, 0.8f, 0.8f));
	p2.SetSpecular(glm::vec3(0.8f, 0.8f, 0.8f));
	PL.push_back(p2);

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
		input->update();

		//render
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		gui->Render();
		//Get the current projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(editorCamera->Zoom()), (float)width / (float)height, 0.1f, 1000.0f);
		//Get the current view matrix;
		glm::mat4 view = editorCamera->View();

		for each (Object o in objects)
		{
			o.Render(projection, view, editorCamera->GetPosition(), DL, PL);
		}

		for each (PointLight p in PL)
		{
			p.getBox()->RenderNoLight(projection, view, editorCamera->GetPosition());
		}

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


