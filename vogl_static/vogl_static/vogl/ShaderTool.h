#pragma once

#ifndef SHADERTOOL
#define SHADERTOOL

#include"domain.h"
#include<fstream>
#include<string>
#include<sstream>

namespace vogl
{
	class ShaderTool
	{
	protected:
		unsigned int id;

		void bind() const;

		void unbind() const;
	public:
		bool loadFromString(const char* vertexStr, const char* fragmentStr);

		bool loadFromFile(const char* vertexFile, const char* fragmentFile);

		~ShaderTool();

		bool setUniform1i(const char* name, int vec);

		bool setUniform2i(const char* name, Vector2<int> vec);

		bool setUniform3i(const char* name, Vector3<int> vec);

		bool setUniform4i(const char* name, Vector4<int> vec);

		bool setUniform1f(const char* name, float vec);

		bool setUniform2f(const char* name, Vector2<float> vec);

		bool setUniform3f(const char* name, Vector3<float> vec);

		bool setUniform4f(const char* name, Vector4<float> vec);

		bool setUniform2f(const char* name, glm::vec2 vec);

		bool setUniform3f(const char* name, glm::vec3 vec);

		bool setUniform4f(const char* name, glm::vec4 vec);

		bool setUniform1ui(const char* name, unsigned int vec);

		bool setUniform2ui(const char* name, Vector2<unsigned int> vec);

		bool setUniform3ui(const char* name, Vector3<unsigned int> vec);

		bool setUniform4ui(const char* name, Vector4<unsigned int> vec);

		bool setUniformMat2f(const char* name, const glm::mat2& mat);

		bool setUniformMat3f(const char* name, const glm::mat3& mat);

		bool setUniformMat4f(const char* name, const glm::mat4& mat) const;

		bool setUniformMat2x3f(const char* name, const glm::mat2x3& mat);

		bool setUniformMat3x2f(const char* name, const glm::mat3x2& mat);

		bool setUniformMat2x4f(const char* name, const glm::mat2x4& mat);

		bool setUniformMat4x2f(const char* name, const glm::mat4x2& mat);

		bool setUniformMat3x4f(const char* name, const glm::mat3x4& mat);

		bool setUniformMat4x3f(const char* name, const glm::mat4x3& mat);

	private:
		std::string parse(const char* filepath);
	};
}
#endif // !SHADERTOOL
