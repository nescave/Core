#pragma once
#include "CoreTypes.h"
#include "DamageData.h"
#include "InputManager.h"
#include "WeaponEnums.h"

struct WeaponProperties
{
    DamageData damageData;
    float projectileSpeed;
    double shotCooldown;
    float heatGeneration;   //per second
    float heatExhaust;      //per second
    float heatMax;
    float heatSafety; //fraction of heatMax that need to be achieved before firing again after reaching heatMax
    
    SharedTexture ammunitionTexture;
    EActionType fireType; //maybe should create another enum to remap values and disallow "Single" action type
    explicit WeaponProperties(Weapons::Types typeDefault);
    WeaponProperties();
};
