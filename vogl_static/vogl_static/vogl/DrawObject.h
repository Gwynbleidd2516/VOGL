#pragma once

#include"Tools.h"
#include"Shader.h"

namespace vogl
{
	EXTERN class API DrawObject
	{
		friend class RenderWindow;
	protected:
		//VertexBuffer vb;
		//VertexArray va;
		//VertexBufferLayout vbl;
		//IndexBuffer ib;
		Vector2<float> pos = Vector2<float>(0.0, 0.0);
		Vector2<float> scale = Vector2<float>(1.0f, 1.0f);
		Vector4<float> color = Vector4<float>(1.f, 1.f, 1.f, 1.f);
		Vector2<float> zeroCoords = Vector2<float>(0.0f, 0.0f);
		float angle = 0;
		Shader shader;

		void bindVertexBuffer() const;

		void bindVertexArray() const;

		void bindIndexBuffer() const;

		void unbindVertexBuffer() const;

		void unbindVertexArray() const;

		void unbindIndexBuffer() const;
#ifdef GET_ACCESS
	public:
#endif // DEBUGET_ACCESSG
		unsigned int vb;
		unsigned int va;
		unsigned int ib;

	public:

		void setPosition(Vector2<float> position) { pos = position; }

		void setPosition(float x, float y) { pos = Vector2<float>(x, y);}

		void setPosition(Vector2<double> position) { pos = Vector2<float>(position.x, position.y);}

		void setPosition(double x, double y) { pos = Vector2<float>(x, y);}

		void move(Vector2<float> position) { pos += position;}

		void move(float x, float y) { pos += Vector2<float>(x, y);}

		void move(Vector2<double> position) { pos += Vector2<float>(position.x, position.y);}

		void move(double x, double y) { pos += Vector2<float>(x, y);}

		Vector2<float> getPosition() const { return pos; }

		void setScalse(Vector2<float> scale) { this->scale = scale; updateModel(); }

		void setScalse(float x, float y) { this->scale = Vector2<float>(x, y); updateModel(); }

		void setScalse(Vector2<double> scale) { this->scale = Vector2<float>(scale.x, scale.y); updateModel(); }

		void setScalse(double x, double y) { this->scale = Vector2<float>(x, y); updateModel(); }

		void scalse(Vector2<float> scale) { this->scale *= scale; updateModel(); }

		void scalse(float x, float y) { this->scale *= Vector2<float>(x, y); updateModel(); }

		void scalse(Vector2<double> scale) { this->scale *= Vector2<float>(scale.x, scale.y); updateModel(); }

		void scalse(double x, double y) { this->scale *= Vector2<float>(x, y); updateModel(); }

		Vector2<float> getScalse() const { return scale; }

		void setColor(Vector4<float> color) { this->color = color; updateModel(); }

		void setColor(Vector4<unsigned int> color) { this->color = Vector4<float>((float)color.x / 255.0f, (float)color.y / 255.0f, (float)color.z / 255.0f, (float)color.w / 255.0f); updateModel(); }

		Vector4<float> getColor() const { return color; }

		void setRotation(float angle) { this->angle = angle; }

		void rotate(float angle) { this->angle += angle; }

		float getRotation() const { return angle; }

		void setZeroCoords(Vector2<float> procent) { zeroCoords = procent; updateModel(); }

		void setZeroCoords(float x, float y) { zeroCoords = Vector2<float>(x, y); updateModel(); }

		Vector2<float> getZeroCoords() const { return zeroCoords; }

		void operator=(DrawObject& obj)
		{
			pos = obj.pos;
			scale = obj.scale;
			color = obj.color;
			zeroCoords = obj.zeroCoords;
			angle = obj.angle;
			updateModel();
		}
	
		~DrawObject();
	protected:
		virtual void updateModel() = 0;

		virtual void drawMethod(Vector4<float> rendView, unsigned int slot = 0) = 0;

	};
}