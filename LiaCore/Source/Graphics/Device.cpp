#include "Device.h"


namespace Lia
{
	Device::Device(const Settings& settings)
		: mWindow(settings.Win)
	{

		mGpuObjs = CreateUptr<GpuObjects>();
		//Set procs for the dawn backend, so that the functions get loaded
		DawnProcTable backendProcs = dawn::native::GetProcs();
		dawnProcSetProcs(&backendProcs);
		
		CreateDevice();
		SetupSwapchain();


		
	}

	Device::~Device()
	{
	}


	void Device::ClearScreen(const glm::vec3& color)
	{

		auto cmdEncoder = mGpuObjs->Device.CreateCommandEncoder();

		wgpu::RenderPassDescriptor rPassDesc;

		auto nextSwapTex = mGpuObjs->Swapchain.GetCurrentTextureView();
		wgpu::RenderPassColorAttachment colorAttachment
		{
			.view = nextSwapTex,
			.loadOp = wgpu::LoadOp::Clear,
			.storeOp = wgpu::StoreOp::Store,
			.clearValue = {.r = color.r, .g = color.g, .b = color.b, .a = 1.0}
		};

		rPassDesc.colorAttachments = &colorAttachment;
		rPassDesc.colorAttachmentCount = 1;
		rPassDesc.depthStencilAttachment = nullptr;
		{
			wgpu::RenderPassEncoder rPassEnc = cmdEncoder.BeginRenderPass(&rPassDesc);


			rPassEnc.End();
		}

		wgpu::CommandBuffer cmdBuf = cmdEncoder.Finish();
		nextSwapTex.Release();
		auto queue = mGpuObjs->Device.GetQueue();

		queue.Submit(1, &cmdBuf);



	}

	
	void Device::Present()
	{
		mGpuObjs->Swapchain.Present();

	}


	//HELPERS ---------------------
	void Device::CreateDevice()
	{
		mGpuObjs->Instance = wgpu::Instance::Acquire(mGpuObjs->NativeInstance.Get());
#ifdef NDEBUG
		mGpuObjs->NativeInstance.SetBackendValidationLevel(dawn::native::Disabled);
#else
		mGpuObjs->NativeInstance.SetBackendValidationLevel(dawn::native::Full);
#endif // NDEBUG
		mGpuObjs->NativeInstance.DiscoverDefaultAdapters();
		auto adapters = mGpuObjs->NativeInstance.GetAdapters();
		for (auto& adaper : adapters)
		{
			wgpu::AdapterProperties properties{};
			adaper.GetProperties(&properties);
			LOG_INFO(properties.name);
			if (properties.backendType == wgpu::BackendType::Vulkan)
			{
				wgpu::DeviceDescriptor deviceDesc{};
				auto dev = adaper.CreateDevice();
				mGpuObjs->Device = wgpu::Device::Acquire(dev);
				return;
			}
			
		}
	}



	void Device::SetupSwapchain()
	{
#ifdef WIN32
		{
			wgpu::SurfaceDescriptor surfDesc{};
			wgpu::SurfaceDescriptorFromWindowsHWND surfDescWin{};

			surfDescWin.hwnd = glfwGetWin32Window(mWindow->GetGLFWWindow());
			surfDescWin.hinstance = GetModuleHandle(nullptr);

			surfDesc.nextInChain = &surfDescWin;
			mGpuObjs->Surface = mGpuObjs->Instance.CreateSurface(&surfDesc);
			
		}
		{
			wgpu::SwapChainDescriptor swapDesc{};
			swapDesc.format = wgpu::TextureFormat::BGRA8Unorm;
			swapDesc.height = mWindow->GetDimensions().y;
			swapDesc.width = mWindow->GetDimensions().x;
			swapDesc.presentMode = wgpu::PresentMode::Immediate;
			swapDesc.usage = wgpu::TextureUsage::RenderAttachment;

			mGpuObjs->Swapchain = mGpuObjs->Device.CreateSwapChain(mGpuObjs->Surface,
																&swapDesc);

			

		}
		return;
	//TODO: Detect wayland or x11 and implement the surface function
#elif WAYLAND

#elif X11


#endif
	}

}	

