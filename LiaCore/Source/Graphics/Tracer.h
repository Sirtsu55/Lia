#pragma once
#include "Window.h"

namespace Lia
{
	class Tracer
	{
	public:
		Tracer();
		~Tracer();

	private:
		virtual void CreateDevice() = 0;




	protected:
		Sptr<Window> mWindow;
		


	};

}