#include "stdafx.h"
#include "DamageData.h"

DamageData::DamageData(float bDamage, float aDamage, float sDamage, float aPiercing, float sPiercing, DamageType dType) :
baseDamage(bDamage),
armorDamage(aDamage),
shieldDamage(sDamage),
armorPiercing(aPiercing),
shieldPiercing(sPiercing),
damageType(dType)
{}
