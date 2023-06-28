#include "ShaderShape.h"

vogl::ShaderShape::ShaderShape(Vector2<float> size)
{
	shader.~Shader();
	this->size = size;
	for (int i = 0; i < 8; i += 2)
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
}

void vogl::ShaderShape::updateModel()
{
	vertices[0] = (1.0f - zeroCoords.x) * size.x * scale.x;
	vertices[1] = (1.0f - zeroCoords.y) * size.y * scale.y;
	vertices[2] = (1.0f - zeroCoords.x) * size.x * scale.x;
	vertices[3] = -zeroCoords.y * size.y * scale.y;
	vertices[4] = -zeroCoords.x * size.x * scale.x;
	vertices[5] = -zeroCoords.y * size.y * scale.y;
	vertices[6] = -zeroCoords.x * size.x * scale.x;
	vertices[7] = (1.0f - zeroCoords.y) * size.y * scale.y;
}

void vogl::ShaderShape::drawMethod(Vector4<float> rendView, unsigned int slot)
{
	glm::mat4 model, mvp, projection, view;
	projection = glm::ortho(0.0f, rendView.z, rendView.w, 0.0f, -1.0f, 1.0f);
	view = glm::translate(glm::mat4(1.0f), glm::vec3(-rendView.x, -rendView.y, 0));
	model = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0));
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 0, 1));
	mvp = projection * view * model;

	setUniformMat4f("u_MVP", mvp);
	//shader.setUniform1f("u_Zoom", zoom);

	bind();
	bindVertexArray();
	bindIndexBuffer();
	GLCAll(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
	unbind();
	unbindVertexArray();
	unbindIndexBuffer();
}
