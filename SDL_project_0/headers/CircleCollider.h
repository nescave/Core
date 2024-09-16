#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{

public:
    bool PointOverlaps(Vector2i& point) override;
    bool ColliderOverlaps(Collider* other) override;
    void OnSpawn() override;
};
