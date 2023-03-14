#include "Application.h"
#include "../Window/WindowsWindow.h"

void error_callback(int error, const char* description) {
	LOG(description);
}

namespace Simulator {
	Application::Application() {

	};
	Application::~Application() {
	
	};
	void Application::Run() {
		if (!glfwInit()) {
			// Initialization failed
		}
		glfwSetErrorCallback(error_callback);

		WindowsWindow windows_window;
		GLFWwindow* window = windows_window.CreateWindow();


		while (!glfwWindowShouldClose(window)) {
			// Keep running
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwDestroyWindow(window);

	}
}