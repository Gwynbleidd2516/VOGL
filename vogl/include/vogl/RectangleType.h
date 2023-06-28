#pragma once

#include"DrawObject.h"

namespace vogl
{
	class API RectangleType :public DrawObject
	{
	protected:
		Vector2<float> size;
	public:
		void setSize(Vector2<float> size) { this->size = size; updateModel(); }

		void setSize(float x, float y) { this->size = Vector2<float>(x, y); updateModel(); }

		void setSize(Vector2<double> size) { this->size = Vector2<float>(size.x, size.y); updateModel(); }

		void setSize(double x, double y) { this->size = Vector2<float>(x, y); updateModel(); }

		Vector2<float> getSize() const { return size; }
	};
}