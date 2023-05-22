#pragma once
#include "DamageSource.h"

class Projectile : public DamageSource
{
public:
    void OnDestroy() override;
};
