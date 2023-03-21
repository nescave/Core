#include "stdafx.h"
#include "RenderableComponent.h"
#include "RenderableObject.h"

RenderableComponent::RenderableComponent()
{}

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
