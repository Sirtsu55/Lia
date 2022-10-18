#include "App.h"
#include "Graphics/Texture.h"
#include "Graphics/ComputeShader.h"
#include "Graphics/Buffer.h"


void TestApp::OnStart()
{
    Lia::Window::Settings settings = { .Name = "LiaEngine", .Resolution = glm::ivec2(1280, 720) };

    mWindow = CreateSptr<Lia::Window>(settings);

    Lia::Device::Settings devSettings = { mWindow };
    mDevice = CreateSptr<Lia::Device>(devSettings);

	mDevice->SetupCompute();

	mCompShader = CreateSptr<Lia::ComputeShader>(mDevice->GetDevice(), "../Resources/Shaders/Compute.comp.spv");



	auto bufferUsages = wgpu::BufferUsage::Uniform;

	BackgroudColor = glm::vec3(1.0f, 0.0f, 1.0f);
	mBuffer = CreateSptr<Lia::Buffer>(mDevice->GetDevice(), bufferUsages, sizeof(glm::vec4) + sizeof(glm::vec2), glm::value_ptr(BackgroudColor));
	

	Lia::Texture::Info inf{};
	inf.Dimentions = glm::uvec2(1289, 720);
	inf.Format = wgpu::TextureFormat::RGBA16Float;
	inf.Usage = wgpu::TextureUsage::TextureBinding | wgpu::TextureUsage::StorageBinding;
	mTex = CreateSptr<Lia::Texture>(mDevice->GetDevice(), inf);
	mTexview = mTex->GetView();

	mCompShader->BindGroupManager.AddStorageTexture(GetSmartPtrAsRef<Lia::Texture>(mTex), 0);
	mCompShader->BindGroupManager.AddBuffer(GetSmartPtrAsRef<Lia::Buffer>(mBuffer), 1, wgpu::BufferBindingType::Uniform);

	RenderSize = inf.Dimentions;

	mCompShader->BindGroupManager.ConstructBindGroups(mDevice->GetDevice());

	mCompShader->CreatePipeline();
	mBuffer->UploadData(glm::value_ptr(RenderSize), sizeof(glm::vec2), sizeof(glm::vec4));

	LayerInfo |= Lia::LayerFlags::WindowOpen;

}

void TestApp::BeforeGameLoop(const Lia::LayerData& data)
{
}

void TestApp::GameLoop(const Lia::LayerData& data)
{
    mDevice->BeginFrame();
	{
		ImGui::Begin("Viewport", nullptr);
		auto winSize = ImGui::GetContentRegionAvail();
		ImGui::Image(mTex->GetView()->Get(), winSize);
		ImGui::End();
	}

	{
		ImGui::Begin("Pick Color", NULL);
		ImGui::ColorPicker3("picker", glm::value_ptr(BackgroudColor));
		ImGui::End();
	}
	if (LastColor != BackgroudColor)
	{
		mBuffer->UploadData(glm::value_ptr(RenderSize), sizeof(glm::vec2), sizeof(glm::vec4));
		mBuffer->UploadData(glm::value_ptr(BackgroudColor), sizeof(glm::vec3), 0);
	}

	LastColor = BackgroudColor;


    //LOG_INFO("Frame Time: {} ms", timer.Endd(TimerAccuracy::MilliSec));

}

void TestApp::AfterGameLoop(const Lia::LayerData& data)
{
	mDevice->DispatchCompute(mCompShader, RenderSize);
	mWindow->UpdateInput();

	if (!mWindow->IsActive())
		LayerInfo &= ~Lia::LayerFlags::WindowOpen;

	mDevice->EndFrame();
}

void TestApp::OnEnd()
{
}
