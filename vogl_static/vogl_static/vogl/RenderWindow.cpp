#include "RenderWindow.h"

vogl::RenderWindow::RenderWindow(Vector2<int> windowSize, const char* name, bool resize, Style style)
{
	setWindow(windowSize, name, resize, style);
}

vogl::RenderWindow::RenderWindow()
{
}

vogl::RenderWindow::~RenderWindow()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void vogl::RenderWindow::setFrameRate(float fps)
{
	glfwSwapInterval(fps / 60.f);
}

void vogl::RenderWindow::setWindow(Vector2<int> windowSize, const char* name, bool resize, Style style)
{
	if (!glfwInit())
	{
#ifdef SHOW_ERROR
		std::cout << "Failed to init the glfw!" << std::endl;
#endif
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, resize);
	switch (style)
	{
	case vogl::Style::None:
		glfwWindowHint(GLFW_DECORATED, GL_FALSE);
		break;
	case vogl::Style::Fullscreen:
		glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
		break;
	case vogl::Style::FullTitlebar:
		glfwWindowHint(GLFW_DECORATED, GL_TRUE);
		break;
	case vogl::Style::CloseButton:
		break;
	default:
		break;
	}
	window = glfwCreateWindow(windowSize.x, windowSize.y, name, nullptr, nullptr);
	
	if (!window)
	{
#ifdef SHOW_ERROR
		std::cout << "Failed to create window!" << std::endl;
#endif		
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
#ifdef SHOW_ERROR
		std::cout << "Failed to init the glew! " << glewGetErrorString(glewError) << std::endl;
#endif		
		exit(EXIT_FAILURE);
	}

	glfwGetFramebufferSize(window, &size.x, &size.y);
	glViewport(0, 0, size.x, size.y);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

vogl::Vector2<int> vogl::RenderWindow::getSize()
{
	return size;
}

void vogl::RenderWindow::clear(Vector4<float> color) const
{
	glClearColor(color.x, color.y, color.z, color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void vogl::RenderWindow::draw(DrawObject& rect) const
{
	if (usedView)
		rect.drawMethod(view);
	else
		rect.drawMethod(Vector4<float>(0.0f, 0.0f, size.x, size.y));
}

void vogl::RenderWindow::draw(Sprite& rect, unsigned int slot) const
{
	if (usedView)
		rect.drawMethod(view, slot);
	else
		rect.drawMethod(Vector4<float>(0.0f, 0.0f, size.x, size.y), slot);

}

void vogl::RenderWindow::display() const
{
	glfwSwapBuffers(window);
}

bool vogl::RenderWindow::shouldClose() const
{
	return glfwWindowShouldClose(window);
}

void vogl::RenderWindow::pollEvents()
{
	usedView = false;
	KeyboardEvent::window = &this->window;
	Mouse::window = &this->window;
	glfwSetCursorPosCallback(window, Mouse::cursorPosCallBack);
	glfwSetCursorEnterCallback(window, Mouse::cursorEnterCallBack);
	glfwSetScrollCallback(window, Mouse::scrollCallBack);
	glfwPollEvents();
}

void vogl::RenderWindow::makeContextCurrent() const
{
	glfwMakeContextCurrent(window);
}

void vogl::RenderWindow::setMouseMode(vogl::Mouse::Mode mode)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL + (int)mode);
}

void vogl::RenderWindow::close()
{
	glfwSetWindowShouldClose(window, 1);
}

void vogl::RenderWindow::setView(const View& v)
{
	usedView = true;
	view = Vector4<float>(v.getPosition(), v.getSize());
	zoom = v.getZoom();
}
