#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
class input {
public:
#define KEY_0 0
#define KEY_1 1
#define KEY_2 2
#define KEY_3 3
#define KEY_4 4
#define KEY_5 5
#define KEY_6 6
#define KEY_7 7
#define KEY_8 8
#define KEY_9 9
#define KEY_A 10
#define KEY_B 11
#define KEY_C 12
#define KEY_D 13
#define KEY_E 14
#define KEY_F 15
#define KEY_G 16
#define KEY_H 17
#define KEY_I 18
#define KEY_J 19
#define KEY_K 20
#define KEY_L 21
#define KEY_M 22
#define KEY_N 23
#define KEY_O 24
#define KEY_P 25
#define KEY_Q 26
#define KEY_R 27
#define KEY_S 28
#define KEY_T 29
#define KEY_U 30
#define KEY_V 31
#define KEY_W 32
#define KEY_X 33
#define KEY_Y 34
#define KEY_Z 35
#define KEY_SPACE 36
#define KEY_APOSTROPHE 37
#define KEY_COMMA 38
#define KEY_MINUS 39
#define KEY_PERIOD 40
#define KEY_SLASH 41
#define KEY_ESCAPE 42
#define KEY_ENTER 43
#define KEY_TAB 44
#define KEY_BACKSPACE 45
#define KEY_INSERT 46
#define KEY_DELETE 47
#define KEY_RIGHT 48
#define KEY_LEFT 49
#define KEY_DOWN 50
#define KEY_UP 51
#define KEY_CAPS_LOCK 52
#define KEY_F1 53
#define KEY_F2 54
#define KEY_F3 55
#define KEY_F4 56
#define KEY_F5 57
#define KEY_F6 58
#define KEY_F7 59
#define KEY_F8 60
#define KEY_F9 61
#define KEY_F10 62
#define KEY_F12 63
#define KEY_KP_0 64
#define KEY_KP_1 65
#define KEY_KP_2 66
#define KEY_KP_3 67
#define KEY_KP_4 68
#define KEY_KP_5 69
#define KEY_KP_6 70
#define KEY_KP_7 71
#define KEY_KP_8 72
#define KEY_KP_9 73
#define KEY_KP_DECIMAL 74
#define KEY_KP_DIVIDE 75
#define KEY_KP_MULTIPLY 76
#define KEY_KP_SUBTRACT 77
#define KEY_KP_ADD 78
#define KEY_KP_ENTER 79
#define KEY_KP_EQUAL 80
#define KEY_LEFT_SHIFT 81
#define KEY_LEFT_CONTROL 82
#define KEY_LEFT_ALT 83
#define KEY_RIGHT_SHIFT 84
#define KEY_RIGHT_CONTROL 85
#define KEY_RIGHT_ALT 86

#define MOUSE_LEFT 0
#define MOUSE_RIGHT 1
#define MOUSE_MIDDLE 2
private:
	bool keyStatus[87];
	bool mouseStatus[3];
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
		keyStatus[KEY_SPACE] = glfwGetKey(window, GLFW_KEY_SPACE);
		keyStatus[KEY_APOSTROPHE] = glfwGetKey(window, GLFW_KEY_APOSTROPHE);
		keyStatus[KEY_COMMA] = glfwGetKey(window, GLFW_KEY_COMMA);
		keyStatus[KEY_MINUS] = glfwGetKey(window, GLFW_KEY_MINUS);
		keyStatus[KEY_PERIOD] = glfwGetKey(window, GLFW_KEY_PERIOD);
		keyStatus[KEY_SLASH] = glfwGetKey(window, GLFW_KEY_SLASH);
		keyStatus[KEY_ENTER] = glfwGetKey(window, GLFW_KEY_ENTER);
		keyStatus[KEY_TAB] = glfwGetKey(window, GLFW_KEY_TAB);
		keyStatus[KEY_BACKSPACE] = glfwGetKey(window, GLFW_KEY_BACKSPACE);
		keyStatus[KEY_INSERT] = glfwGetKey(window, GLFW_KEY_INSERT);
		keyStatus[KEY_DELETE] = glfwGetKey(window, GLFW_KEY_DELETE);
		keyStatus[KEY_RIGHT] = glfwGetKey(window, GLFW_KEY_RIGHT);
		keyStatus[KEY_LEFT] = glfwGetKey(window, GLFW_KEY_LEFT);
		keyStatus[KEY_DOWN] = glfwGetKey(window, GLFW_KEY_DOWN);
		keyStatus[KEY_UP] = glfwGetKey(window, GLFW_KEY_UP);
		keyStatus[KEY_CAPS_LOCK] = glfwGetKey(window, GLFW_KEY_CAPS_LOCK);
		keyStatus[KEY_F1] = glfwGetKey(window, GLFW_KEY_F1);
		keyStatus[KEY_F2] = glfwGetKey(window, GLFW_KEY_F2);
		keyStatus[KEY_F3] = glfwGetKey(window, GLFW_KEY_F3);
		keyStatus[KEY_F4] = glfwGetKey(window, GLFW_KEY_F4);
		keyStatus[KEY_F5] = glfwGetKey(window, GLFW_KEY_F5);
		keyStatus[KEY_F6] = glfwGetKey(window, GLFW_KEY_F6);
		keyStatus[KEY_F7] = glfwGetKey(window, GLFW_KEY_F7);
		keyStatus[KEY_F8] = glfwGetKey(window, GLFW_KEY_F8);
		keyStatus[KEY_F9] = glfwGetKey(window, GLFW_KEY_F9);
		keyStatus[KEY_F10] = glfwGetKey(window, GLFW_KEY_F10);
		keyStatus[KEY_F12] = glfwGetKey(window, GLFW_KEY_F12);
		keyStatus[KEY_KP_0] = glfwGetKey(window, GLFW_KEY_KP_0);
		keyStatus[KEY_KP_1] = glfwGetKey(window, GLFW_KEY_KP_1);
		keyStatus[KEY_KP_2] = glfwGetKey(window, GLFW_KEY_KP_2);
		keyStatus[KEY_KP_3] = glfwGetKey(window, GLFW_KEY_KP_3);
		keyStatus[KEY_KP_4] = glfwGetKey(window, GLFW_KEY_KP_4);
		keyStatus[KEY_KP_5] = glfwGetKey(window, GLFW_KEY_KP_5);
		keyStatus[KEY_KP_6] = glfwGetKey(window, GLFW_KEY_KP_6);
		keyStatus[KEY_KP_7] = glfwGetKey(window, GLFW_KEY_KP_7);
		keyStatus[KEY_KP_8] = glfwGetKey(window, GLFW_KEY_KP_8);
		keyStatus[KEY_KP_9] = glfwGetKey(window, GLFW_KEY_KP_9);
		keyStatus[KEY_KP_DECIMAL] = glfwGetKey(window, GLFW_KEY_KP_DECIMAL);
		keyStatus[KEY_KP_DIVIDE] = glfwGetKey(window, GLFW_KEY_KP_DIVIDE);
		keyStatus[KEY_KP_MULTIPLY] = glfwGetKey(window, GLFW_KEY_KP_MULTIPLY);
		keyStatus[KEY_KP_SUBTRACT] = glfwGetKey(window, GLFW_KEY_KP_SUBTRACT);
		keyStatus[KEY_KP_ADD] = glfwGetKey(window, GLFW_KEY_KP_ADD);
		keyStatus[KEY_KP_ENTER] = glfwGetKey(window, GLFW_KEY_KP_ENTER);
		keyStatus[KEY_KP_EQUAL] = glfwGetKey(window, GLFW_KEY_KP_EQUAL);
		keyStatus[KEY_LEFT_SHIFT] = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
		keyStatus[KEY_LEFT_CONTROL] = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL);
		keyStatus[KEY_LEFT_ALT] = glfwGetKey(window, GLFW_KEY_LEFT_ALT);
		keyStatus[KEY_RIGHT_SHIFT] = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT);
		keyStatus[KEY_RIGHT_CONTROL] = glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL);
		keyStatus[KEY_RIGHT_ALT] = glfwGetKey(window, GLFW_KEY_RIGHT_ALT);

		mouseStatus[MOUSE_LEFT] = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		mouseStatus[MOUSE_RIGHT] = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
		mouseStatus[MOUSE_MIDDLE] = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);
	}

	const bool getKeyStatus(const unsigned int key) const {
		return keyStatus[key];
	}

	const bool getMouseStatus(const unsigned int key) const {
		return mouseStatus[key];
	}

	input(GLFWwindow* _window) {
		window = _window;
		update();
	}

	void updateCurrentWindow(GLFWwindow* _window) {
		window = _window;
	}
};
