#include "stdafx.h"
#include "CircleCollider.h"
#include "RenderableObject.h"



bool CircleCollider::PointOverlaps(Vector2i& point)
{
    const float dist = Vector2f::Distance(point, this->GetPosition());
    return dist < extents.GetMaxValue();
}

bool CircleCollider::ColliderOverlaps(Collider* other)
{
    return Vector2f::Distance(other->GetPosition(), this->GetPosition()) < (other->GetExtents().GetMaxValue() + this->GetExtents().GetMaxValue()); 
}

