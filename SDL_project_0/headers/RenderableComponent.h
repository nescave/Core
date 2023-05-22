#pragma once
#include "SceneComponent.h"
#include "Renderable.h"

class RenderableComponent : 
	public SceneComponent,
	public Renderable
{
protected:

public:
	RenderableComponent();

	SDL_Rect GetDstRect() override;
	void OnSpawn() override;
};

