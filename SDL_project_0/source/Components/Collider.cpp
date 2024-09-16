#include "stdafx.h"
#include "Collider.h"
#include "RenderableObject.h"

Collider::Collider() :
    extents(),
    moved(true),
    layerMask((uint32_t)ECollisionLayer::GAME)
{}

Collider& Collider::SetExtents()
{
    auto rObj = dynamic_cast<RenderableObject*>(&*owner.lock());
    if (!rObj) return *this;
    const auto size = Vector2f(rObj->GetSize() * rObj->GetScale());
    const auto sizeFrac = Vector2f(size * rObj->GetPivot());
    return SetExtents({size.x - sizeFrac.x, sizeFrac.x, size.y - sizeFrac.y, sizeFrac.y});
}

Collider& Collider::SetExtents(ColliderExtents ext)
{
    extents = ext;
    return *this;
}

bool Collider::PointOverlaps(Vector2i&& point)
{
    return PointOverlaps(point);
}

uint32_t Collider::GetLayerMask()
{
    return layerMask;
}

Collider& Collider::SetLayerMask(uint32_t mask)
{
    layerMask = mask;
    return *this;
}

Collider& Collider::AddToLayer(uint32_t layer)
{
    layerMask = layerMask|layer;
    return *this;
}

Collider& Collider::RemoveFromLayer(uint32_t layer)
{
    layerMask = layerMask&~layer;
    return *this;
}

bool Collider::IsOnLayers(uint32_t layers)
{
    return layerMask&layers;
}

void Collider::OnSpawn()
{
    const auto ownerPtr = owner.lock();
    if (!ownerPtr) return;
    ownerPtr->RegisterCollider(weak_from_this());
	
    SetExtents();
}

