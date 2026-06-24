#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
public:
    bool PointOverlaps(Vector2i& point) override;
    bool ColliderOverlaps(Collider* other) override;
};
