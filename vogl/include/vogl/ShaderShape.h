#pragma once

#ifndef SHADERSHAPE
#define SHADERSHAPE

#include"ShaderTool.h"
#include"RectangleType.h"

namespace vogl
{
	class API ShaderShape :public ShaderTool, public RectangleType
	{
		GLfloat vertices[8] =
		{
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f
		};
		GLuint indices[6] =
		{
			0, 1, 3,
			1, 2, 3
		};
	public:
		ShaderShape(Vector2<float> size = Vector2<float>(50.0f, 50.0f));

	private:
		void updateModel() override;

		void drawMethod(Vector4<float> rendView, unsigned int slot = 0) override;

	};
}
#endif // !SHADER
