#include "KeyboardEvent.h"
GLFWwindow** vogl::KeyboardEvent::window;

bool vogl::KeyboardEvent::getKeyCallback(Key key, Action action)
{
	return glfwGetKey(*window, (int)key) == (int)action;
}