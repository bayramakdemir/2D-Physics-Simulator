#pragma once
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "../Core.h"

namespace Simulator {
	class SIMULATOR_API WindowsWindow{
	public:
		WindowsWindow();
		~WindowsWindow();
		GLFWwindow* CreateWindow();
	};

}


