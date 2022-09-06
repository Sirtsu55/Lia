#pragma once
#include "Window.h"


namespace Lia
{
	class ComputeShader;
	class Buffer;
	class Texture;

	//Create Everything to render on the screen
	//-Creates a Swapchain
	//-Sets up Imgui rendering for the given window
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

		//TESTING
		void SetupCompute();
		void BeginFrame();

		void EndFrame();

	private:
		//TESTING
		glm::vec3 color;

		Uptr<ComputeShader> mCompShader;
		wgpu::BindGroup mComputeBindGroup;
		Uptr<Texture> mTex;
		Sptr<wgpu::TextureView> mTexview;


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
		Uptr<GpuObjects> mGfx;

		Sptr<Window> mWindow;
	};
}