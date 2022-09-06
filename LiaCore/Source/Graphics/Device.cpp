#include "Device.h"
#include "Callbacks.h"
#include "ComputeShader.h"
#include "Buffer.h"
#include "Texture.h"

namespace Lia
{
	Device::Device(const Settings& settings)
		: mWindow(settings.Win)
	{

		mGfx = CreateUptr<GpuObjects>();
		//Set procs for the dawn backend, so that the functions get loaded
		DawnProcTable backendProcs = dawn::native::GetProcs();
		dawnProcSetProcs(&backendProcs);
		
		CreateDevice();
		SetupSwapchain();

		//Setup Imgui

		
		ImGui::CreateContext();
		ImGuiIO io = ImGui::GetIO();
		io.ConfigFlags = ImGuiConfigFlags_DockingEnable;
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOther(mWindow->GetGLFWWindow(), true);
		ImGui_ImplWGPU_Init(mGfx->Device.Get(), 3, WGPUTextureFormat_BGRA8Unorm);
	}

	Device::~Device()
	{
		ImGui_ImplWGPU_Shutdown();

		mGfx->Device.Destroy();
	}
	void Device::SetupCompute()
	{
		mCompShader = CreateUptr<ComputeShader>(mGfx->Device,"Shaders/Compute.comp.spv");
		Texture::TextureInfo inf{};
		inf.Dimentions = glm::uvec2(mWindow->GetDimensions());
		inf.Format = wgpu::TextureFormat::RGBA16Float;
		inf.Usage = wgpu::TextureUsage::TextureBinding | wgpu::TextureUsage::StorageBinding;

		mTex = CreateUptr<Texture>(mGfx->Device, inf);
		mTexview = mTex->GetView();
		mCompShader->BindGroupManager.AddStorageTexture(GetSmartPtrAsRef<Texture>(mTex), 0);
		mCompShader->BindGroupManager.ConstructBindGroups(mGfx->Device);

		mCompShader->CreatePipeline();
	}


	void Device::BeginFrame()
	{
		//Setup Imgui for new frame
		ImGui_ImplWGPU_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		bool show = true;
		{
			ImGui::Begin("Window", &show);
			ImGui::Image(mTexview->Get(), ImVec2(1280, 720));
			ImGui::End();
		}

		{
			ImGui::Begin("Pick Color", &show);
			ImGui::ColorPicker3("picker", glm::value_ptr(color));
			ImGui::End();
		}


	}
	
	void Device::EndFrame()
	{

		//Dispatch compute

		wgpu::Queue queue = mGfx->Device.GetQueue();
		wgpu::CommandEncoderDescriptor enc_desc = {};
		wgpu::CommandEncoder cmdencoder = mGfx->Device.CreateCommandEncoder(& enc_desc);
		
		auto compCmd = cmdencoder.BeginComputePass();
		{

			mCompShader->SetupForDispatch(compCmd);
			compCmd.DispatchWorkgroups(mWindow->GetDimensions().x, mWindow->GetDimensions().y, 1);

		}
		compCmd.End();
		auto cmdBuf = cmdencoder.Finish();
		queue.Submit(1, &cmdBuf);


		// Rendering

		wgpu::RenderPassColorAttachment color_attachments = {};
		color_attachments.loadOp = wgpu::LoadOp::Clear;
		color_attachments.storeOp = wgpu::StoreOp::Store;
		color_attachments.clearValue = {0.0f, 0.0f, 0.0f, 1.0f};
		color_attachments.view = mGfx->Swapchain.GetCurrentTextureView();


		ImGui::Render();
		wgpu::RenderPassDescriptor render_pass_desc = {};
		render_pass_desc.colorAttachmentCount = 1;
		render_pass_desc.colorAttachments = &color_attachments;
		render_pass_desc.depthStencilAttachment = 0;
		wgpu::CommandEncoder encoder = mGfx->Device.CreateCommandEncoder(&enc_desc);

		wgpu::RenderPassEncoder rPass = encoder.BeginRenderPass(&render_pass_desc);
		ImGui_ImplWGPU_RenderDrawData(ImGui::GetDrawData(), rPass.Get());
		rPass.End();
		
		auto rendercmdBuf = encoder.Finish();
		queue.Submit(1, &rendercmdBuf);

		mGfx->Swapchain.Present();
	}


	//HELPERS ---------------------
	void Device::CreateDevice()
	{
		mGfx->Instance = wgpu::Instance::Acquire(mGfx->NativeInstance.Get());
#ifdef NDEBUG
		mGfx->NativeInstance.SetBackendValidationLevel(dawn::native::Disabled);
#else
		mGfx->NativeInstance.EnableBackendValidation(true);
		mGfx->NativeInstance.SetBackendValidationLevel(dawn::native::Full);
#endif // NDEBUG
		mGfx->NativeInstance.DiscoverDefaultAdapters();
		auto adapters = mGfx->NativeInstance.GetAdapters();
		for (auto& adaper : adapters)
		{
			wgpu::AdapterProperties properties{};
			adaper.GetProperties(&properties);
			LOG_INFO(properties.name);
			if (properties.backendType == wgpu::BackendType::Vulkan)
			{
				wgpu::DeviceDescriptor deviceDesc{};
				auto dev = adaper.CreateDevice();
				mGfx->Device = wgpu::Device::Acquire(dev);
				mGfx->Device.SetLoggingCallback(DeviceLogCback, nullptr);
				mGfx->Device.SetUncapturedErrorCallback(DeviceErrorCback, nullptr);


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
			mGfx->Surface = mGfx->Instance.CreateSurface(&surfDesc);
			
		}
		{
			wgpu::SwapChainDescriptor swapDesc{};
			swapDesc.format = wgpu::TextureFormat::BGRA8Unorm;
			swapDesc.height = mWindow->GetDimensions().y;
			swapDesc.width = mWindow->GetDimensions().x;
			swapDesc.presentMode = wgpu::PresentMode::Immediate;
			swapDesc.usage = wgpu::TextureUsage::RenderAttachment;

			mGfx->Swapchain = mGfx->Device.CreateSwapChain(mGfx->Surface,
																&swapDesc);

		}
		return;
	//TODO: Detect wayland or x11 and implement the surface function
#elif WAYLAND

#elif X11


#endif
	}

}	

