#pragma once

enum class DamageType
{
    IMPACT,
    OVERTIME
};

struct DamageData
{
    float baseDamage;
    float armorDamage;      //fraction of base damage dealt to armor
    float shieldDamage;     //fraction of base damage dealt to shield
    float armorPiercing;    //fraction of base damage that goes through even if there still is armor
    float shieldPiercing;   //fraction of base damage that goes through even if there still is shield

    DamageType damageType;

    DamageData(float bDamage, float aDamage, float sDamage, float aPiercing, float sPiercing, DamageType dType);
};
