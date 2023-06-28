#include "Sprite.h"

vogl::Sprite::Sprite(Texture& texture, Vector4<float> rect)
{
	loadFromTexture(texture, rect);
}

vogl::Sprite::Sprite(Texture& texture)
{
	loadFromTexture(texture);
}

vogl::Sprite::Sprite()
{
}

void vogl::Sprite::loadFromTexture(Texture& texture)
{
	this->size = Vector2<float>(texture.size.x, texture.size.y);
	this->texture = &texture.texture;
	textureSize = size;
	tile = Vector4<float>(Vector2<float>(0, 0), size);
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
		"color = texture(u_Texture, TexCoord)*inputColor;\n"
		"}\0";
	for (int i = 0; i < 16; i += 4)
	{
		vertices[i] *= size.x;
		vertices[i + 1] *= size.y;
	}
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

}

void vogl::Sprite::loadFromTexture(Texture& texture, Vector4<float> rect)
{
	loadFromTexture(texture);
	setTextureRect(rect);
}

void vogl::Sprite::setTextureRect(Vector4<float> rect)
{
	tile = rect;
	updateModel();
}

vogl::Vector4<float> vogl::Sprite::getTextureRect()
{
	return tile;
}

void vogl::Sprite::updateModel()
{
	vertices[0] = (1.0f - zeroCoords.x) * size.x * scale.x;
	vertices[1] = (1.0f - zeroCoords.y) * size.y * scale.y;

	vertices[2] = tile.z / textureSize.x;
	vertices[3] = tile.w / textureSize.y;

	vertices[4] = (1.0f - zeroCoords.x) * size.x * scale.x;
	vertices[5] = -zeroCoords.y * size.y * scale.y;

	vertices[6] = tile.z / textureSize.x;
	vertices[7] = tile.y / textureSize.y;

	vertices[8] = -zeroCoords.x * size.x * scale.x;
	vertices[9] = -zeroCoords.y * size.y * scale.y;

	vertices[10] = tile.x / textureSize.x;
	vertices[11] = tile.y / textureSize.y;

	vertices[12] = -zeroCoords.x * size.x * scale.x;
	vertices[13] = (1.0f - zeroCoords.y) * size.y * scale.y;

	vertices[14] = tile.x / textureSize.x;
	vertices[15] = tile.w / textureSize.y;

	bindVertexBuffer();
	GLCAll(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(float), vertices, GL_DYNAMIC_DRAW));
	unbindVertexBuffer();
	shader.setUniform4f("inputColor", color);
}

void vogl::Sprite::drawMethod(Vector4<float> rendView, unsigned int slot)
{
	glm::mat4 model, mvp, projection, view;
	projection = glm::ortho(0.0f, rendView.z, rendView.w, 0.0f, -1.0f, 1.0f);

	view = glm::translate(glm::mat4(1.0f), glm::vec3(-rendView.x, -rendView.y, 0));
	model = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0));
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 0, 1));
	mvp = projection * view * model;

	shader.setUniformMat4f("u_MVP", mvp);
	//shader.setUniform1f("u_Zoom", zoom);
	if (slot < 31)
	{
		shader.setUniform1i("u_Texture", slot);
		glActiveTexture(GL_TEXTURE0 + slot);
	}
	else
	{
		shader.setUniform1i("u_Texture", 0);
		glActiveTexture(GL_TEXTURE0);
	}
	glBindTexture(GL_TEXTURE_2D, *texture);

	shader.bind();
	bindVertexArray();
	GLCAll(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
	shader.unbind();
	unbindVertexArray();
}
