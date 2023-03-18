#pragma once


#include "../Window/WindowsWindow.h"
#include "Graphics/GraphicCore.h"
#include "glm//glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Object/Material.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

#ifdef PYS_PLATFORM_WINDOWS 
extern Simulator::Application* Simulator::CreateApplication();

int main(int argc, char** argv) {

    auto app = Simulator::CreateApplication();

	SimulatorCore::InitGlfw();
	//create Window
	Simulator::WindowsWindow windows_window;
	GLFWwindow* window = windows_window.CreateWindow(640, 480);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	SimulatorCore::InitGlew();
	SimulatorCore::InitImGui(window);
	
	ImGuiIO& io = ImGui::GetIO();

	app->OnStart();

	while (!glfwWindowShouldClose(window)) {
		//poll events
		glfwPollEvents();

		SimulatorCore::ImGuiStartFrame();
		app->OnUpdate();
		
		SimulatorCore::Clear();

		app->OnRender();

		SimulatorCore::ImGuiRender();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(window);
	}
	SimulatorCore::Terminate(window);
    delete app;
    return 0;
}


#endif // 

