#include "Window.h"
#include "Graphics/ComputeTracer.h"



int main()
{
	Log::Init();
    Lia::Window::Init();


    
    {
        Lia::Window::Settings settings = { .Name = "LiaEngine", .Resolution = glm::ivec2(1280, 720) };
        
        Sptr<Lia::Window> win = CreateSptr<Lia::Window>(settings);

        Lia::ComputeTracer::CreateInfo tracerInf{};
        tracerInf.Win = win;


        Sptr<Lia::Tracer> tracer = Lia::Tracer::CreateComputeTracer(tracerInf);


        SimpleTimer frametimer;

        while (win->IsActive())
        {
            frametimer.Start();
            tracer->BeginFrame();
            tracer->DrawTriangle();
            win->UpdateInput();
            tracer->EndFrame();
            double time = frametimer.Endd(TimerAccuracy::MilliSec);
            LOG_INFO("[FrameTime]: {} [FPS]: {}", time, 1000 / time);
        }
    }
    
    
    Lia::Window::DeInit();
    
    return 0;
}
