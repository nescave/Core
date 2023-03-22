#include "stdafx.h"
#include "Serf.h"
#include "Core.h"
#include "AssetManager.h"
#include "CoreTextures.h"
#include "Text.h"
#include "Collider.h"
#include "InputManager.h"
#include "CoreActionButtons.h"

void Serf::Begin()
{
}

void Serf::Update(double dTime)
{
	Actor::Update(dTime);
	printf("wakuwaku\n");
}

void Serf::Serf_F()
{
	printf(("wakuwaku\n"));
}

void Serf::OnSpawn()
{
	
	printf("Serf's OnSpawn called\n");
	SetTexture(core->GetAssetManager().GetLoadedTexture(CoreTexture::GreenArrow));
	SetPosition({ 620,480});
	SetScale({ 10,10 }).SetRotation(0);

	auto textComp = AddComponent<Text>().lock();
	textComp->SetAndUpdateText("w").SetAnchor(Anchor::Top);
	textComp->SetScale({.3f,.3f});

	auto collider = AddComponent<Collider>().lock();

	InputManager::RegisterAction(ECoreActionButton::LMB, [this](){this->Serf_F();});
}
