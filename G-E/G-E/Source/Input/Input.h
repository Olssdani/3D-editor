#pragma once
#include <GLFW/glfw3.h>
class Input {
public:
#define KEY_0 0
#define KEY_1 1
#define KEY_2  2
#define KEY_3  3
#define KEY_4  4
#define KEY_5  5
#define KEY_6  6
#define KEY_7  7
#define KEY_8  8
#define KEY_9  9
#define KEY_A  10
#define KEY_B  11
#define KEY_C  12
#define KEY_D  13
#define KEY_E  14
#define KEY_F  15
#define KEY_G  16
#define KEY_H  17
#define KEY_I  18
#define KEY_J  19
#define KEY_K  20
#define KEY_L  21
#define KEY_M  22
#define KEY_N  23
#define KEY_O  24
#define KEY_P  25
#define KEY_Q  26
#define KEY_R  27
#define KEY_S  28
#define KEY_T  29
#define KEY_U  30
#define KEY_V  31
#define KEY_W  32
#define KEY_X  33
#define KEY_Y  34
#define KEY_Z  35
#define KEY_SPACE  36
#define KEY_APOSTROPHE  37
#define KEY_COMMA  38
#define KEY_MINUS  39
#define KEY_PERIOD  40
#define KEY_SLASH  41
#define KEY_ESCAPE  42
#define KEY_ENTER  43
#define KEY_TAB  44
#define KEY_BACKSPACE  45
#define KEY_INSERT  46
#define KEY_DELETE  47
#define KEY_RIGHT  48
#define KEY_LEFT  49
#define KEY_DOWN  50
#define KEY_UP  51 
#define KEY_CAPS_LOCK  52
#define KEY_F1  53
#define KEY_F2  54
#define KEY_F3  55
#define KEY_F4  56
#define KEY_F5  57
#define KEY_F6  58
#define KEY_F7  59
#define KEY_F8  60
#define KEY_F9  61
#define KEY_F10  62
#define KEY_F12  63
#define KEY_KP_0  64
#define KEY_KP_1  65
#define KEY_KP_2  66
#define KEY_KP_3  67
#define KEY_KP_4  68
#define KEY_KP_5  69
#define KEY_KP_6  70
#define KEY_KP_7  71
#define KEY_KP_8  72
#define KEY_KP_9  73
#define KEY_KP_DECIMAL  74
#define KEY_KP_DIVIDE  75
#define KEY_KP_MULTIPLY  76
#define KEY_KP_SUBSTRACT  77
#define KEY_KP_ADD  78
#define KEY_KP_ENTER  79
#define KEY_KP_EQUAL  80
#define KEY_LEFT_SHIFT  81
#define KEY_LEFT_CONTROL  82
#define KEY_LEFT_ALT  83
#define KEY_RIGHT_SHIFT  84
#define KEY_RIGHT_CONTROL  85
#define KEY_RIGHT_ALT  86

private:
	bool keyStatus[87];
	GLFWwindow* window;
public:
	void update() {
		keyStatus[KEY_0] = glfwGetKey(window, GLFW_KEY_0);
		keyStatus[KEY_1] = glfwGetKey(window, GLFW_KEY_1);
		keyStatus[KEY_2] = glfwGetKey(window, GLFW_KEY_2);
		keyStatus[KEY_3] = glfwGetKey(window, GLFW_KEY_3);
		keyStatus[KEY_4] = glfwGetKey(window, GLFW_KEY_4);
		keyStatus[KEY_5] = glfwGetKey(window, GLFW_KEY_5);
		keyStatus[KEY_6] = glfwGetKey(window, GLFW_KEY_6);
		keyStatus[KEY_7] = glfwGetKey(window, GLFW_KEY_7);
		keyStatus[KEY_8] = glfwGetKey(window, GLFW_KEY_8);
		keyStatus[KEY_9] = glfwGetKey(window, GLFW_KEY_9);		
		keyStatus[KEY_A] = glfwGetKey(window, GLFW_KEY_A);
		keyStatus[KEY_B] = glfwGetKey(window, GLFW_KEY_B);
		keyStatus[KEY_C] = glfwGetKey(window, GLFW_KEY_C);
		keyStatus[KEY_D] = glfwGetKey(window, GLFW_KEY_D);
		keyStatus[KEY_E] = glfwGetKey(window, GLFW_KEY_E);
		keyStatus[KEY_F] = glfwGetKey(window, GLFW_KEY_F);
		keyStatus[KEY_G] = glfwGetKey(window, GLFW_KEY_G);
		keyStatus[KEY_H] = glfwGetKey(window, GLFW_KEY_H);
		keyStatus[KEY_I] = glfwGetKey(window, GLFW_KEY_I);
		keyStatus[KEY_J] = glfwGetKey(window, GLFW_KEY_J);
		keyStatus[KEY_K] = glfwGetKey(window, GLFW_KEY_K);
		keyStatus[KEY_L] = glfwGetKey(window, GLFW_KEY_L);
		keyStatus[KEY_M] = glfwGetKey(window, GLFW_KEY_M);
		keyStatus[KEY_N] = glfwGetKey(window, GLFW_KEY_N);
		keyStatus[KEY_O] = glfwGetKey(window, GLFW_KEY_O);
		keyStatus[KEY_P] = glfwGetKey(window, GLFW_KEY_P);
		keyStatus[KEY_Q] = glfwGetKey(window, GLFW_KEY_Q);
		keyStatus[KEY_R] = glfwGetKey(window, GLFW_KEY_R);
		keyStatus[KEY_S] = glfwGetKey(window, GLFW_KEY_S);
		keyStatus[KEY_T] = glfwGetKey(window, GLFW_KEY_T);
		keyStatus[KEY_U] = glfwGetKey(window, GLFW_KEY_U);
		keyStatus[KEY_V] = glfwGetKey(window, GLFW_KEY_V);
		keyStatus[KEY_W] = glfwGetKey(window, GLFW_KEY_W);
		keyStatus[KEY_X] = glfwGetKey(window, GLFW_KEY_X);
		keyStatus[KEY_Y] = glfwGetKey(window, GLFW_KEY_Y);
		keyStatus[KEY_Z] = glfwGetKey(window, GLFW_KEY_Z);
	}

	bool getKeyStatus(const unsigned int key) {
		return keyStatus[key];
	}

	Input(GLFWwindow* _window) {
		window = _window;
		update();
	}

	void updateWindow(GLFWwindow* _window) {
		window = _window;
	}



};