#pragma once
#include <memory>

#include "CoreTypes.h"
#include "DamageData.h"

#include "Actor.h"
#include "Damageable.h"

class DamageSource : public Actor
{

public:
    DamageData damageData;
    SharedSceneObject source;
    std::shared_ptr<Damageable> target;
    void OnBeginOverlap(SharedSceneObject other) override;
    void OnEndOverlap(SharedSceneObject other) override;
    void DealDamage();
};
