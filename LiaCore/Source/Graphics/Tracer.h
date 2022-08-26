#pragma once
#include "Window.h"

namespace Lia
{
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




	};

}