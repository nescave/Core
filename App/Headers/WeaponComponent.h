#pragma once
#include "SceneComponent.h"
#include "WeaponProperties.h"

class WeaponComponent : public SceneComponent
{
protected:
    WeaponProperties properties;
    float currentHeat;
    bool bOverHeated;
    bool bOnCooldown;

public:
    WeaponComponent(); //TODO have to finally make all object and component constructors private or protected

    virtual Actor* Fire();

    virtual void AccumulateHeat();
    virtual void ExhaustHeat(double dTime);
    virtual void HeatCheckup();
    bool IsOverheated() const {return bOverHeated;}
    WeaponProperties& GetWeaponProperties(){return properties;}
};
