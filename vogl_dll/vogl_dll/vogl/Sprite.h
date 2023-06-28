#pragma once

#ifndef SPRITE
#define SPRITE

#include"RectangleType.h"
#include"Texture.h"

namespace vogl
{
	EXTERN class API Sprite : public RectangleType
	{
		friend class RenderWindow;
	private:
		GLfloat vertices[16] =
		{
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 1.0f
		};
		GLuint indices[6] =
		{
			0, 1, 3,
			1, 2, 3 
		};
		GLuint* texture;
		Vector4<float> tile;
		Vector2<float> textureSize;

	public:
		Sprite(Texture& texture, Vector4<float> rect);

		Sprite(Texture& texture);

		Sprite();

		void loadFromTexture(Texture& texture);

		void loadFromTexture(Texture& texture, Vector4<float> rect);

		void setTextureRect(Vector4<float> rect);

		Vector4<float> getTextureRect();
	private:
		void updateModel() override;

		void drawMethod(Vector4<float> rendView, unsigned int slot = 0) override;
	};
}
#endif // !SPRITE