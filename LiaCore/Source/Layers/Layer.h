#pragma once

namespace Lia
{
	class Texture;

	struct LayerData
	{
		Sptr<Texture> RenderedImage = nullptr;
	};
	//Base interface for any layers that will go into Lia
	//eg. Rendering layer, editor, widgets, physics
	class Layer
	{
	public:
		Layer() {};
		virtual ~Layer() {};

		virtual void BeforeGameLoop(const LayerData& data){};
		virtual void GameLoop(const LayerData& data) {};
		virtual void AfterGameLoop(const LayerData& data) {};
		virtual void OnStart() {};
		virtual void OnEnd() {};
		


		uint32_t GetRequestedData() const { return RequestedData; }
		uint32_t GetLayerInfo() const { return LayerInfo; }
	protected:

		//bit flag of what kind of data this layer needs
		uint32_t RequestedData = 0;
		uint32_t LayerInfo = 0;



	};
	namespace LayerFlags
	{
		enum LayerFlag
		{
			WindowOpen = 0b1,
			LayerActive = 0b01
		};
	}

}