#pragma once


#include "../Window/WindowsWindow.h"
#include "Graphics/GraphicCore.h"
#include "glm//glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#ifdef PYS_PLATFORM_WINDOWS 
extern Simulator::Application* Simulator::CreateApplication();

int main(int argc, char** argv) {

    auto app = Simulator::CreateApplication();

	SimulatorCore::InitGlfw();
	//create Window
	Simulator::WindowsWindow windows_window;
	GLFWwindow* window = windows_window.CreateWindow(640, 640);
	glfwMakeContextCurrent(window);

	SimulatorCore::InitGlew();
	SimulatorCore::InitImGui(window);
	
	ImGuiIO& io = ImGui::GetIO();

	app->OnStart(window);

	while (!glfwWindowShouldClose(window)) {
		//poll events
		glfwPollEvents();

		SimulatorCore::ImGuiStartFrame();
		app->OnUpdate(window);
		
		SimulatorCore::Clear();

		app->OnRender(window);

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

