#include "View.h"

void vogl::View::update()
{
	//Vector2<float> center=Vector2<float>(view.x/2.f)
	updateView.x = view.x * (1.0f + zoom);
	updateView.y = view.y * (1.0f + zoom);
	updateView.z = view.z * (1.0f - zoom);
	updateView.w = view.w * (1.0f - zoom);

	//updateView.x = view.z / 2.f;
	//updateView.y = view.w / 2.f;
}

vogl::View::View()
{
	view = 0.f;
}
void vogl::View::setPosition(Vector2<float> vec)
{
	view = Vector4<float>(vec.x, vec.y, view.z, view.w); 
	update();
}

void vogl::View::setPosition(float x, float y)
{
	view = Vector4<float>(x, y, view.z, view.w); 
	update();
}

vogl::View::View(Vector4<float> view)
{
	this->view = view;
	update();
}

void vogl::View::setCenter(Vector2<float> vec)
{
	setCenter(vec.x, vec.y);
}

void vogl::View::setCenter(float x, float y)
{
	updateView.x = x - updateView.z / 2.f;
	updateView.y = y - updateView.w / 2.f;
}

void vogl::View::setSize(Vector2<float> size)
{
	view = Vector4<float>(Vector2<float>(view.x, view.y), size);
	update();
}

void vogl::View::setSize(float x, float y)
{
	view = Vector4<float>(Vector2<float>(view.x, view.y), Vector2<float>(x, y));
	update();
}

void vogl::View::setZoom(float zoom)
{
	if (!std::abs(zoom) < 1.0f)
	{
		this->zoom = zoom;
	}
	update();
}

float vogl::View::getZoom() const
{
	return zoom;
}

void vogl::View::addZoom(float add)
{
	if (zoom + add < 1.0f and zoom + add > -1.0f)
	{
		zoom += add;
	}
	update();
}
