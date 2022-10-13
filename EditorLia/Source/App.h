#pragma once
#include "Graphics/Device.h"


//Only for testing purposes
class TestApp
{
public:
	TestApp() = default;
	~TestApp() = default;

	void Start();

	void OnUpdate();

	void Destroy();

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

	friend int main();


};