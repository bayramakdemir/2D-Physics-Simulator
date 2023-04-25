
#include <Simulator.h>
#include <thread>
#include <random>


class   TestApplication : public Simulator::Application {
private:
	Simulator::OrthographicCamera* m_camera;
	Simulator::Scene m_Scene;

	struct WindowData {
		int width;
		int height;
		
		Simulator::OrthographicCamera* m_camera;
	};
	WindowData m_data;

	int size = 0;
	std::mt19937_64 gen64;
	
public:
    TestApplication() {

    }
    ~TestApplication() {

    }
	void resizeFunction() {

	}
	
	void OnStart(GLFWwindow* window) override {
		ImGuiIO& io = ImGui::GetIO();
		m_camera = new Simulator::OrthographicCamera(-10, 10,-10, 10);
		glViewport(0, 0, io.DisplaySize.x, io.DisplaySize.y);
		
		m_data.m_camera = m_camera;
		glfwSetWindowUserPointer(window, &m_data);
		glfwSetWindowSizeCallback(window, [](GLFWwindow * window, int width, int height) {
			glViewport(0, 0, width, height);
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.height = height;
			data.width = width;
			float aspectRatio = width / (float) height;

			data.m_camera->setProjection(aspectRatio * 10.0f, -aspectRatio * 10.0f,  10.0f, -10.0f);
		});

		m_Scene.start();
		for (int x = 0; x < size; x++) {
			for (int y = 0; y < size; y++) {
				auto& circle = m_Scene.createEntity();
				circle.addComponent<Simulator::CircleRendererComponent>();
				
				auto& transform = circle.getComponent< Simulator::TransformComponent>();
				transform.setPosition({ x,y, 0.0f });
		
				circle.addComponent<Simulator::CircleRigidbody>(&transform);
			}
		}
		

		SimulatorCore::Renderer::Init();
		
	}

	void OnUpdate(GLFWwindow* window) override {
		const float cameraSpeed = 50.0f; // adjust accordingly
		ImGuiIO& io = ImGui::GetIO();
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			m_camera->move(glm::vec3( cameraSpeed * io.DeltaTime, 0.0f, 0.0f));
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			m_camera->move(glm::vec3( -cameraSpeed * io.DeltaTime, 0.0f, 0.0f));
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			m_camera->move(glm::vec3(0.0f, -cameraSpeed * io.DeltaTime, 0.0f));
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			m_camera->move(glm::vec3(0.0f, cameraSpeed * io.DeltaTime, 0.0f));

		float zoomSpeed = 5.0f;
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			zoomSpeed *= 3.0f;
		m_camera->zoom(io.MouseWheel * io.DeltaTime * zoomSpeed);
		
	}
	bool solving = false;
	void OnRender(GLFWwindow* window) override{

		ImGuiIO& io = ImGui::GetIO();
		ImGui::Begin("Stats");

		Simulator::Solver::Solve(m_Scene, io.DeltaTime);

		//RENDER 
		m_Scene.render(*m_camera);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::Text("Renderer Triangle Count:%d \nRenderer render call Count:%d", 
			SimulatorCore::Renderer::RenderStat.TriangleCount, SimulatorCore::Renderer::RenderStat.RenderCall);

		double x, y;
		glfwGetCursorPos(window, &x, &y);
		const glm::vec2 worldp = m_camera->screenToWorldCoord({ x,y }, { io.DisplaySize.x,io.DisplaySize.y });

		static bool pressed = false;
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !pressed) {
			auto& circle = m_Scene.createEntity();
			auto& renderer =circle.addComponent<Simulator::CircleRendererComponent>();

			auto& transform = circle.getComponent< Simulator::TransformComponent>();
			transform.setPosition({ worldp.x,worldp.y, 0.0f });
			std::uniform_real_distribution<float> unif(0, 1);
			renderer.color = { unif(gen64),unif(gen64),unif(gen64),1.0f };
			circle.addComponent<Simulator::CircleRigidbody>(&transform);
			const float scale = unif(gen64) + 0.4f;
			transform.setScale({ scale,scale,scale } );
			
			//pressed = true;
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
			//pressed = false;
		}

		ImGui::Text("mouse world pos: %.3f,%.3f",worldp.x, worldp.y);
		ImGui::End();
    }
};

Simulator::Application* Simulator::CreateApplication() {
    return new TestApplication();
}