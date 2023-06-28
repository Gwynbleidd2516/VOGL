#include "Text.h"

void vogl::Text::updateModel()
{
	vertices[0] = (1.0f - zeroCoords.x) * face->glyph->bitmap.width * scale.x;
	vertices[1] = (1.0f - zeroCoords.y) * face->glyph->bitmap.rows * scale.y;

	vertices[4] = (1.0f - zeroCoords.x) * face->glyph->bitmap.width * scale.x;
	vertices[5] = -zeroCoords.y * face->glyph->bitmap.rows * scale.y;

	vertices[8] = -zeroCoords.x * face->glyph->bitmap.width * scale.x;
	vertices[9] = -zeroCoords.y * face->glyph->bitmap.rows * scale.y;

	vertices[12] = -zeroCoords.x * face->glyph->bitmap.width * scale.x;
	vertices[13] = (1.0f - zeroCoords.y) * face->glyph->bitmap.rows * scale.y;

	bindVertexBuffer();
	GLCAll(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(float), vertices, GL_DYNAMIC_DRAW));
	unbindVertexBuffer();
	shader.setUniform4f("inputColor", color);
}

void vogl::Text::loadChar(wchar_t symb, Vector2<float> size)
{
	FT_Set_Pixel_Sizes(face, size.x, size.y);
	if (FT_Load_Char(face, symb, FT_LOAD_RENDER))
	{
#ifdef SHOW_ERROR
		std::cout << "Failed to load Glyph " << symb << std::endl;
#endif
	}
	face->style_flags = FT_STYLE_FLAG_BOLD;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
	GLCAll(glGenerateMipmap(GL_TEXTURE_2D));
	GLCAll(glBindTexture(GL_TEXTURE_2D, 0));

}

void vogl::Text::drawMethod(Vector4<float> rendView, unsigned int slot)
{
	glm::mat4 model, mvp, projection, view;
	projection = glm::ortho(0.0f, rendView.z, rendView.w, 0.0f, -1.0f, 1.0f);

	unsigned int max_yoffset = 0;

	for (auto& x : string)
	{
		loadChar(x, size * scale);
		max_yoffset = std::max(max_yoffset, face->glyph->bitmap.rows);
	}

	view = glm::translate(glm::mat4(1.0f), glm::vec3(-rendView.x, -rendView.y, 0));
	float x_interval = 0, y_interval = 0;
	int j = 0;

	for (int i = 0; i < string.length(); i++)
	{
		loadChar(string[i], size * scale);
		updateModel();

		if (string[i] == '\n')
		{
			j++;
			max_yoffset += max_yoffset / j;
			x_interval = 0;
			continue;
		}

		
		y_interval = -face->glyph->bitmap_top + max_yoffset;
		
		setZeroCoords(-x_interval / face->glyph->bitmap.width, -y_interval / face->glyph->bitmap.rows);
		
		model = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0));
		model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 0, 1));
		mvp = projection * view * model;
		
		x_interval += face->glyph->bitmap.width + face->glyph->bitmap_left;

		shader.setUniformMat4f("u_MVP", mvp);
		//shader.setUniform1f("u_Zoom", zoom);

		shader.setUniform1i("u_Texture", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *texture);

		shader.bind();
		bindVertexArray();
		GLCAll(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
		shader.unbind();
		unbindVertexArray();
	}

}

vogl::Text::Text()
{
}

vogl::Text::Text(Font& font, std::wstring str)
{
	setFont(font);
	setString(str);
	size = Vector2<float>(0.f, 48.f);
	const GLchar* vertexShaderSource =
		"#version 410 core\n"
		"layout (location = 0) in vec2 vertex;\n"
		"layout (location = 1) in vec2 texCoords;\n"
		""
		"uniform mat4 u_MVP;\n"
		"uniform float u_Zoom;\n"
		""
		"out vec2 TexCoord;\n"
		""
		"void main()\n"
		"{\n"
		"gl_Position = u_MVP * vec4(vertex, 0.0f, 1.0f);\n"
		"TexCoord = texCoords;\n"
		"}\0";
	const GLchar* fragmentShaderSource =
		"#version 410 core\n"
		"out vec4 color;\n"
		""
		"in vec2 TexCoord;\n"
		""
		"uniform vec4 inputColor;\n"
		"uniform sampler2D u_Texture;\n"
		""
		"void main()\n"
		"{\n"
		"color = vec4(1.0f,1.0f,1.0f, texture(u_Texture, TexCoord).r) * inputColor;\n"
		"}\0";
	GLCAll(glGenVertexArrays(1, &va));
	GLCAll(glGenBuffers(1, &vb));
	GLCAll(glGenBuffers(1, &ib));

	GLCAll(glBindVertexArray(va));

	GLCAll(glBindBuffer(GL_ARRAY_BUFFER, vb));
	GLCAll(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(float), vertices, GL_DYNAMIC_DRAW));


	GLCAll(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib));
	GLCAll(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

	GLCAll(glEnableVertexAttribArray(0));
	GLCAll(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0));
	GLCAll(glEnableVertexAttribArray(1));
	GLCAll(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(2 * sizeof(float))));
	unbindVertexArray();
	unbindIndexBuffer();
	unbindVertexBuffer();
	shader.loadFromString(vertexShaderSource, fragmentShaderSource);
	shader.setUniform4f("inputColor", color);
	shader.unbind();

	setSize(Vector2<float>(0, 48) * scale);
}

void vogl::Text::setFont(Font& font)
{
	face = font.face;
	texture = &font.texture;
}

void vogl::Text::setString(std::wstring str)
{
	string = str;
	isSizeKnown = false;
}

std::wstring vogl::Text::getString()
{
	return string;
}

vogl::Vector2<float> vogl::Text::getSize()
{
	Vector2<float> returnable = 0.0f;

	if (!isSizeKnown)
	{
		Vector2<float> buff = 0.0f;
		for (int i = 0; i < string.size(); i++)
		{
			loadChar(string[i], size * scale);
			if (string[i] == '\n' or i == string.size()-1)
			{
				returnable.x = std::max(returnable.x, buff.x);
				returnable.y += buff.y;
				buff = 0.0f;
			}
			else
			{
				buff.x += face->glyph->bitmap.width + face->glyph->bitmap_left;
				buff.y = std::max(buff.y, (float)face->glyph->bitmap.rows);
			}
		}
		isSizeKnown = true;
		strSize = returnable;
	}
	return strSize;
}

