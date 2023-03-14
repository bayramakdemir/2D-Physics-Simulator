#pragma once

namespace Simulator {

    class Application {
    public:
        Application();
        virtual ~Application();
        virtual void Run(); //reun in client
    };

    //to be defined in client
    Application* CreateApplication();

}

