#pragma once
#include "Layers/Layer.h"

namespace Lia
{

	//This is the layer for the editor, It will handle GUI and other stuff

	class EditorLayer : public Lia::Layer
	{
	public:
		EditorLayer();

		virtual ~EditorLayer();

		virtual void BeforeGameLoop(const LayerData& data) override;
		virtual void AfterGameLoop(const LayerData& data) override;
		virtual void GameLoop(const LayerData& data) override;
		virtual void OnStart() override;
		virtual void OnEnd() override;
	private:

	};

}