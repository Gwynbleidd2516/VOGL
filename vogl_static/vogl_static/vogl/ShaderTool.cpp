#include "ShaderTool.h"

bool vogl::ShaderTool::loadFromString(const char* vertexStr, const char* fragmentStr)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexStr, NULL);
	glCompileShader(vertexShader);

	GLint success;
	GLchar log[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
#ifdef SHOW_ERROR
		glGetShaderInfoLog(vertexShader, 512, NULL, log);
		std::cout << "Failed to compile vertex shader -> " << log << std::endl;
#endif
		return false;
	}

	GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentStr, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
#ifdef SHOW_ERROR
		glGetShaderInfoLog(fragmentShader, 512, NULL, log);
		std::cout << "Failed to compile fragment shader -> " << log << std::endl;
#endif
		return false;
	}
	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, 512, NULL, log);
		std::cout << "Failed to link program -> " << log << std::endl;

		return false;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return true;
}

bool vogl::ShaderTool::loadFromFile(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexStr = parse(vertexFile);
	std::string fragmentStr = parse(fragmentFile);
	if (vertexStr == "\0" or fragmentStr == "\0")
	{
		return false;
	}
	return loadFromString(vertexStr.c_str(), fragmentStr.c_str());;
}

void vogl::ShaderTool::bind() const
{
	glUseProgram(id);
}

void vogl::ShaderTool::unbind() const
{
	glUseProgram(0);
}

vogl::ShaderTool::~ShaderTool()
{
	glDeleteProgram(id);
}

bool vogl::ShaderTool::setUniform1i(const char* name, int vec)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniform1i(location, vec);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniform2i(const char* name, Vector2<int> vec)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniform2i(location, vec.x, vec.y);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniform3i(const char* name, Vector3<int> vec)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniform3i(location, vec.x, vec.y, vec.z);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniform4i(const char* name, Vector4<int> vec)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniform4i(location, vec.x, vec.y, vec.z, vec.w);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniform1f(const char* name, float vec)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniform1f(location, vec);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniform2f(const char* name, Vector2<float> vec)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniform2f(location, vec.x, vec.y);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniform3f(const char* name, Vector3<float> vec)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniform3f(location, vec.x, vec.y, vec.z);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniform4f(const char* name, Vector4<float> vec)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniform2f(const char* name, glm::vec2 vec)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniform2f(location, vec.x, vec.y);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniform3f(const char* name, glm::vec3 vec)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniform3f(location, vec.x, vec.y, vec.z);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniform4f(const char* name, glm::vec4 vec)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniform1ui(const char* name, unsigned int vec)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniform1ui(location, vec);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniform2ui(const char* name, Vector2<unsigned int> vec)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniform2ui(location, vec.x, vec.y);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniform3ui(const char* name, Vector3<unsigned int> vec)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniform3ui(location, vec.x, vec.y, vec.z);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniform4ui(const char* name, Vector4<unsigned int> vec)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniform4ui(location, vec.x, vec.y, vec.z, vec.w);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniformMat2f(const char* name, const glm::mat2& mat)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniformMatrix2fv(location, 1, GL_FALSE, &mat[0][0]);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniformMat3f(const char* name, const glm::mat3& mat)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniformMat4f(const char* name, const glm::mat4& mat) const
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniformMat2x3f(const char* name, const glm::mat2x3& mat)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniformMatrix2x3fv(location, 1, GL_FALSE, &mat[0][0]);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniformMat3x2f(const char* name, const glm::mat3x2& mat)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniformMatrix3x2fv(location, 1, GL_FALSE, &mat[0][0]);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniformMat2x4f(const char* name, const glm::mat2x4& mat)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniformMatrix2x4fv(location, 1, GL_FALSE, &mat[0][0]);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniformMat4x2f(const char* name, const glm::mat4x2& mat)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniformMatrix4x2fv(location, 1, GL_FALSE, &mat[0][0]);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniformMat3x4f(const char* name, const glm::mat3x4& mat)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniformMatrix3x4fv(location, 1, GL_FALSE, &mat[0][0]);
	unbind();
	return true;
}

bool vogl::ShaderTool::setUniformMat4x3f(const char* name, const glm::mat4x3& mat)
{
	GLint location = glGetUniformLocation(id, name);
	if (location == -1)
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return true;
	}
	bind();
	glUniformMatrix4x3fv(location, 1, GL_FALSE, &mat[0][0]);
	unbind();
	return true;
}

std::string vogl::ShaderTool::parse(const char* filepath)
{
	std::stringstream ss;
	std::string buff;
	std::ifstream file;
	file.open(filepath);
	if (!file.is_open())
	{
#ifdef SHOW_ERROR
		std::cout << "Uniform \"" << name << "\" is not found!" << std::endl;
#endif
		return "\0";
	}
	while (getline(file, buff))
	{
		ss << buff << "\n";
	}
	file.close();
	return ss.str();
}