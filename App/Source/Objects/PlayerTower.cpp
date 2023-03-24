#include "stdafx.h"
#include "PlayerTower.h"
#include "Core.h"
#include "AssetManager.h"
#include "CoreTextures.h"
#include "Text.h"
#include "Collider.h"
#include "CoreActionButtons.h"
#include "GameEnums.h"
#include "ObjectSpawner.h"

PlayerTower::PlayerTower() :
	input(nullptr),
	textComp(nullptr),
	moveAcc(.004f),
	bAccelerating(false)
{}

void PlayerTower::Fire()
{
	SharedActor bullet = ObjectSpawner::SpawnObject<Actor>(
		transform.position+ GetUpVector()*10,
		core->GetAssetManager().GetLoadedTexture(CoreTexture::RedDot, true),
		Vector2d(10,10),
		"bullet"
	);//spawn object you object spawner!

	bullet->
	Accelerate(GetUpVector() *3000).
	SetRotation(transform.rotation).
	SetScale({.5f,3.0f}).
	Destroy(.4);
	
}

void PlayerTower::PropelRight()
{
	AccelerateAbsolute(Vector2f::right * moveAcc);
	bAccelerating = true;
}

void PlayerTower::PropelLeft()
{
	AccelerateAbsolute(-Vector2f::right* moveAcc);
	bAccelerating = true;
}

void PlayerTower::OnSpawn()
{
	Avatar::OnSpawn();
	input = InputManager::Get();
	
	SetTexture(core->GetAssetManager().GetLoadedTexture(GameTextures::MAIN_SHIP));

	SetPosition({ 640,740});
	SetScale({ .2f,.2f }).SetRotation(0);

	// textComp = &*AddComponent<Text>().lock();
	// textComp->SetAndUpdateText("w").SetAnchor(Anchor::Top);
	// textComp->SetScale({.3f,.3f});

	// auto collider = AddComponent<Collider>().lock();

	RegisterAction(ECoreActionButton::LMB, [this](){this->Fire();}, EActionType::REPETABLE);
	RegisterAction(ECoreActionButton::A, BINDFUNC(PropelLeft), EActionType::CONTINUOUS);
	RegisterAction(ECoreActionButton::D, BINDFUNC(PropelRight), EActionType::CONTINUOUS);
}

void PlayerTower::Begin()
{
	Avatar::Begin();
	// SetActive(false);
}

void PlayerTower::Update(double dTime)
{
	Avatar::Update(dTime);
	const double lookAtRotation = GetLookAtRotation(input->GetPointerScreenPosition()); 
	SetRotation(lookAtRotation);
	if (!bAccelerating)
	{
		speed *= .99f;
		if(speed.LengthSqr()< .01f) speed = Vector2f::zero;

	}
	bAccelerating = false;
}
