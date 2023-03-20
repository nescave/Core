#include "stdafx.h"
#include "Serf.h"
#include "Core.h"
#include "AssetManager.h"
#include "CoreTextures.h"
#include "Text.h"

void Serf::Begin()
{
}

void Serf::OnSpawn()
{
	printf("Serf's OnSpawn called\n");
	SetTexture(core->GetAssetManager().GetLoadedTexture(CoreTexture::GreenArrow));
	SetPosition({ 120,180});
	SetScale({ 5,5 });


	auto textComp = AddComponent<Text>().lock();
	textComp->SetAndUpdateText("WakuWaku").SetAnchor(Anchor::Center);
	textComp->SetScale({.3f,.3f});
	//textComp->Set
}
