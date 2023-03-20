#pragma once
#include "ComponentTransform.h"
#include "Renderable.h"

class RenderableComponent : 
	public ComponentTransform,
	public Renderable
{
protected:

public:
	RenderableComponent(weak_Object own, shared_Texture tx = nullptr);
	RenderableComponent();
};

