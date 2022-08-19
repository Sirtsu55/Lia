#include "ComputeTracer.h"





namespace Lia
{
	Sptr<Tracer> Tracer::CreateComputeTracer(const CreateInfo& cInf)
	{
		return CreateSptr<ComputeTracer>(cInf);
	}

	ComputeTracer::ComputeTracer(const CreateInfo& cInf)
	{
		dg::EngineVkCreateInfo EngineCI;
		EngineCI.Features.ComputeShaders = dg::DEVICE_FEATURE_STATE::DEVICE_FEATURE_STATE_ENABLED;

		mEngineFactoryVk = dg::GetEngineFactoryVk();
		mEngineFactoryVk->CreateDeviceAndContextsVk(EngineCI, &mDevice, &mImmediateContext);

		dg::NativeWindow nativeWin;

		nativeWin.hWnd = glfwGetWin32Window(cInf.Win->GetGLFWWindow());

		dg::SwapChainDesc swapDC{};
	
		mEngineFactoryVk->CreateSwapChainVk(mDevice, mImmediateContext, swapDC, nativeWin, &mSwapChain);
		
	}

	ComputeTracer::~ComputeTracer()
	{


	}


}