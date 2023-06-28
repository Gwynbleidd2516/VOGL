#include "Font.h"

vogl::Font::Font()
{
	if (FT_Init_FreeType(&ft))
	{
#ifdef SHOW_ERROR
		std::cout << "Failed to init freetype!" << std::endl;
#endif
	}
}

void vogl::Font::loadChar(char symb, Vector2<float> size, Vector2<int>& indexSize)
{
	FT_Set_Pixel_Sizes(face, size.x, size.y);
	if (FT_Load_Char(face, symb, FT_LOAD_RENDER))
	{
#ifdef SHOW_ERROR
		std::cout << "Failed to load Glyph " << symb << std::endl;
#endif
	}
	indexSize = Vector2<int>(face->glyph->bitmap.width, face->glyph->bitmap.rows);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
	GLCAll(glGenerateMipmap(GL_TEXTURE_2D));
	GLCAll(glBindTexture(GL_TEXTURE_2D, 0));

}

vogl::Font::Font(std::string path)
{
	if (FT_Init_FreeType(&ft))
	{
#ifdef SHOW_ERROR
		std::cout << "Failed to init freetype!" << std::endl;
#endif
	}
	loadFromFile(path);
}

bool vogl::Font::loadFromFile(std::string path)
{
	if (FT_New_Face(ft, path.c_str(), 0, &face))
	{
#ifdef SHOW_ERROR
		std::cout << "Failed to load font" << std::endl;
#endif
		return false;
	}
	FT_Set_Pixel_Sizes(face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	GLCAll(glGenTextures(1, &texture));
	GLCAll(glBindTexture(GL_TEXTURE_2D, texture));

	GLCAll(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCAll(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCAll(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCAll(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	return true;
}

vogl::Font::~Font()
{
	FT_Done_FreeType(ft);
	FT_Done_Face(face);
}
