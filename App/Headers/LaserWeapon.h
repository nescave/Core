#pragma once
#include "Projectile.h"
#include "WeaponComponent.h"

class LaserWeapon : public WeaponComponent
{
private:
    std::shared_ptr<DamageSource> ray;
    bool bFiring;
public:
    LaserWeapon();
    bool Fire() override;
    void Update(double dTime) override;
};
