#pragma once
#include <iostream>
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

#ifdef PYS_PLATFORM_WINDOWS

#endif

#define LOG(...) std::cout << __VA_ARGS__ << std::endl;

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__,__LINE__))

static void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* func, const char* file, int line) {
	while (GLenum error = glGetError()) {
		LOG("[OpenGL Error] (" << error << "):" << func <<
			" " << file << ":" << line);
		return false;
	}
	return true;
}

