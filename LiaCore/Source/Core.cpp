#include "Window.h"
#include "EngineFactoryVk.h"

//dg = Diligent Graphics
namespace dg = Diligent;


int main()
{
	Log::Init();
    Lia::Window::Init();

    dg::IRenderDevice*  m_pDevice;
    dg::IDeviceContext* m_pImmediateContext;
    dg::ISwapChain*     m_pSwapChain;
    dg::IPipelineState* m_pPSO;
    dg::EngineVkCreateInfo EngineCI;

    auto* pFactoryVk = dg::GetEngineFactoryVk();
    pFactoryVk->CreateDeviceAndContextsVk(EngineCI, &m_pDevice, &m_pImmediateContext);
    dg::SwapChainDesc     SCDesc;




    {
        Lia::Window::Settings settings = { .Name = "LiaEngine", .Resolution = glm::ivec2(1280, 720) };
        
        Sptr<Lia::Window> win = CreateSptr<Lia::Window>(settings);

        dg::NativeWindow nativeWin;
        
        nativeWin.hWnd = glfwGetWin32Window(win->GetGLFWWindow());
        pFactoryVk->CreateSwapChainVk(m_pDevice, m_pImmediateContext, SCDesc, nativeWin, &m_pSwapChain);
        
        while (win->IsActive())
        {
            win->UpdateInput();
        }
    }
    
    
    Lia::Window::DeInit();
    
    return 0;
}
