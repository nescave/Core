#include "stdafx.h"
#include "RenderableComponent.h"
#include "RenderObject.h"

RenderableComponent::RenderableComponent(weak_Object own, shared_Texture tx) :
	ComponentTransform(own)
{
	auto lOwner = &*own.lock();
	if (lOwner) 
	{
		RenderObject* rObj = static_cast<RenderObject*>(lOwner);
		sortingPriority = rObj->GetSortingPriority();
	}
}

RenderableComponent::RenderableComponent() :
	RenderableComponent(weak_Object())
{}
