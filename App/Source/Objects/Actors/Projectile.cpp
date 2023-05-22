#include "stdafx.h"
#include "Projectile.h"

#include "ExplosionAnim.h"
#include "ObjectSpawner.h"

void Projectile::OnDestroy()
{
    if(damageData.damageType == DamageType::IMPACT)
        ObjectSpawner::SpawnObject<ExplosionAnim>(transform.position)->Scale(.3f);
}
