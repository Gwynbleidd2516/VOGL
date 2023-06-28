#include "Texture.h"
//#include"soil/SOIL/SOIL.h"
#include"stb_image.h"

vogl::Texture::Texture(const std::string path)
{
	if (path != "\0")
	{
		loadFromFile(path);
	}
}

void vogl::Texture::loadFromString(unsigned char* stream, Vector2<int> size)
{
	data = stream;
	this->size = size;
	GLCAll(glGenTextures(1, &texture));
	GLCAll(glBindTexture(GL_TEXTURE_2D, texture));

	GLCAll(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCAll(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCAll(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCAll(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

	GLCAll(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	GLCAll(glGenerateMipmap(GL_TEXTURE_2D));
	GLCAll(glBindTexture(GL_TEXTURE_2D, 0));
}

bool vogl::Texture::loadFromFile(const std::string path)
{
	stbi_set_flip_vertically_on_load(0);
	int width, height;
	data = stbi_load(path.c_str(), &width, &height, &channel, STBI_rgb_alpha);
	if (data == NULL)
	{
#ifdef SHOW_ERROR
		std::cout << "Texture is not loaded: " << path << std::endl;
#endif
		return false;
	}
	loadFromString(data, Vector2<int>(width, height));
	stbi_image_free(data);
	return true;
}

vogl::Vector2<int> vogl::Texture::getSize()
{
	return size;
}

vogl::Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}
