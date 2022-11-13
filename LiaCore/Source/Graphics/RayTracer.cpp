#include "RayTracer.h"
#include "GameWorld/World.h"
#include "Buffer.h"

namespace Lia
{
	RayTracer::RayTracer(const Settings& info)
		: mInfo(info)
	{
		//Device Creation
		Lia::Device::Settings devSettings = { mInfo.OutputWindow };
		mDevice = CreateSptr<Lia::Device>(devSettings);

		
		mShader = CreateSptr<Lia::ComputeShader>(mDevice->GetDevice(), info.RTShaderPath);

		//Create texture for output 
		Lia::Texture::Info inf{};
		inf.Dimentions = info.CanvasSize;
		inf.Format = wgpu::TextureFormat::RGBA16Float;
		inf.Usage = wgpu::TextureUsage::TextureBinding | wgpu::TextureUsage::StorageBinding;

		mOutTexture = CreateSptr<Lia::Texture>(mDevice->GetDevice(), inf);
		mOutTexView = mOutTexture->GetView();

		auto bufferUsages = wgpu::BufferUsage::Uniform;
		mUniformBuffer = CreateSptr<Lia::Buffer>(mDevice->GetDevice(), bufferUsages, sizeof(UniformBufferData), nullptr);

		bufferUsages = wgpu::BufferUsage::Storage;
		mVoxelBuffer = CreateSptr<Lia::Buffer>(mDevice->GetDevice(), bufferUsages, sizeof(VoxelData) * 100, nullptr);

		mVoxelTreeBuffer = CreateSptr<Lia::Buffer>(mDevice->GetDevice(), bufferUsages, sizeof(VoxelNode) * 100, nullptr);

		mVoxelMaterialBuffer = CreateSptr<Lia::Buffer>(mDevice->GetDevice(), bufferUsages, sizeof(VoxelNode) * 25, nullptr);

		mShader->BindGroupManager.AddStorageTexture(GetSmartPtrAsRef<Lia::Texture>(mOutTexture), 0);
		mShader->BindGroupManager.AddBuffer(GetSmartPtrAsRef<Lia::Buffer>(mUniformBuffer), 1, wgpu::BufferBindingType::Uniform);

		mShader->BindGroupManager.AddBuffer(GetSmartPtrAsRef<Lia::Buffer>(mVoxelBuffer), 2, wgpu::BufferBindingType::Storage);
		mShader->BindGroupManager.AddBuffer(GetSmartPtrAsRef<Lia::Buffer>(mVoxelTreeBuffer), 3, wgpu::BufferBindingType::Storage);
		mShader->BindGroupManager.AddBuffer(GetSmartPtrAsRef<Lia::Buffer>(mVoxelMaterialBuffer), 4, wgpu::BufferBindingType::Storage);

		mShader->BindGroupManager.ConstructBindGroups(mDevice->GetDevice());

		mShader->CreatePipeline();
	}
	RayTracer::~RayTracer()
	{
	}
	

	void RayTracer::TraceWorld(const Sptr<World>& world)
	{

		mDevice->DispatchCompute(mShader, mInfo.CanvasSize);
		mDevice->RenderImgui();
	}
	
	void RayTracer::UpdateBuffers(Sptr<World>& world)
	{
	
		if (world->VoxelsUpdated)
		{
			//This is reuploading whole buffer
			//TODO: upload chunks that have been updated and 

			
			mVoxelBuffer->UploadData(world->mVoxelSDF.data(),
				world->mVoxelSDF.size() * sizeof(VoxelSDF),
				0);

			uint32_t numTrees = world->mVoxelsTree.size();



			mVoxelTreeBuffer->UploadData(world->mVoxelsTree.data(),
				numTrees* sizeof(VoxelNode),
				0);

			world->VoxelsUpdated = false;

		}

	}

	void RayTracer::UpdateUniformBuffer()
	{
		mUniformBuffer->UploadData( &mUniformData, sizeof(UniformBufferData), 0);

	}
}