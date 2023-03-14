
#include <Simulator.h>

class TestApplication : public Simulator::Application {
public:
    TestApplication() {

    }
    ~TestApplication() {

    }
};


Simulator::Application* Simulator::CreateApplication() {
    return new TestApplication();
}