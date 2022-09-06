#pragma once
#include "Texture.h"

namespace Lia
{


	struct BGManager
	{

		void AddStorageTexture( 
			Texture& tex,
			uint32_t binding,
			wgpu::ShaderStage visibility = wgpu::ShaderStage::Compute)
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
		void ConstructBindGroups(const wgpu::Device& dev)
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



	private:

		wgpu::BindGroupLayout mBindGroupLayout;
		wgpu::BindGroup mBindGroup;

		std::vector<wgpu::BindGroupEntry> mBGEntries;
		std::vector<wgpu::BindGroupLayoutEntry> mBGLEntries;

		friend class ComputeShader;
	};
}