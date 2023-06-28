#pragma once

#ifndef TEXTURE
#define TEXTURE

#include"Tools.h"
#include<string>

namespace vogl {

	class API Texture
	{
		friend class Sprite;
	private:
		unsigned char* data;
		Vector2<int> size;
		int channel = 0;
#ifdef GET_ACCESS
	public:
#endif // DEBUGET_ACCESSG
		GLuint texture;

	public:
		Texture(const std::string path = "\0");

		void loadFromString(unsigned char* stream, Vector2<int> size);

		bool loadFromFile(const std::string path);

		Vector2<int> getSize();

		~Texture();
	};
}

#endif // !TEXTURE