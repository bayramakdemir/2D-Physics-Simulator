#pragma once
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "../Core.h"

namespace Simulator {
	class WindowsWindow{
	public:
		WindowsWindow();
		~WindowsWindow();
		GLFWwindow* CreateWindow();
	};

}


