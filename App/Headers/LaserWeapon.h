#pragma once
#include "WeaponComponent.h"

class LaserWeapon : public WeaponComponent
{
public:
    LaserWeapon();
    Actor* Fire() override;
    
};
