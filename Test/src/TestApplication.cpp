
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

	int size = 100;
	std::vector<glm::vec2> positions;
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
				positions.push_back({ x,y });
				auto circle = m_Scene.createEntity();
				circle.addComponent<Simulator::CircleRendererComponent>();
				auto transform = circle.getComponent< Simulator::TransformComponent>();
				transform.setPosition({ x,y, 0.0f });
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

	void OnRender(GLFWwindow* window) override{

		ImGuiIO& io = ImGui::GetIO();
		ImGui::Begin("Stats");
		/*static float pos[2];
		static float scale[2] = {1.0f,1.0f};
		
		ImGui::SliderFloat2("Position", pos, 0, 10.0f);
		ImGui::SliderFloat2("scale", scale, 0.1f, 5.0f);*/
	
		
		for (glm::vec2& pos : positions) {
			pos.x += (((float)gen64() / gen64.max()) - 0.5f) * io.DeltaTime;
			pos.y += (((float)gen64() / gen64.max()) - 0.5f) * io.DeltaTime;
		}

		auto view = (*m_Scene.getRegistery()).view<Simulator::TransformComponent>();
		int i = 0;
		for (auto entity : view) {
			auto& transform = view.get<Simulator::TransformComponent>(entity);
			transform.setPosition({ positions[i].x ,positions[i].y,0.0f});
			i++;
		}

		auto start = std::chrono::high_resolution_clock::now();
		
		//RENDER 
		m_Scene.render(*m_camera);
			
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::Text("Renderer Triangle Count:%d \nRenderer render call Count:%d", 
			SimulatorCore::Renderer::RenderStat.TriangleCount, SimulatorCore::Renderer::RenderStat.RenderCall);

		double x, y;
		glfwGetCursorPos(window, &x, &y);
		const glm::vec2 worldp = m_camera->screenToWorldCoord({ x,y }, { io.DisplaySize.x,io.DisplaySize.y });
		ImGui::Text("mouse world pos: %.3f,%.3f",worldp.x, worldp.y);
		ImGui::Text("render call took: %.2f ms", duration.count()/1000.0f);
		ImGui::End();
    }
};

Simulator::Application* Simulator::CreateApplication() {
    return new TestApplication();
}