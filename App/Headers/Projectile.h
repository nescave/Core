#pragma once
#include "CoreTypes.h"
#include "DamageData.h"

class Projectile
{
public:
    DamageData damageData;
    SharedActor source;
};
