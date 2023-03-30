#include "stdafx.h"
#include "WeaponComponent.h"
#include "Actor.h"
#include "ObjectSpawner.h"
#include "Collider.h"

WeaponComponent::WeaponComponent() :
    currentHeat(0),
    bOverHeated(true)
{}

Actor* WeaponComponent::Fire()
{
    if(bOverHeated)
    {
        HeatCheckup();
        return nullptr;
    }
    Transform spawnTrans = GetWorldTransform();
    spawnTrans.position += GetUpVector() * 10;
    const auto projectile = ObjectSpawner::SpawnObject<Actor>(spawnTrans);
    projectile->
        SetTexture(properties.ammunitionTexture);
    
    projectile->
        Accelerate(Vector2f::up * properties.projectileSpeed).
        SetScale({.2f,.5f}).
        AddComponent<Collider>();

    projectile->Destroy(.5);
    
    AccumulateHeat();
    HeatCheckup();

    return &*projectile;
}

void WeaponComponent::AccumulateHeat()
{
    currentHeat += properties.heatGeneration;
}

void WeaponComponent::ExhaustHeat(double dTime)
{
    if(currentHeat>0)
        currentHeat -= float((double)properties.heatExhaust *dTime);
}

void WeaponComponent::HeatCheckup()
{
    if(bOverHeated)
        bOverHeated = currentHeat>properties.heatMax*properties.heatSafety;
    else
        bOverHeated = currentHeat>properties.heatMax;
}
