#include "WindowsWindow.h"
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "../Core.h"


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

namespace Simulator {
	WindowsWindow::WindowsWindow() {

	}

	WindowsWindow::~WindowsWindow() {

	}
	GLFWwindow* WindowsWindow::CreateWindow(int width, int height) {
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		GLFWwindow* window = glfwCreateWindow(width, height, "Physic Simulator", NULL, NULL);
		if (!window) {
			LOG("Window creation failed");
			glfwTerminate();
		}
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);

		return window;
	}
}
