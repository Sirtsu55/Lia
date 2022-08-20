#pragma once
#include "Tracer.h"

namespace Lia
{

	

	class ComputeTracer : public Tracer
	{
	public:

		//Do not use this method, Create the ComputeTracer from Lia::Tracer::CreateComputeTracer
		ComputeTracer(const CreateInfo& cInf);
		~ComputeTracer();


		void BeginFrame() override;
		void EndFrame() override;
	

		
	private:

	};

}

