#pragma once
#include "Actor.h"
#include "Color.h"
#include "DamageData.h"
#include "FloatingTextUI.h"

class Damageable :  public Actor
{
    friend class ObjectSpawner;
protected:
    float currentHp;
    float maxHp;
    std::map<uint16_t, std::weak_ptr<FloatingTextUI>> reports;
    Damageable();
public:
    virtual ~Damageable();
    Damageable& SetHp(float val);
    Damageable& SetMaxHp(float val);
    float GetHp() const {return currentHp;}
    float GetMaxHp() const {return maxHp;}

    
    virtual void TakeDamage(DamageData data, SharedSceneObject source = nullptr) = 0;
    virtual void RecoverHp(float val);

    void ReportDamage(
        const Vector2d& position,
        float damage,
        uint16_t id,
        Color color = Color::white,
        float floatSpeed = 5,
        float fadeDelay = 1
        );
    bool IsOperational() const {return currentHp > 0;}
};
