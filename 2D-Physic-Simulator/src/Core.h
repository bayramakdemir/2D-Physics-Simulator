#pragma once
#include <iostream>

#ifdef PYS_PLATFORM_WINDOWS
#ifdef PYS_BUILD_DLL
#define SIMULATOR_API __declspec(dllexport)
#else       
#define SIMULATOR_API __declspec(dllimport)   
#endif
#else
#error 2D simulator supports only windows
#endif

#define LOG(...) std::cout << __VA_ARGS__ << std::endl;