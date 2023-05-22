#pragma once
#include "Actor.h"
#include "Damageable.h"

class BasicShip : public Damageable
{
    friend class ObjectSpawner;
protected:
    float armor;
    float shield;
    BasicShip();
    
public:
    void TakeDamage(DamageData data, SharedSceneObject source) override;
    // void ReportDamage(float hullDamage, float armorDamage, float shieldDamage);

    void OnBeginOverlap(SharedSceneObject other) override;
    void Update(double dTime) override;
};
