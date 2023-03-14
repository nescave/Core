#include "stdafx.h"
#include "Serf.h"
#include "Core.h"
#include "AssetManager.h"
#include "CoreTextures.h"

void Serf::Begin()
{
}

void Serf::OnSpawn()
{
	printf("Serf's OnSpawn called\n");
	SetTexture(core->GetAssetManager().GetLoadedTexture(CoreTexture::GreenArrow));
	SetPosition({ 120,180});
	SetScale({ 2,2 });
}
