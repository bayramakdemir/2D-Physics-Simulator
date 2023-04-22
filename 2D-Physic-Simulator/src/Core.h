#pragma once
#include <iostream>
#include "GLEW/glew.h"


#ifdef PYS_PLATFORM_WINDOWS

#endif

#ifdef PYS_RELEASE
	#define LOG(...);
	#define ASSERT(x);
	#define GLCall(x) x;
#else
	#define LOG(...) std::cout << __VA_ARGS__ << std::endl;

	#define ASSERT(x) if (!(x)) __debugbreak();
	#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogCall(#x, __FILE__,__LINE__))

	void GLClearError();
	bool GLLogCall(const char* func, const char* file, int line);
#endif



