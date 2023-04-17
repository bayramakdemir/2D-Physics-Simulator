#pragma once

struct GLFWwindow;

namespace Simulator {

    class Application {
    public:
        Application();
        virtual ~Application();

        virtual void OnUpdate(GLFWwindow* window){};
        virtual void OnRender(GLFWwindow* window){};
        virtual void OnStart(GLFWwindow* window){};

    };

    //to be defined in client
    Application* CreateApplication();

}

