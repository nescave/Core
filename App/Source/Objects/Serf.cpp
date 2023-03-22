#include "stdafx.h"
#include "Serf.h"
#include "Core.h"
#include "AssetManager.h"
#include "CoreTextures.h"
#include "Text.h"
#include "Collider.h"
#include "InputManager.h"
#include "CoreActionButtons.h"

Serf::Serf() :
	input(nullptr),
	textComp(nullptr)
{}

void Serf::Begin()
{
}

void Serf::Serf_F()
{
	printf(("wakuwaku\n"));
}

void Serf::OnSpawn()
{
	input = InputManager::Get();
	
	printf("Serf's OnSpawn called\n");
	SetTexture(core->GetAssetManager().GetLoadedTexture(CoreTexture::GreenArrow));
	SetPosition({ 620,480});
	SetScale({ 10,10 }).SetRotation(0);

	textComp = &*AddComponent<Text>().lock();
	textComp->SetAndUpdateText("w").SetAnchor(Anchor::Top);
	textComp->SetScale({.3f,.3f});

	auto collider = AddComponent<Collider>().lock();

	// InputManager::RegisterAction(ECoreActionButton::LMB, [this](){this->Serf_F();});
}

void Serf::Update(double dTime)
{
	Actor::Update(dTime);
	const double lookAtRotation = GetLookAtRotation(input->GetPointerScreenPosition()); 
	if((int)GetRotation() != (int)lookAtRotation)
	{
		SetRotation(lookAtRotation);
		textComp->SetAndUpdateText(std::to_string(lookAtRotation));
	}
	
}
