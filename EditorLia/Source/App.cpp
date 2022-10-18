#include "App.h"
#include "Graphics/Texture.h"
#include "Graphics/ComputeShader.h"
#include "Graphics/Buffer.h"
#include "GameWorld/World.h"

void TestApp::OnStart()
{
    Lia::Window::Settings winSettings = { .Name = "LiaEngine", .Resolution = glm::ivec2(1280, 720) };

    mWindow = CreateSptr<Lia::Window>(winSettings);
	mWorld = CreateSptr<Lia::World>();

	Lia::RayTracer::Settings rtSettings = {
		.CanvasSize = glm::vec2(1280, 720),
		.OutputWindow = mWindow,
		.RTShaderPath = "../Resources/Shaders/Compute.comp.spv" 
	};

	mTracer = CreateSptr<Lia::RayTracer>(rtSettings);

	BackgroudColor = glm::vec3(1.0f, 0.0f, 1.0f);

	auto& data = mTracer->GetUniformData();
	data.bgColor = glm::vec4(BackgroudColor, 0.0);
	data.RenderSize = glm::vec2(rtSettings.CanvasSize);
	mTracer->UpdateUniformBuffer();

	{
		std::vector<Lia::Voxel> voxels(25);
		for (int i = 0; i < 25; i++)
		{
				voxels[i].Position = glm::vec3(i, 0, -10);


		}

		mWorld->AddVoxels(voxels);
	}



	LayerInfo |= Lia::LayerFlags::WindowOpen;

}

void TestApp::BeforeGameLoop(const Lia::LayerData& data)
{
}

void TestApp::GameLoop(const Lia::LayerData& data)
{
	//Setup Imgui for new frame
	ImGui_ImplWGPU_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	{
		ImGui::Begin("Viewport", nullptr);
		auto winSize = ImGui::GetContentRegionAvail();
		ImGui::Image(mTracer->GetOutTexView()->Get(), winSize);
		ImGui::End();
	}

	{
		ImGui::Begin("Pick Color", NULL);
		ImGui::ColorPicker3("picker", glm::value_ptr(BackgroudColor));
		ImGui::End();
	}
	if (LastColor != BackgroudColor)
	{
		auto& data = mTracer->GetUniformData();
		data.bgColor = glm::vec4(BackgroudColor, 0.0);
		mTracer->UpdateUniformBuffer();
	}

	LastColor = BackgroudColor;


    //LOG_INFO("Frame Time: {} ms", timer.Endd(TimerAccuracy::MilliSec));

}

void TestApp::AfterGameLoop(const Lia::LayerData& data)
{
	mTracer->TraceWorld(mWorld);

	mWindow->UpdateInput();

	if (!mWindow->IsActive())
		LayerInfo &= ~Lia::LayerFlags::WindowOpen;

	//TODO: Abstract low level Device code to different layer
}

void TestApp::OnEnd()
{
}
