#pragma once
#include "Window.h"


namespace Lia
{
	class Device
	{

	public:
		struct Settings
		{
			Sptr<Window> Win;
			
		};

		
		Device(const Settings& settings);
		~Device();


		Device(Device&) = delete;
		Device& operator=(Device&) = delete;

		void ClearScreen(const glm::vec3& color);

		void Present();

	private:

		void SetupSwapchain();
		void CreateDevice();
		struct GpuObjects
		{
			wgpu::Surface Surface;
			wgpu::Device Device;
			dawn::native::Instance NativeInstance;
			wgpu::Instance Instance;
			wgpu::SwapChain Swapchain;
		};
		Uptr<GpuObjects> mGpuObjs;
		

		Sptr<Window> mWindow;
	};
}