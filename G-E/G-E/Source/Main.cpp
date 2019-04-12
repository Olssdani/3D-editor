#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Object/Box.h"
#include "Object/Object.h"
#include "Object/Plane.h"
#include <iostream>
#include "Camera\Camera.h"
#include "Light\DirectionalLight.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void updateTime();

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 800;

Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));

//Mouse
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// time
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
	int width, height;
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	const GLFWvidmode * mode = glfwGetVideoMode(primary);
														 // glfw window creation
														 // --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	// Disable the mouse and capture it
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//Plane
	Plane plane = Plane(glm::vec3(0,-5,0),10.0f, 10.0f, 1);

	//Boxes
	Box b1 = Box(1, 1, 1);
	b1.RotateX(20.0f * D2R);
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

	std::vector<Object> objects;
	objects.push_back(b1);
	objects.push_back(b2);
	objects.push_back(b3);
	objects.push_back(b4);
	objects.push_back(plane);
	DirectionalLight DL(glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.5f, 0.5f, 0.5f));
	std::vector<PointLight> PL;
	PointLight p1 = PointLight(glm::vec3(0.0, 0.0, 3.0), 1.0f, 0.09f, 0.032f);
	p1.SetAmbient(glm::vec3(0.1f, 0.1f, 0.1f));
	p1.SetDiffuse(glm::vec3(0.8f, 0.8f, 0.8f));
	p1.SetSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
	PL.push_back(p1);
	PointLight p2 = PointLight(glm::vec3(7.0, 0.0, 0.0), 1.0f, 0.09f, 0.032f);
	p2.SetAmbient(glm::vec3(0.1f, 0.1f, 0.1f));
	p2.SetDiffuse(glm::vec3(0.8f, 0.8f, 0.8f));
	p2.SetSpecular(glm::vec3(0.8f, 0.8f, 0.8f));
	PL.push_back(p2);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		updateTime();
		//
		glfwGetWindowSize(window,&width, &height);
		// input
		// -----
		processInput(window);

		//render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Get the current projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom()), (float)width / (float)height, 0.1f, 1000.0f);
		//Get the current view matrix;
		glm::mat4 view = camera.View();
		
		for each (Object o in objects)
		{
			o.Render(projection, view, camera.GetPosition(), DL, PL);
		}
		
		for each (PointLight p in PL)
		{
			p.getBox()->RenderNoLight(projection, view, camera.GetPosition());
		}
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	//Close
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//Move camera
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(camera.FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(camera.BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(camera.LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(camera.RIGHT, deltaTime);


	//Toggle wireframe or solid
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


//Get mouse movement
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset, true);
}

//scroll input
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	SCR_HEIGHT = height;
	SCR_WIDTH = width;
	glViewport(0, 0, width, height);
}


//Get delta time
void updateTime()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}
















