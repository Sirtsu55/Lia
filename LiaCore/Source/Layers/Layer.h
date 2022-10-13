

namespace Lia
{

	struct LayerData
	{
		
	};
	//Base interface for any layers that will go into Lia
	//eg. Rendering layer, editor, widgets, physics
	class Layer
	{
	public:
		Layer() = 0;
		virtual ~Layer() = 0;

		virtual void BeforeGameLoop(const LayerData& data) = 0;
		virtual void AfterGameLoop(const LayerData& data) = 0;
		virtual void OnStart() = 0;
		virtual void OnEnd() = 0;

	protected:


	};

}