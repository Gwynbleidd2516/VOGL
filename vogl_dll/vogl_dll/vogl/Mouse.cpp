#include "Mouse.h"

vogl::Vector2<float> vogl::Mouse::pos;
vogl::Vector2<float> vogl::Mouse::scroll;
bool vogl::Mouse::isEnter;
GLFWwindow** vogl::Mouse::window;


void vogl::Mouse::cursorPosCallBack(GLFWwindow* window, double x, double y)
{
	pos = Vector2<float>(x, y);
}

void vogl::Mouse::scrollCallBack(GLFWwindow* window, double xoffset, double yoffset)
{
	scroll = Vector2<float>(xoffset, yoffset);
}

void vogl::Mouse::cursorEnterCallBack(GLFWwindow* window, int entered)
{
	isEnter = entered;
}

bool vogl::Mouse::getButtonCallBack(Button button, Action action)
{
	return glfwGetMouseButton(*window, (int)button) == (int)action;
}