#include "stdafx.h"
#include "RenderableComponent.h"
#include "RenderableObject.h"

RenderableComponent::RenderableComponent()
{}

SDL_Rect RenderableComponent::GetDstRect()
{
	auto wTrans = GetAbsoluteTransform();
	Vector2d scrSize = GetSize() * wTrans.scale;
	return SDL_Rect{
		int(wTrans.position.x - scrSize.x * (double)wTrans.pivot.x),
		int(wTrans.position.y - scrSize.y * (double)wTrans.pivot.y),
		int(scrSize.x),
		int(scrSize.y)
	};
}

void RenderableComponent::OnSpawn()
{
	SceneComponent::OnSpawn();
	auto lOwner = owner.lock();
	if (lOwner)
	{
		RenderableObject* rObj = static_cast<RenderableObject*>(&*lOwner);
		sortingPriority = rObj->GetSortingPriority() -1;
	}
}
