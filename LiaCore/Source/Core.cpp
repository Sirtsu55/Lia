#include "Window.h"
#include "Graphics/Device.h"


int main()
{
	Log::Init();
    Lia::Window::Init();

    SimpleTimer timer;
    {
        Lia::Window::Settings settings = { .Name = "LiaEngine", .Resolution = glm::ivec2(1280, 720) };
        
        Sptr<Lia::Window> win = CreateSptr<Lia::Window>(settings);

        Lia::Device::Settings devSettings = { win };
        Sptr<Lia::Device> dev = CreateSptr<Lia::Device>(devSettings);

        SimpleTimer frametimer;
        dev->SetupCompute();
        while (win->IsActive())
        {
            //timer.Start();
            dev->BeginFrame();
            dev->EndFrame();
            win->UpdateInput();
            //LOG_INFO("Frame Time: {} ms", timer.Endd(TimerAccuracy::MilliSec));
        }
    }
    
    
    Lia::Window::DeInit();
    
    return 0;
}
