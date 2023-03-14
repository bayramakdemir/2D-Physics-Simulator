#pragma once
#include <iostream>

#ifdef PYS_PLATFORM_WINDOWS

#endif

#define LOG(...) std::cout << __VA_ARGS__ << std::endl;