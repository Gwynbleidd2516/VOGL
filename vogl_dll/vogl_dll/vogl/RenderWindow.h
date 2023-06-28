#pragma once
#ifndef RENDER_WINDOW
#define RENDER_WINDOW

#include"tools.h"
#include<vector>
#include"Rectangle.h"
#include"KeyboardEvent.h"
#include"Mouse.h"
#include"View.h"
#include"Sprite.h"

namespace vogl
{
	EXTERN struct API WindowSettings
	{
	private:
		std::vector<int> settings;
	public:
		void push(int hint, int value)
		{
			settings.push_back(hint);
			settings.push_back(value);
		}
	private:
		void setUp()
		{
			for (int i = 0; i < settings.size(); i += 2)
			{
				glfwWindowHint(settings[i], settings[i + 1]);
			}
		}
	};

	enum class Style
	{
		None,
		Fullscreen,
		FullTitlebar,
		CloseButton
	};

	EXTERN class API RenderWindow
	{
	private:
		Style style;
		Vector2<int> size;
		Vector4<float> view;
		bool usedView = false;
		float zoom = 0.0f;
#ifdef GET_ACCESS
	public:
#endif // DEBUGET_ACCESSG
		GLFWwindow* window;

	public:
		RenderWindow(Vector2<int> windowSize, const char* name, bool resize = true, Style style = Style::FullTitlebar);

		RenderWindow();

		~RenderWindow();

		void setFrameRate(float fps);

		void setWindow(Vector2<int> windowSize, const char* name, bool resize = true, Style style = Style::FullTitlebar);

		Vector2<int> getSize();

		void clear(Vector4<float> color = Vector4<float>(0.0f, 0.0f, 0.0f, 1.0f)) const;

		void draw(DrawObject& rect) const;

		void draw(Sprite& rect, unsigned int slot = 0) const;

		void display() const;

		bool shouldClose() const;

		void pollEvents();

		void makeContextCurrent() const;

		void setMouseMode(vogl::Mouse::Mode mode);

		void close();

		void setView(const View& v);
	};
}

#endif // !RENDER_WINDOW