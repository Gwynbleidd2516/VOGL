#pragma once

#ifndef SHADER
#define SHADER

#include"ShaderTool.h"

namespace vogl
{
	EXTERN class API Shader :public ShaderTool
	{
	public:
		void bind() const;

		void unbind() const;
	};
}
#endif // !SHADER