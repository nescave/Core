#include "stdafx.h"
#include "Asteroid.h"

#include "AssetManager.h"
#include "Core.h"
#include "CoreTextures.h"
#include "Collider.h"

void Asteroid::OnSpawn()
{
    Actor::OnSpawn();
    SetTexture(core->GetAssetManager().GetLoadedTexture(CoreTexture::OrangeTriangle));
    collider = &*(AddComponent<Collider>().lock());
}
