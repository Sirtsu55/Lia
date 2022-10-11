#include "App.h"


int main()
{
    Log::Init();
    Lia::Window::Init();

    {
        TestApp* app = new TestApp();

        app->Start();
        //Lia::Window::Settings settings = { .Name = "LiaEngine", .Resolution = glm::ivec2(1280, 720) };

        //Sptr<Lia::Window> win = CreateSptr<Lia::Window>(settings);

        //Lia::Device::Settings devSettings = { win };
        //Sptr<Lia::Device> dev = CreateSptr<Lia::Device>(devSettings);

        //SimpleTimer frametimer;
        //dev->SetupCompute();
        while (app->mWindow->IsActive())
        {
            app->OnUpdate();
        }

        app->Destroy();
        delete app;
    }


    Lia::Window::DeInit();

    return 0;
}
