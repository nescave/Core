#include "stdafx.h"
#include "LaserWeapon.h"

#include "Actor.h"

LaserWeapon::LaserWeapon()
{
    properties = WeaponProperties(Weapons::ENERGY);
}

Actor* LaserWeapon::Fire()
{
    const auto projectile = WeaponComponent::Fire();
    if(!projectile) return nullptr;
    // projectile->name = "laserParticle";
    projectile->SetScale({.1f,1});
    return projectile;
}
