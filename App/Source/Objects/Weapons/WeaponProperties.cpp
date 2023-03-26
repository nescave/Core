#include "stdafx.h"
#include "WeaponProperties.h"

#include "AssetManager.h"
#include "GameEnums.h"

WeaponProperties::WeaponProperties(Weapons::Types typeDefault)
{
    switch (typeDefault)
    {
    case Weapons::KINETIC:
        baseDamage = 10;
        armorDamage = .1f;
        shieldDamage = 0;
        armorPiercing = .25f;
        shieldPiercing = 1;
        projectileSpeed = 3500;
        heatGeneration = 1;
        heatExhaust = 1.5f;
        heatMax = 10;
        heatSafety = .5f;
        fireType = EActionType::REPETABLE;
        ammunitionTexture = AssetManager::Get()->LoadTexture("res/pngs/white_dot.png", GameTextures::KINETIC_SHOT);

        if(SDL_SetTextureColorMod(&*ammunitionTexture,255,180,0))
        {
            printf("Texture coloring failed! %s\n", SDL_GetError());
        }

        break;
    case Weapons::ENERGY:
        baseDamage = 12;
        armorDamage = 1.5f;
        shieldDamage = .5F;
        armorPiercing = 0;
        shieldPiercing = 0;
        projectileSpeed = 5500;
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
        baseDamage = 0;
        armorDamage = 0;
        shieldDamage = 0;
        armorPiercing = 0;
        shieldPiercing = 0;
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
    baseDamage = 0;
    armorDamage = 0;
    shieldDamage = 0;
    armorPiercing = 0;
    shieldPiercing = 0;
    projectileSpeed = 0;
    heatGeneration = 0;
    heatExhaust = 0;
    heatMax = 0;
    heatSafety = 0;
    fireType = EActionType::SINGLE;
    ammunitionTexture = nullptr;
}
