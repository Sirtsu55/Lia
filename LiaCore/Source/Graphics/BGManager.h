#pragma once

namespace Lia
{
	class Texture;
	class Buffer;

	struct BGManager
	{

		void ConstructBindGroups(const wgpu::Device& dev);


		void AddStorageTexture(Texture& tex,
			uint32_t binding,
			wgpu::ShaderStage visibility = wgpu::ShaderStage::Compute);

		void AddBuffer(Buffer& buffer,
			uint32_t binding,
			wgpu::BufferBindingType bindingType,
			wgpu::ShaderStage visibility = wgpu::ShaderStage::Compute);

	private:

		wgpu::BindGroupLayout mBindGroupLayout;
		wgpu::BindGroup mBindGroup;

		std::vector<wgpu::BindGroupEntry> mBGEntries;
		std::vector<wgpu::BindGroupLayoutEntry> mBGLEntries;

		friend class ComputeShader;
	};
}