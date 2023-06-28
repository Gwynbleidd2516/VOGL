#include "DrawObject.h"

void vogl::DrawObject::bindVertexBuffer() const
{
	GLCAll(glBindBuffer(GL_ARRAY_BUFFER, vb));
}

void vogl::DrawObject::bindVertexArray() const
{
	GLCAll(glBindVertexArray(va));
}

void vogl::DrawObject::bindIndexBuffer() const
{
	GLCAll(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib));
}

void vogl::DrawObject::unbindVertexBuffer() const
{
	GLCAll(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void vogl::DrawObject::unbindVertexArray() const
{
	GLCAll(glBindVertexArray(0));
}

void vogl::DrawObject::unbindIndexBuffer() const
{
	GLCAll(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

vogl::DrawObject::~DrawObject()
{
}
