#include "stdafx.h"
#include "KineticWeapon.h"
#include "ObjectSpawner.h"
#include "Projectile.h"
#include "Collider.h"

KineticWeapon::KineticWeapon()
{
    properties = WeaponProperties(Weapons::KINETIC);
}

bool KineticWeapon::Fire()
{
    if(!WeaponComponent::Fire()) return false;

    if(bOnCooldown)
    {
        return false;
    }
    bOnCooldown = true;
    owner.lock()->SetupTask(properties.shotCooldown, [=](){this->bOnCooldown = false;});
    
    Transform spawnTrans = GetAbsoluteTransform();
    spawnTrans.position += GetUpVector() * 10;
    const auto projectile = ObjectSpawner::SpawnObject<Projectile>(spawnTrans);
    projectile->source = owner.lock();
    projectile->damageData = properties.damageData;
    projectile->
        SetTexture(properties.ammunitionTexture);
    projectile->
        Accelerate(Vector2f::up * properties.projectileSpeed).
        SetScale({.2f,.5f}).
        AddComponent<Collider>();
    projectile->Destroy(.5);

    return true;
}
