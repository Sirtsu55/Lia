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


		virtual void DrawTriangle() = 0;


		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;
	private:




	protected:
		Sptr<Window> mWindow;
		dg::IRenderDevice* mDevice;
		dg::IDeviceContext* mContext;
		dg::IEngineFactoryVk* mEngineFactoryVk;

		dg::ISwapChain* mSwapChain;



	};

}