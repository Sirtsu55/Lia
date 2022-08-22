#include "ComputeTracer.h"




namespace Lia
{
	Sptr<Tracer> Tracer::CreateComputeTracer(const CreateInfo& cInf)
	{
		return CreateSptr<ComputeTracer>(cInf);
	}



	ComputeTracer::ComputeTracer(const CreateInfo& cInf)
	{
		dg::EngineVkCreateInfo EngineCI{};
#ifndef NDEBUG
		EngineCI.EnableValidation = true;
		EngineCI.ValidationFlags = dg::VALIDATION_FLAGS::VALIDATION_FLAG_CHECK_SHADER_BUFFER_SIZE;
		//EngineCI.SetValidationLevel(dg::VALIDATION_LEVEL::VALIDATION_LEVEL_2);
#endif // NDEBUG



		EngineCI.Features.ComputeShaders = dg::DEVICE_FEATURE_STATE::DEVICE_FEATURE_STATE_ENABLED;

		mEngineFactoryVk = dg::GetEngineFactoryVk();
		mEngineFactoryVk->CreateDeviceAndContextsVk(EngineCI, &mDevice, &mContext);

		dg::NativeWindow nativeWin;
#ifdef WIN32
		nativeWin.hWnd = glfwGetWin32Window(cInf.Win->GetGLFWWindow());
#endif // WIN32


		dg::SwapChainDesc swapDC{};

		mEngineFactoryVk->CreateSwapChainVk(mDevice, mContext, swapDC, nativeWin, &mSwapChain);
	
		
	}

	ComputeTracer::~ComputeTracer()
	{


	}

	void ComputeTracer::BeginFrame()
	{
		auto* pRTV = mSwapChain->GetCurrentBackBufferRTV();
		auto* pDSV = mSwapChain->GetDepthBufferDSV();
		mContext->SetRenderTargets(1, &pRTV, pDSV, dg::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

		// Clear the back buffer
		const float ClearColor[] = { 0.350f, 0.350f, 0.350f, 1.0f };
		// Let the engine perform required state transitions
		mContext->ClearRenderTarget(pRTV, ClearColor, dg::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
		mContext->ClearDepthStencil(pDSV, dg::CLEAR_DEPTH_FLAG, 1.f, 0, dg::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
		mContext->Flush();

	}

	void ComputeTracer::EndFrame()
	{
		mContext->FinishFrame();
		mSwapChain->Present(0);
	}

	void ComputeTracer::DrawTriangle()
	{
		if (!pipelineInitialized)
		{
			pipelineInitialized = true;

			dg::GraphicsPipelineStateCreateInfo PSOcreate{};

			PSOcreate.PSODesc.Name = "Triangle PSO";
			PSOcreate.PSODesc.PipelineType = dg::PIPELINE_TYPE_GRAPHICS;

			PSOcreate.GraphicsPipeline.NumRenderTargets = 1;
			PSOcreate.GraphicsPipeline.PrimitiveTopology = dg::PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			PSOcreate.GraphicsPipeline.RasterizerDesc.CullMode = dg::CULL_MODE_NONE;
			PSOcreate.GraphicsPipeline.DepthStencilDesc.DepthEnable = false;


			dg::ShaderCreateInfo shaderCI;
			shaderCI.SourceLanguage = dg::SHADER_SOURCE_LANGUAGE_HLSL;
			shaderCI.UseCombinedTextureSamplers = true;

			{
				std::cout << std::filesystem::current_path().string();
				pxSdr = CreateSptr<dg::IShader*>();
				shaderCI.EntryPoint = "main";
				shaderCI.Desc.ShaderType = dg::SHADER_TYPE_PIXEL;

				mDevice->CreateShader(shaderCI, pxSdr.get());
			}



		}
	}


}