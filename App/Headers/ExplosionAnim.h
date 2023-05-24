#pragma once
#include "Actor.h"

class ExplosionAnim : public Actor
{
public:
    void Update(double dTime) override;
    void OnSpawn() override;
};
