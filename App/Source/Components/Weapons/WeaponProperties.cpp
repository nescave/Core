#include "stdafx.h"
#include "WeaponProperties.h"

#include "AssetManager.h"
#include "GameEnums.h"

WeaponProperties::WeaponProperties(Weapons::Types typeDefault)
{
    switch (typeDefault)
    {
    case Weapons::KINETIC:
        damageData.baseDamage = 10;
        damageData.armorDamage = .1f;
        damageData.shieldDamage = 0;
        damageData.armorPiercing = .25f;
        damageData.shieldPiercing = 1;
        projectileSpeed = 3500;
        shotCooldown = .1;
        heatGeneration = 1.2f;
        heatExhaust = .5f;
        heatMax = 10;
        heatSafety = .5f;
        fireType = EActionType::CONTINUOUS;
        ammunitionTexture = AssetManager::Get()->LoadTexture("res/pngs/white_dot.png", GameTextures::KINETIC_SHOT);

        if(SDL_SetTextureColorMod(&*ammunitionTexture,255,180,0))
        {
            printf("Texture coloring failed! %s\n", SDL_GetError());
        }

        break;
    case Weapons::ENERGY:
        damageData.baseDamage = 12;
        damageData.armorDamage = 1.5f;
        damageData.shieldDamage = .5F;
        damageData.armorPiercing = 0;
        damageData.shieldPiercing = 0;
        projectileSpeed = 5500;
        shotCooldown = .01;
        heatGeneration = .02f;
        heatExhaust = .75f;
        heatMax = 10;
        heatSafety = .66f;
        fireType = EActionType::CONTINUOUS;
        ammunitionTexture = AssetManager::Get()->LoadTexture("res/pngs/white_dot.png", GameTextures::ENERGY_SHOT);

        if(SDL_SetTextureColorMod(&*ammunitionTexture,128,0,228))
        {
            printf("Texture coloring failed! %s\n", SDL_GetError());
        }

        break;
    default:
        damageData.baseDamage = 0;
        damageData.armorDamage = 0;
        damageData.shieldDamage = 0;
        damageData.armorPiercing = 0;
        damageData.shieldPiercing = 0;
        projectileSpeed = 0;
        heatGeneration = 0;
        heatExhaust = 0;
        heatMax = 0;
        heatSafety = 0;
        fireType = EActionType::SINGLE;
        ammunitionTexture = nullptr;

        break;
    }
}

WeaponProperties::WeaponProperties()
{
    damageData.baseDamage = 0;
    damageData.armorDamage = 0;
    damageData.shieldDamage = 0;
    damageData.armorPiercing = 0;
    damageData.shieldPiercing = 0;
    projectileSpeed = 0;
    heatGeneration = 0;
    heatExhaust = 0;
    heatMax = 0;
    heatSafety = 0;
    fireType = EActionType::SINGLE;
    ammunitionTexture = nullptr;
}
