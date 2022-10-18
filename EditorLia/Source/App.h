#pragma once
#include "Graphics/Device.h"
#include "Layers/Layer.h"
#include "Graphics/RayTracer.h"

//Only for testing purposes
class TestApp : public Lia::Layer
{
public:
	TestApp() = default;
	~TestApp() = default;

	virtual void BeforeGameLoop(const Lia::LayerData& data) override;
	virtual void GameLoop(const Lia::LayerData& data) override;
	virtual void AfterGameLoop(const Lia::LayerData& data) override;
	virtual void OnStart() override;
	virtual void OnEnd() override;

private:

	Sptr<Lia::RayTracer> mTracer;
	Sptr<Lia::Window> mWindow;
	Sptr<Lia::World> mWorld;
	glm::vec3 BackgroudColor;
	glm::vec3 LastColor;



};