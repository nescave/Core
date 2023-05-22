#include "stdafx.h"
#include "LaserWeapon.h"

#include "Actor.h"
#include "BasicShip.h"
#include "Core.h"
#include "ObjectSpawner.h"
#include "PhysicsCore.h"
#include "PlayerShip.h"
#include "Projectile.h"

LaserWeapon::LaserWeapon() :
    bFiring(false)
{
    properties = WeaponProperties(Weapons::ENERGY);
}

bool LaserWeapon::Fire()
{
    auto ship = std::dynamic_pointer_cast<PlayerShip>(owner.lock());
    auto mousePos = ship->input->GetPointerScreenPosition();
    auto direction = (mousePos - GetPosition()).Normalize();
    auto hit = core->GetPhysicsCore().RayCast(GetPosition(), direction, 800, ECollisionLayer::GAME);
    
    if(!ray)
    {
        ray = ObjectSpawner::SpawnObject<DamageSource>(GetAbsoluteTransform().position);
        ray->SetTexture(properties.ammunitionTexture);
        ray->SetPivot({.5,1});
    }

    ray->SetSize({4, (double)hit.second.distance});
    ray->SetRotation(owner.lock()->GetRotation());

    if(hit.first)
    {
        auto target =  std::dynamic_pointer_cast<BasicShip>(hit.second.object);
        if(target)
        {
            target->TakeDamage()
        }
    }

    bFiring = true;
    return true;
}

void LaserWeapon::Update(double dTime)
{
    WeaponComponent::Update(dTime);
    if(!bFiring && ray != nullptr)
    {
        ray->Destroy();
        ray = nullptr;
    }
    bFiring = false;
}
