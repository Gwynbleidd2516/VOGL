#pragma once
#include"GL/glew.h"
#include"GLFW/glfw3.h"
#include"Vector.h"
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#define PRINTF(x) std::cout<<x<<std::endl
#define PRINT(x) std::cout<<x
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCAll(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);