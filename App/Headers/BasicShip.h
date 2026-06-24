#pragma once
#include "Actor.h"
#include "DamageData.h"

class Damageable;

class BasicShip : public Actor
{
    friend class ObjectSpawner;
protected:
    float armor;
    float shield;
    BasicShip();
    class std::weak_ptr<Damageable> damageableComponent;
public:
    void OnSpawn() override;
    void TakeDamage(DamageData data, SharedSceneObject source);
    // void ReportDamage(float hullDamage, float armorDamage, float shieldDamage);

    void OnBeginOverlap(SharedSceneObject other) override;
    void Update(double dTime) override;
};
