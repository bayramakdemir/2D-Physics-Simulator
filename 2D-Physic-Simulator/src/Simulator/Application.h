#pragma once

#include "../Core.h"

namespace Simulator {

    class SIMULATOR_API Application {
    public:
        Application();
        virtual ~Application();
        void Run();
    };

    //to be defined in client
    Application* CreateApplication();

}

