#include "stdafx.h"
#include "Asteroid.h"

#include "AssetManager.h"
#include "Core.h"
#include "CoreTextures.h"
#include "Collider.h"
#include "GameEnums.h"

Asteroid::Asteroid()
{
}

void Asteroid::OnSpawn()
{
    Actor::OnSpawn();
    SetTexture(core->GetAssetManager().GetLoadedTexture(GameTextures::ASTEROID));
    Accelerate(Vector2f::up*50);
    collider = &*(AddComponent<Collider>());
}

void Asteroid::Update(double dTime)
{
    Actor::Update(dTime);
    
}

void Asteroid::OnBeginOverlap(SharedSceneObject other)
{
    Actor::OnBeginOverlap(other);
    other->Destroy();
}
