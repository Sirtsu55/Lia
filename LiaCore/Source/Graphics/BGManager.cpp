#include "BGManager.h"
#include "Texture.h"
#include "Buffer.h"

namespace Lia
{

	void BGManager::ConstructBindGroups(const wgpu::Device& dev)
	{
		{
			wgpu::BindGroupLayoutDescriptor BGLDesc{};
			BGLDesc.entries = mBGLEntries.data();
			BGLDesc.entryCount = mBGLEntries.size();
			mBindGroupLayout = dev.CreateBindGroupLayout(&BGLDesc);
		}
			
		{
			wgpu::BindGroupDescriptor BGDesc{};
			BGDesc.entries = mBGEntries.data();
			BGDesc.entryCount = mBGEntries.size();
			BGDesc.layout = mBindGroupLayout;
			mBindGroup = dev.CreateBindGroup(&BGDesc);
		}
	}
	void BGManager::AddStorageTexture (
		Texture& tex,
		uint32_t binding,
		wgpu::ShaderStage visibility )
	{
		{
			wgpu::BindGroupLayoutEntry BGLentry{};
			BGLentry.binding = binding;
			BGLentry.storageTexture = wgpu::StorageTextureBindingLayout{
				nullptr, // nextInChain
				wgpu::StorageTextureAccess::WriteOnly, //access
				tex.GetFormat(), //format
				wgpu::TextureViewDimension::e2D	//view dimention
			};
			BGLentry.visibility = visibility;

			mBGLEntries.emplace_back(BGLentry);
		}

		{
			wgpu::BindGroupEntry BGEntry;

			BGEntry.binding = binding;
			BGEntry.textureView = GetSmartPtrAsRef<wgpu::TextureView>(tex.GetView());
			BGEntry.offset = 0;
			BGEntry.size = 0;

			mBGEntries.emplace_back(BGEntry);

		}
	}

	void BGManager::AddBuffer(Buffer& buffer, uint32_t binding, wgpu::BufferBindingType bindingType, wgpu::ShaderStage visibility)
	{
		{
			wgpu::BindGroupLayoutEntry BGLentry{};
			BGLentry.binding = binding;
			BGLentry.buffer = wgpu::BufferBindingLayout{
				nullptr, // nextInChain
				bindingType, //buffer binding type
				false, //has dynamic offset
				buffer.GetSize() //min binding size
			};
			BGLentry.visibility = visibility;

			mBGLEntries.emplace_back(BGLentry);
		}
		{
			wgpu::BindGroupEntry BGEntry;

			BGEntry.binding = binding;
			BGEntry.buffer = buffer.Get();
			BGEntry.offset = 0;
			BGEntry.size = buffer.GetSize();
			mBGEntries.emplace_back(BGEntry);

		}
	}

}

