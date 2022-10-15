#pragma once
#include "Graphics/Device.h"
#include "Layers/Layer.h"

//Only for testing purposes
class TestApp : public Lia::Layer
{
public:
	TestApp() = default;
	~TestApp() = default;

	virtual void BeforeGameLoop(const Lia::LayerData& data) override;
	virtual void GameLoop(const Lia::LayerData& data) override;
	virtual void AfterGameLoop(const Lia::LayerData& data) override;
	virtual void OnStart() override;
	virtual void OnEnd() override;

private:
	Sptr<Lia::Device> mDevice;
	Sptr<Lia::Window> mWindow;

	Sptr<Lia::ComputeShader> mCompShader;
	Sptr<Lia::Texture> mTex;
	
	Sptr<wgpu::TextureView> mTexview;
	Sptr<Lia::Buffer> mBuffer;
	
	glm::vec3 BackgroudColor;
	glm::vec3 LastColor;
	glm::vec2 RenderSize;



};