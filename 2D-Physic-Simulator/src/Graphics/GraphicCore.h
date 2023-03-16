#pragma once
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
//imgui
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

//log
#include "../Core.h"

namespace SimulatorCore {
	void error_callback(int error, const char* description) {
		LOG("error:"<< error << " " << description);
	}


	void InitGlfw() {
		//init glfw
		if (!glfwInit()) {
			// Initialization failed
		}
		glfwSetErrorCallback(error_callback);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
	void InitGlew() {

		GLenum status;
		if (GLEW_OK != (status = glewInit())) {
			LOG("glew initilazion failed reason:" << glewGetErrorString(status));
		}
	}
	void InitImGui(GLFWwindow* window) {
		//ImGui Stuff
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		ImGui::StyleColorsDark();
		const char* glsl_version = "#version 150";
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);
	}
	void ImGuiStartFrame() {
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	void ImGuiRender() {
		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	void Clear() {
		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void Terminate(GLFWwindow* window) {
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		glfwDestroyWindow(window);
		glfwTerminate();
	}
}