#pragma once
struct GLFWwindow;

namespace Simulator {
	class WindowsWindow{
	public:
		WindowsWindow();
		~WindowsWindow();
		GLFWwindow* CreateWindow(int width = 640, int height = 480);
	};

}


