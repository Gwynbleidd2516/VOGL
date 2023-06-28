#pragma once
#ifndef TEXT
#define TEXT

#include"RectangleType.h"
#include"Font.h"
#include<math.h>

namespace vogl
{
	class API Text:public RectangleType
	{
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
		const float pi = 3.1415926535f;
		GLuint* texture;
		Vector2<int> indexSize;
		std::wstring string;
		FT_Face face;
		Vector2<float> textureSize;
		bool isSizeKnown = false;
		Vector2<float> strSize = 0.0f;

		void updateModel() override;

		void drawMethod(Vector4<float> rendView, unsigned int slot = 0) override;

		void loadChar(wchar_t symb, Vector2<float> size);
	public:
		Text();

		Text(Font& font, std::wstring str);

		void setFont(Font& font);

		void setString(std::wstring str);

		std::wstring getString();

		Vector2<float> getSize();
	};
}
#endif // !TEXT