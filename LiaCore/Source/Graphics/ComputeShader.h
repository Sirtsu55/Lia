#pragma once
#include "BGManager.h"


namespace Lia
{
	class Texture;
	class ComputeShader
	{
	public:
		ComputeShader(const wgpu::Device& dev, const std::string& path);
		~ComputeShader();


		ComputeShader(ComputeShader&) = delete;
		ComputeShader& operator=(ComputeShader&) = delete;


		wgpu::ComputePipeline Get() const { return mComputePipe; }

		//Call CreatePipeline after entries have been added to Bind Group Manager
		void CreatePipeline();

		void AddStorageTextureToPipeline(Texture& tex, uint32_t binding);

		//TODO: Setup Pipeline and bind all resources from this command
		void SetupForDispatch(const wgpu::ComputePassEncoder& cmdEncoder);

		BGManager BindGroupManager;
	private:

		//TODO: support many bind groups, NOW IT IS HARDCODED TO ONE BIND GROUP
		void CreatePipeLayout();


		wgpu::Device mDev;
		
		wgpu::ShaderModule mShaderModule;
		wgpu::ComputePipeline mComputePipe;
		wgpu::PipelineLayout mPipeLayout;
		wgpu::ComputePipelineDescriptor mPipeDesc;



	};

}
