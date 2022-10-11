#include "Texture.h"

namespace Lia
{
	Texture::Texture(const wgpu::Device& dev, const Info& texInfo)
	{
		mTextureDesc.size = wgpu::Extent3D{ .width = texInfo.Dimentions.x, .height = texInfo.Dimentions.y, .depthOrArrayLayers = 1 };
		mTextureDesc.format = texInfo.Format;
		mTextureDesc.usage = texInfo.Usage;
		mTextureDesc.mipLevelCount = texInfo.MipMaps;
		mTextureDesc.dimension = wgpu::TextureDimension::e2D;
		mTextureDesc.viewFormats = &texInfo.Format;
		mTextureDesc.viewFormatCount = 1;
		mTexture = dev.CreateTexture(&mTextureDesc);
	}

	Texture::~Texture()
	{
	}

	Sptr<wgpu::TextureView> Texture::GetView()
	{
		//wgpu::TextureViewDescriptor texDesc{};
		//texDesc.aspect = wgpu::TextureAspect::All;
		//texDesc.baseMipLevel = 0;
		//texDesc.dimension = wgpu::TextureViewDimension::e2D;
		//texDesc.mipLevelCount = 1;
		//texDesc.format = mTextureDesc.format;
		if (mDefaultTexView.get() == nullptr)
		{
			mDefaultTexView = CreateSptr<wgpu::TextureView>();
			*mDefaultTexView.get() = std::move(mTexture.CreateView());
		}
		return mDefaultTexView;
	}

	void Texture::Resize(const wgpu::Device& dev, const glm::uvec2& newSize)
	{
		mTexture.Destroy();
		mDefaultTexView = nullptr;
		mTextureDesc.size = { .width = newSize.x, .height = newSize.y, .depthOrArrayLayers = 1 };
		mTexture = dev.CreateTexture(&mTextureDesc);
	}

}