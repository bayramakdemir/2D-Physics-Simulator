
#include <Simulator.h>
#include <Window/WindowsWindow.h>

void error_callback(int error, const char* description) {
	LOG(description);
}

class   TestApplication : public Simulator::Application {
	Simulator::Scene* scene;
public:
    TestApplication() {

    }
    ~TestApplication() {

    }
    void Run() {

		//init glfw
		if (!glfwInit()) {
			// Initialization failed
		}
		glfwSetErrorCallback(error_callback);

		//create Window
		Simulator::WindowsWindow windows_window;
		GLFWwindow* window = windows_window.CreateWindow(640,640);

		//scene manager
		Simulator::SceneManager manager;
		manager.setActiveScene(scene);
		//scene
		scene = new Simulator::Scene();
		
		//objects
		Simulator::Circle* circle1 = new Simulator::Circle();

		//add them
		scene->addObject(circle1);

		
		//start function (not implemented yet)
		

		while (!glfwWindowShouldClose(window)) {
			// Keep running
			glClear(GL_COLOR_BUFFER_BIT);

			//render scene objects
			manager.renderScene();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		delete scene;
		glfwDestroyWindow(window);
    }
};


Simulator::Application* Simulator::CreateApplication() {
    return new TestApplication();
}