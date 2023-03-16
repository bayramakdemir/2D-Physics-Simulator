
#include <Simulator.h>
#include <Window/WindowsWindow.h>
#include "Graphics/GraphicCore.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

class   TestApplication : public Simulator::Application {
	Simulator::Scene* scene;
public:
    TestApplication() {

    }
    ~TestApplication() {

    }
    void Run() {

		SimulatorCore::InitGlfw();

		//create Window
		Simulator::WindowsWindow windows_window;
		GLFWwindow* window = windows_window.CreateWindow(640, 640);
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		SimulatorCore::InitGlew();
		SimulatorCore::InitImGui(window);
		ImGuiIO& io = ImGui::GetIO();

		//scene
		scene = new Simulator::Scene();
		
		//objects
		//add them
		Simulator::Circle* circle = new Simulator::Circle(100);
		scene->addObject(circle);

		//scene manager
		Simulator::SceneManager manager;
		manager.setActiveScene(scene);

		LOG(glGetString(GL_VERSION));
       
        
		//create a Shader
		SimulatorCore::Shader shader;
		//shader.compileShaderFromText(vertexShaderSource, SimulatorCore::Shader::VERTEX);
		//shader.compileShaderFromText(fragmentShaderSource, SimulatorCore::Shader::FRAGMENT);
		shader.attachShader();
		float vertices[] = {
				 0.5f,  0.5f, 0.0f,  // top right
				 0.5f, -0.5f, 0.0f,  // bottom right
				-0.5f, -0.5f, 0.0f,  // bottom left
				-0.5f,  0.5f, 0.0f   // top left 
		};

        unsigned int indices[] = {  // note that we start from 0!
		   0, 1, 3,  // first Triangle
		   1, 2, 3   // second Triangle
        };


		SimulatorCore::VertexArray va;
		SimulatorCore::VertexBuffer vb(vertices,sizeof(vertices));
		
		SimulatorCore::VertexBufferLayout layout;
		layout.push<float>(3);
		va.addBuffer(vb, layout);
		SimulatorCore::IndexBuffer ib(indices, 6);

		va.unbind();
		vb.unbind();
		ib.unbind();

		SimulatorCore::Renderer renderer;

        // uncomment this call to draw in wireframe polygons.
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//start function (not implemented yet)
		while (!glfwWindowShouldClose(window)) {
			//poll events
			glfwPollEvents();

			SimulatorCore::ImGuiStartFrame();
			
			//FPS
			{
				ImGui::Begin("FPS Counter");    
				static float pos[2];
				ImGui::SliderFloat2("Circle Position", pos,0,1.0f);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
				ImGui::End();
				shader.bind();
				shader.setUniform4f("u_Pos", glm::vec4(pos[0], pos[1],0,1));
			}
			//rendering
			SimulatorCore::Clear();

			renderer.render(va, ib, shader);
			//manager.renderScene();
			SimulatorCore::ImGuiRender();

			glfwSwapBuffers(window);
		}

		SimulatorCore::Terminate(window);
		delete scene;
    }
};


Simulator::Application* Simulator::CreateApplication() {
    return new TestApplication();
}