#pragma once
#ifndef MOUSE
#define MOUSE

#include"Tools.h"
#include<glm/glm.hpp>

namespace vogl
{
	class Mouse
	{
		friend class RenderWindow;
	private:
		static Vector2<float> pos;

		static bool isEnter;

		static GLFWwindow** window;

		static Vector2<float> scroll;

		static void cursorPosCallBack(GLFWwindow* window, double x, double y);

		static void cursorEnterCallBack(GLFWwindow* window, int entered);
	
		static void scrollCallBack(GLFWwindow* window, double xoffset, double yoffset);

	public:
		enum Button
		{
			BUTTON_1 = GLFW_MOUSE_BUTTON_1,
			BUTTON_2 = GLFW_MOUSE_BUTTON_2,
			BUTTON_3 = GLFW_MOUSE_BUTTON_3,
			BUTTON_4 = GLFW_MOUSE_BUTTON_4,
			BUTTON_5 = GLFW_MOUSE_BUTTON_5,
			BUTTON_6 = GLFW_MOUSE_BUTTON_6,
			BUTTON_7 = GLFW_MOUSE_BUTTON_7,
			BUTTON_8 = GLFW_MOUSE_BUTTON_8,
			BUTTON_LAST = GLFW_MOUSE_BUTTON_LAST,
			BUTTON_LEFT = GLFW_MOUSE_BUTTON_LEFT,
			BUTTON_RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
			BUTTON_MIDDL = GLFW_MOUSE_BUTTON_MIDDLE
		};

		enum Mode
		{
			NORMAL,
			HIDDEN,
			DISABLED
		};

		enum Action
		{
			RELEASE,
			PRESS,
			REPEAT
		};

		static Vector2<float> getPosition() { return pos; }
		
		static bool isEntered() { return isEnter; }

		static bool getButtonCallBack(Button button, Action action);
	
		static Vector2<float> getScroll() { return scroll; }
	};
}
#endif // !MOUSE
