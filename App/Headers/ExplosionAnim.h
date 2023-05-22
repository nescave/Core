#pragma once
#include "Actor.h"
#include "RenderableObject.h"

class ExplosionAnim : public Actor
{
public:
    void Update(double dTime) override;
    void OnSpawn() override;
};
