#pragma once
#include "CoreTypes.h"
#include "InputManager.h"
#include "WeaponEnums.h"

struct WeaponProperties
{
    float baseDamage;
    float armorDamage;
    float shieldDamage;
    float armorPiercing;
    float shieldPiercing;

    float projectileSpeed;
    float heatGeneration;   //per shot (maybe laser should override it to also use per second acc?)
    float heatExhaust;      //per second
    float heatMax;
    float heatSafety; //fraction of heatMax that need to be achieved before firing again after reaching heatMax

    SharedTexture ammunitionTexture;
    EActionType fireType; //maybe should create another enum to remap values and disallow "Single" action type
    explicit WeaponProperties(Weapons::Types typeDefault);
    WeaponProperties();
};
