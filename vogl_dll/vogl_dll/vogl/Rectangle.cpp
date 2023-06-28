#include "Rectangle.h"

vogl::Rectangle::Rectangle(Vector2<float> size)
{
	this->size = size;
	const GLchar* vertexShaderSource =
		"#version 410 core\n"
		"layout (location = 0) in vec2 vertex;\n"
		"uniform mat4 u_MVP;\n"
		"uniform float u_Zoom;"
		"void main()\n"
		"{\n"
		"gl_Position = u_MVP * vec4(vertex, u_Zoom, 1.0f);\n"
		"}\0";
	const GLchar* fragmentShaderSource =
		"#version 410 core\n"
		"out vec4 color;\n"
		"uniform vec4 inputColor;\n"
		"void main()\n"
		"{\n"
		"color = inputColor;\n"
		"}\0";
	for (int i = 0; i < 8; i+=2)
	{
		vertices[i] *= size.x;
		vertices[i + 1] *= size.y;
	}
	GLCAll(glGenBuffers(1, &vb));
	GLCAll(glBindBuffer(GL_ARRAY_BUFFER, vb));
	GLCAll(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(float), vertices, GL_DYNAMIC_DRAW));

	GLCAll(glGenVertexArrays(1, &va));

	GLCAll(glGenBuffers(1, &ib));
	GLCAll(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib));
	GLCAll(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW));

	bindVertexArray();
	bindVertexBuffer();
	GLCAll(glEnableVertexAttribArray(0));
	GLCAll(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
	unbindVertexArray();
	unbindIndexBuffer();
	unbindVertexBuffer();
	shader.loadFromString(vertexShaderSource, fragmentShaderSource);
	shader.setUniform4f("inputColor", color);
	shader.unbind();
}

void vogl::Rectangle::updateModel()
{
	vertices[0] = (1.0f - zeroCoords.x) * size.x * scale.x;
	vertices[1] = (1.0f - zeroCoords.y) * size.y * scale.y;
	vertices[2] = (1.0f - zeroCoords.x) * size.x * scale.x;
	vertices[3] = -zeroCoords.y * size.y * scale.y;
	vertices[4] = -zeroCoords.x * size.x * scale.x;
	vertices[5] = -zeroCoords.y * size.y * scale.y;
	vertices[6] = -zeroCoords.x * size.x * scale.x;
	vertices[7] = (1.0f - zeroCoords.y) * size.y * scale.y;
	bindVertexBuffer();
	GLCAll(glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertices, GL_DYNAMIC_DRAW));
	unbindVertexBuffer();
	shader.setUniform4f("inputColor", color);
}

void vogl::Rectangle::drawMethod(Vector4<float> rendView, unsigned int slot)
{
	glm::mat4 model, mvp, projection, view;
	projection = glm::ortho(0.0f, rendView.z, rendView.w, 0.0f, -1.0f, 1.0f);
	view = glm::translate(glm::mat4(1.0f), glm::vec3(-rendView.x, -rendView.y, 0));
	model = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0));
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 0, 1));
	mvp = projection * view * model;

	shader.setUniformMat4f("u_MVP", mvp);

	shader.bind();
	bindVertexArray();
	bindIndexBuffer();
	GLCAll(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
	shader.unbind();
	unbindVertexArray();
	unbindIndexBuffer();
}
