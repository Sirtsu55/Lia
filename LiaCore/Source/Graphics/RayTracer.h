#pragma once
#include "Device.h"
#include "ComputeShader.h"
#include "Texture.h"

namespace Lia
{
	class World;
	class Window;


	struct UniformBufferData
	{
		glm::vec4 bgColor;
		glm::vec2 RenderSize;
	
		void SetRenderSize(const glm::vec2& size) { RenderSize = size; }
		void SetBGColor(const glm::vec4& color) { bgColor = color; }
	};

	//Handles all the GPU data responsible for raytracing
	class RayTracer
	{
	public:
		struct Settings
		{
			glm::vec2 CanvasSize;
			Sptr<Window> OutputWindow;
			std::string RTShaderPath;
		};

		RayTracer(const Settings& info);
		~RayTracer();


		RayTracer(RayTracer&) = delete;
		RayTracer& operator=(RayTracer&) = delete;

		void TraceWorld(const Sptr<World>& world);

		void UpdateBuffers(Sptr<World>& world);
		void UpdateUniformBuffer();


		const Sptr<Texture> GetOutTexture() const { return mOutTexture; }
		const Sptr<wgpu::TextureView> GetOutTexView() const { return mOutTexView; }
		UniformBufferData& GetUniformData() { return mUniformData; }
	private:

		UniformBufferData mUniformData;

		Settings mInfo;

		Sptr<Device> mDevice;
		Sptr<ComputeShader> mShader;

		Sptr<Texture> mOutTexture;
		Sptr<wgpu::TextureView> mOutTexView;


		Sptr<Lia::Buffer> mUniformBuffer;

		Sptr<Lia::Buffer> mVoxelBuffer;
		Sptr<Lia::Buffer> mVoxelTreeBuffer;
		Sptr<Lia::Buffer> mVoxelMaterialBuffer;

	public:

	};

}