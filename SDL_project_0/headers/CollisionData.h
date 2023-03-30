#pragma once
#include "CoreTypes.h"

struct CollisionData
{
    // Collider* collider;
    SharedSceneObject object;
    Vector2d hitPosition;
    float distance;
};
