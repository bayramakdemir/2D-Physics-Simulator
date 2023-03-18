
#include <Simulator.h>


class   TestApplication : public Simulator::Application {
private:
	
public:
    TestApplication() {

    }
    ~TestApplication() {

    }
	void OnStart() override {
		//onStart
	}
	void OnRender() override{
		ImGuiIO& io = ImGui::GetIO();
		ImGui::Begin("FPS Counter");
		static float pos[2];
		static float rotZ, radius;
		ImGui::SliderFloat2("Position", pos, 0, 1.0f);
		ImGui::SliderFloat("Rotation", &rotZ, 0, 360);
		ImGui::SliderFloat("Radius", &radius, 0, 500);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();
    }
};


Simulator::Application* Simulator::CreateApplication() {
    return new TestApplication();
}