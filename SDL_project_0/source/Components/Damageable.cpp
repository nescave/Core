#include "stdafx.h"
#include "Damageable.h"

Damageable::Damageable() :
    maxHp(100),
    hp(maxHp)
{}

Damageable& Damageable::SetHp(int32_t newHp)
{
    hp = newHp>maxHp ? maxHp : newHp;
    return *this;
}

Damageable& Damageable::SetMaxHp(int32_t newMaxHp)
{
    maxHp = newMaxHp;
    hp = std::min(maxHp, hp);

    return *this;
}

bool Damageable::ApplyDamage(int32_t damageVal)
{
    hp-=damageVal;
    return hp>0;
}

bool Damageable::ApplyHeal(int32_t healVal)
{
    SetHp(hp+healVal);
    return hp==maxHp;
}
