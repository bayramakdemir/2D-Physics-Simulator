
#include <Simulator.h>

class   TestApplication : public Simulator::Application {
private:
	Simulator::OrthographicCamera* m_camera;
public:
    TestApplication() {

    }
    ~TestApplication() {

    }
	void OnStart(GLFWwindow* window) override {
		ImGuiIO& io = ImGui::GetIO();
		m_camera = new Simulator::OrthographicCamera(-10, 10,-10, 10);
		glViewport(0, 0, io.DisplaySize.x, io.DisplaySize.y);

		SimulatorCore::Renderer::Init();
		
	}

	void OnUpdate(GLFWwindow* window) override {
		const float cameraSpeed = 10.0f; // adjust accordingly
		ImGuiIO& io = ImGui::GetIO();
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			m_camera->move(glm::vec3( -cameraSpeed * io.DeltaTime, 0.0f, 0.0f));
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			m_camera->move(glm::vec3(cameraSpeed * io.DeltaTime, 0.0f, 0.0f));
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			m_camera->move(glm::vec3(0.0f,cameraSpeed * io.DeltaTime, 0.0f));
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			m_camera->move(glm::vec3(0.0f, -cameraSpeed * io.DeltaTime, 0.0f));
	}

	void OnRender(GLFWwindow* window) override{

		ImGuiIO& io = ImGui::GetIO();
		ImGui::Begin("FPS Counter");
		static float pos[2];
		static float scale[2], radius;
		
		ImGui::SliderFloat2("Position", pos, 0, 10.0f);
		ImGui::SliderFloat2("scale", scale, 0.1f, 5.0f);
		ImGui::SliderFloat("Radius", &radius, 0, 1);

		Simulator::TransformComponent tranform;
		
		tranform.setScale({ scale[0], scale[1], 1.0f });
		tranform.setPosition({ pos[0], pos[1], 0.0f });

		SimulatorCore::Renderer::BeginScene(*m_camera);
		SimulatorCore::Renderer::DrawQuad(tranform);

		for (int i = 0; i < 5; i++) {
			SimulatorCore::Renderer::DrawQuad({i,i*2,1.0f});
		}
		
		SimulatorCore::Renderer::EndScene();

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

		ImGui::End();
    }
};


Simulator::Application* Simulator::CreateApplication() {
    return new TestApplication();
}