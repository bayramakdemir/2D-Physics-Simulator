#pragma once

#ifdef PYS_PLATFORM_WINDOWS 
extern Simulator::Application* Simulator::CreateApplication();

int main(int argc, char** argv) {

    auto app = Simulator::CreateApplication();
    app->Run();

    delete app;
    return 0;
}


#endif // 

