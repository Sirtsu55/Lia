#pragma once
#include "Window.h"
#include "EngineFactoryVk.h"

namespace Lia
{
	namespace dg = Diligent;
	class Tracer
	{
	public:

		struct CreateInfo
		{
			Sptr<Window> Win;
		};


		Tracer() = default;
		virtual ~Tracer() = default;



		static Sptr<Tracer> CreateComputeTracer(const CreateInfo& cInf);

	private:




	protected:
		Sptr<Window> mWindow;
		dg::IRenderDevice* mDevice;
		dg::IDeviceContext* mImmediateContext;
		dg::ISwapChain* mSwapChain;



	};

}