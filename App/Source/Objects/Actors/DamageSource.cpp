#include "DamageSource.h"

void DamageSource::OnBeginOverlap(SharedSceneObject other)
{
    Actor::OnBeginOverlap(other);
    auto cast = std::dynamic_pointer_cast<Damageable>(other);
    if(cast) target = cast;
}

void DamageSource::OnEndOverlap(SharedSceneObject other)
{
    Actor::OnEndOverlap(other);
    if(target) target = nullptr;
}

void DamageSource::DealDamage()
{
    if(target)
        target->TakeDamage(damageData, source);
}
