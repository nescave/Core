#include "stdafx.h"
#include "WeaponComponent.h"
#include "Actor.h"

WeaponComponent::WeaponComponent() :
    currentHeat(0),
    bOverHeated(true),
    bOnCooldown(false)
{}

bool WeaponComponent::Fire()
{
    if(bOverHeated)
    {
        HeatCheckup();
        return false;
    }
    
    AccumulateHeat();
    HeatCheckup();

     return true;
}


void WeaponComponent::AccumulateHeat()
{
    currentHeat += properties.heatGeneration * (float)properties.shotCooldown;
}

void WeaponComponent::ExhaustHeat(double dTime)
{
    if(currentHeat>0)
    {
        currentHeat -= float((double)properties.heatExhaust *dTime);
        // printf("%f\n", currentHeat);
    }

}

void WeaponComponent::HeatCheckup()
{
    if(bOverHeated)
        bOverHeated = currentHeat>properties.heatMax*properties.heatSafety;
    else
        bOverHeated = currentHeat>properties.heatMax;
}

void WeaponComponent::Update(double dTime)
{
    SceneComponent::Update(dTime);
    ExhaustHeat(dTime);
}
