#include "Window.h"



int main()
{
	Log::Init();
    Lia::Window::Init();


    
    {
        Lia::Window::Settings settings = { .Name = "LiaEngine", .Resolution = glm::ivec2(1280, 720) };
        
        Sptr<Lia::Window> win = CreateSptr<Lia::Window>(settings);





        SimpleTimer frametimer;

        while (win->IsActive())
        {

            win->UpdateInput();
        }
    }
    
    
    Lia::Window::DeInit();
    
    return 0;
}
