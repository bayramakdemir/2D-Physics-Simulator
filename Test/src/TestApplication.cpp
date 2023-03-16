
#include <Simulator.h>
#include <Window/WindowsWindow.h>
#include "Graphics/GraphicCore.h"

// Callback function for printing debug statements
void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length,
    const GLchar* msg, const void* data) {
    char* _source;
    char* _type;
    char* _severity;

    switch (source) {
    case GL_DEBUG_SOURCE_API:
        _source = "API";
        break;

    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        _source = "WINDOW SYSTEM";
        break;

    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        _source = "SHADER COMPILER";
        break;

    case GL_DEBUG_SOURCE_THIRD_PARTY:
        _source = "THIRD PARTY";
        break;

    case GL_DEBUG_SOURCE_APPLICATION:
        _source = "APPLICATION";
        break;

    case GL_DEBUG_SOURCE_OTHER:
        _source = "UNKNOWN";
        break;

    default:
        _source = "UNKNOWN";
        break;
    }

    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        _type = "ERROR";
        break;

    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        _type = "DEPRECATED BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        _type = "UDEFINED BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_PORTABILITY:
        _type = "PORTABILITY";
        break;

    case GL_DEBUG_TYPE_PERFORMANCE:
        _type = "PERFORMANCE";
        break;

    case GL_DEBUG_TYPE_OTHER:
        _type = "OTHER";
        break;

    case GL_DEBUG_TYPE_MARKER:
        _type = "MARKER";
        break;

    default:
        _type = "UNKNOWN";
        break;
    }

    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        _severity = "HIGH";
        break;

    case GL_DEBUG_SEVERITY_MEDIUM:
        _severity = "MEDIUM";
        break;

    case GL_DEBUG_SEVERITY_LOW:
        _severity = "LOW";
        break;

    case GL_DEBUG_SEVERITY_NOTIFICATION:
        _severity = "NOTIFICATION";
        break;

    default:
        _severity = "UNKNOWN";
        break;
    }
    LOG(id << ":" << _type <<" of "<< _severity
        <<" severity, raised from "<< _source<< " "<< msg);
}


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
        glDebugMessageCallback(GLDebugMessageCallback,nullptr);
        
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

		for (float& v : vertices) {
			v *=1;
		}
        unsigned int indices[] = {  // note that we start from 0!
       0, 1, 3,  // first Triangle
       1, 2, 3   // second Triangle
        };


        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);

		
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
				circle->setPosition(glm::vec2(pos[0], pos[1]));
				ImGui::SliderFloat2("Circle Position", pos,0,1000);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
				ImGui::End();
			}
			
			
			//rendering
			SimulatorCore::Clear();
			glClearColor(0.7f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

            shader.useShader();
			glBindVertexArray(VAO);
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
			
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