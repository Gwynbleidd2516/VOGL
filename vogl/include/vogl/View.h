#pragma once

#ifndef VIEW
#define VIEW

#include"Tools.h"

namespace vogl
{
	class API View
	{
	private:
		Vector4<float> view;
		Vector4<float> updateView;
		float zoom = 0.0f;
		void update();
		Vector2<float> center;

	public:
		View();

		View(Vector4<float> view);

		void setPosition(Vector2<float> vec);

		void setPosition(float x, float y);
		
		Vector2<float> getPosition() const
		{ return Vector2<float>(updateView.x, updateView.y); }

		Vector2<float> getSize() const
		{ return Vector2<float>(updateView.z, updateView.w); }

		void setCenter(Vector2<float> vec);

		void setCenter(float x, float y);

		void setSize(Vector2<float> size);

		void setSize(float x, float y);

		void setZoom(float zoom);

		void addZoom(float add);

		float getZoom() const;
	};
}
#endif // !VIEW
