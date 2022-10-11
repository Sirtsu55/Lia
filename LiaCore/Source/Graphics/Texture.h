#pragma once

namespace Lia
{
	class Texture
	{
		
	public:
		struct Info
		{
			uint8_t MipMaps = 1;
			glm::uvec2 Dimentions;
			wgpu::TextureFormat Format = wgpu::TextureFormat::RGBA8Unorm;
			wgpu::TextureUsage Usage;
			void* data;
		};


		Texture(const wgpu::Device& dev,const Info& texInfo);
		~Texture();
		Texture(Texture&) = delete;
		Texture& operator=(Texture&) = delete;

		wgpu::Texture Get() const { return mTexture; }

		wgpu::TextureFormat GetFormat() const { return mTextureDesc.format; }
		Sptr<wgpu::TextureView> GetView();

		void Resize(const wgpu::Device& dev, const glm::uvec2& newSize);


	private:
		Sptr<wgpu::TextureView> mDefaultTexView;
		wgpu::TextureDescriptor mTextureDesc;
		wgpu::Texture mTexture;
	};

}