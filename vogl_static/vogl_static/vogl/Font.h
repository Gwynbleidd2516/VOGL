#pragma once
#ifndef FONT
#define FONT

#include"Tools.h"
#include<string>
#include<freetype/freetype.h>
#include<vector>
#include FT_FREETYPE_H

namespace vogl
{
	class Font
	{
		friend class Text;
	private:
		FT_Library ft;
		FT_Face face;

		void loadChar(char symb, Vector2<float> size, Vector2<int>& indexSize);
#ifdef GET_ACCESS
	public:
#endif // DEBUGET_ACCESSG
		GLuint texture;
	
	public:
		Font();

		Font(std::string path);

		bool loadFromFile(std::string path);

		~Font();
	};
}
#endif // !FONT
