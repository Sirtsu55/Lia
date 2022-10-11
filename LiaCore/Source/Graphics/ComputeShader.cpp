#include "ComputeShader.h"
#include "Utils/FileRead.h"
#include "Texture.h"
namespace Lia
{
	ComputeShader::ComputeShader(const wgpu::Device& dev, const std::string& path)
		:mDev(dev)
	{
		//Read Shadercode
		std::vector<uint32_t> spvCode;
		FileRead(path, spvCode);

		wgpu::ShaderModuleSPIRVDescriptor spvDesc{};
		spvDesc.code = spvCode.data();
		spvDesc.codeSize = spvCode.size();

		wgpu::ShaderModuleDescriptor shaderDesc{ .nextInChain = &spvDesc };
		mShaderModule = mDev.CreateShaderModule(&shaderDesc);


	}

	ComputeShader::~ComputeShader()
	{
	}


	void ComputeShader::CreatePipeline()
	{
		CreatePipeLayout();

		mPipeDesc.compute.module = mShaderModule;
		mPipeDesc.compute.entryPoint = "main";
		mPipeDesc.compute.constantCount = 0;
		mPipeDesc.compute.constants = nullptr;
		mPipeDesc.layout = mPipeLayout;

		mComputePipe = mDev.CreateComputePipeline(&mPipeDesc);
	}


	void ComputeShader::SetupForDispatch(const wgpu::ComputePassEncoder& cmdEncoder)
	{
		cmdEncoder.SetBindGroup(0, BindGroupManager.mBindGroup);

		
		cmdEncoder.SetPipeline(mComputePipe);
	}

	
	void ComputeShader::CreatePipeLayout()
	{
		wgpu::PipelineLayoutDescriptor desc{};

		desc.bindGroupLayouts = &BindGroupManager.mBindGroupLayout;
		desc.bindGroupLayoutCount = 1;	//HARDCODED TO ONE

		mPipeLayout = mDev.CreatePipelineLayout(&desc);
	}
}