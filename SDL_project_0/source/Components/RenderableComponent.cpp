#include "stdafx.h"
#include "RenderableComponent.h"
#include "RenderableObject.h"

RenderableComponent::RenderableComponent()
{}

void RenderableComponent::OnSpawn()
{
	ComponentTransform::OnSpawn();
	auto lOwner = owner.lock();
	if (lOwner)
	{
		RenderObject* rObj = static_cast<RenderObject*>(&*lOwner);
		sortingPriority = rObj->GetSortingPriority() -1;
	}
}
