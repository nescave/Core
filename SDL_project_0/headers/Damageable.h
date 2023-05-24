#pragma once
#include "Component.h"

class Damageable : public Component
{
    int32_t maxHp;
    int32_t hp;
public:

    Damageable();
    Damageable& SetHp(int32_t newHp);
    Damageable& SetMaxHp(int32_t newMaxHp);
    
    const int32_t GetHpValue() const {return hp;}

    //applies damage and returns hp>0
    bool ApplyDamage(int32_t damageVal);
    //applies heal and returns hp==maxHp
    bool ApplyHeal(int32_t healVal);
};
