#pragma once

namespace Simulator {

    class Application {
    public:
        Application();
        virtual ~Application();

        virtual void OnUpdate(){};
        virtual void OnRender(){};
        virtual void OnStart(){};

    };

    //to be defined in client
    Application* CreateApplication();

}

