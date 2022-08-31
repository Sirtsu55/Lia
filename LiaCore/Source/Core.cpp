#include "Window.h"
#include "Graphics/Device.h"


int main()
{
	Log::Init();
    Lia::Window::Init();

    {
        Lia::Window::Settings settings = { .Name = "LiaEngine", .Resolution = glm::ivec2(1280, 720) };
        
        Sptr<Lia::Window> win = CreateSptr<Lia::Window>(settings);

        Lia::Device::Settings devSettings = { win };
        Sptr<Lia::Device> dev = CreateSptr<Lia::Device>(devSettings);

        SimpleTimer frametimer;

        while (win->IsActive())
        {
            dev->ClearScreen(glm::vec3(1.0f, 0.0f, 0.0f));
            dev->Present();
            win->UpdateInput();
        }
    }
    
    
    Lia::Window::DeInit();
    
    return 0;
}
