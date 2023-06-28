#include "Shader.h"

void vogl::Shader::bind() const
{
	glUseProgram(id);
}

void vogl::Shader::unbind() const
{
	glUseProgram(0);
}