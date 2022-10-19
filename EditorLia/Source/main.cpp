#include "App.h"
#include "EditorLayer.h"

int main()
{
    Log::Init();
    Lia::Window::Init();
    {
        /*TODO: Make a Layerhandler that gathers data after
        every layer and sends the data through layerdata to 
        the functions, it would also abstract away the for loops here*/
        std::vector<Uptr<Lia::Layer>> layers;
        
        layers.push_back(CreateUptr<TestApp>());
        layers.push_back(CreateUptr<Lia::EditorLayer>());


        Lia::LayerData data{};

        for (auto& layer : layers)
        {
            Lia::LayerData data{};
            layer->OnStart();
        }


        while (layers[0]->GetLayerInfo() & Lia::LayerFlags::WindowOpen)
        {
            for (auto& layer : layers)
            {
                layer->BeforeGameLoop(data);
            }

            for (auto& layer : layers)
            {
                layer->GameLoop(data);
            }

            for (auto& layer : layers)
            {
                layer->AfterGameLoop(data);
            }
        }
        for (auto& layer : layers)
        {
            layer->OnEnd();
        }

    }


    Lia::Window::DeInit();

    return 0;
}
