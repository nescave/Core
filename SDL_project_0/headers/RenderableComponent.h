#pragma once
#include "SceneComponent.h"
#include "Renderable.h"

class RenderableComponent : 
	public ComponentTransform,
	public Renderable
{
protected:

public:
	RenderableComponent();

	void OnSpawn() override;
};

