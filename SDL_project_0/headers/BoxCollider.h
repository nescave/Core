#pragma once
#include "Collider.h"

class BoxCollider : Collider
{
public:
    bool PointOverlaps(Vector2i& point) override;
};
