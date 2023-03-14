
#include <Simulator.h>
#include <Window/WindowsWindow.h>

void error_callback(int error, const char* description) {
	LOG(description);
}

class   TestApplication : public Simulator::Application {
public:
    TestApplication() {

    }
    ~TestApplication() {

    }
    void Run() {
		if (!glfwInit()) {
			// Initialization failed
		}
		glfwSetErrorCallback(error_callback);

		Simulator::WindowsWindow windows_window;
		GLFWwindow* window = windows_window.CreateWindow();


		while (!glfwWindowShouldClose(window)) {
			// Keep running
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwDestroyWindow(window);
    }
};


Simulator::Application* Simulator::CreateApplication() {
    return new TestApplication();
}