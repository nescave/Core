#include "stdafx.h"
#include "BasicShip.h"

#include "Core.h"
#include "FloatingTextUI.h"
#include "ObjectSpawner.h"
#include "Projectile.h"

BasicShip::BasicShip() :
    armor(100),     //temp
    shield(100)     //temp
{}

void BasicShip::TakeDamage(DamageData data, SharedSceneObject source)
{
    float finalHullDamage = data.baseDamage;
    float finalArmorDamage = finalHullDamage * data.armorDamage;
    float finalShieldDamage = finalHullDamage * data.shieldDamage; 

    if(data.damageType == DamageType::OVERTIME)
    {
        finalHullDamage *= (float)core->lastUpdateDuration;
        finalArmorDamage *= (float)core->lastUpdateDuration;
        finalShieldDamage *= (float)core->lastUpdateDuration;
    }

    if(armor>0) finalHullDamage *= data.armorPiercing;
    if(shield>0) finalHullDamage *= data.shieldPiercing;

    currentHp -= finalHullDamage;
    armor -= finalArmorDamage;
    shield -= finalShieldDamage;

    Vector2d size = GetSize()*GetAbsoluteScale();
    
    if(finalHullDamage>0)
    {
        const Vector2d hullReportPos = GetAbsolutePosition() + size * Vector2d(0,-.55);
        ReportDamage(hullReportPos, finalHullDamage, 0);
    }
    if(finalArmorDamage>0)
    {
        const Vector2d armorReportPos = GetAbsolutePosition() + size * Vector2d(-.2,-.42);
        ReportDamage(armorReportPos, finalArmorDamage, 1, Color::yellow);
    }
    if(finalShieldDamage>0)
    {
        const Vector2d shieldReportPos = GetAbsolutePosition() + size * Vector2d(.2,-.42);
        ReportDamage(shieldReportPos, finalShieldDamage,2, Color::cyan);
    }
}

void BasicShip::OnBeginOverlap(SharedSceneObject other)
{
    Actor::OnBeginOverlap(other);
}

void BasicShip::Update(double dTime)
{
    Actor::Update(dTime);
    if(!IsOperational()) Destroy();
}
