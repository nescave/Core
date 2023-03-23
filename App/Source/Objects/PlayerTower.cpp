#include "stdafx.h"
#include "PlayerTower.h"
#include "Core.h"
#include "AssetManager.h"
#include "CoreTextures.h"
#include "Text.h"
#include "Collider.h"
#include "CoreActionButtons.h"
#include "ObjectSpawner.h"

PlayerTower::PlayerTower() :
	input(nullptr),
	textComp(nullptr),
	moveAcc(.004f),
	bAccelerating(false)
{}

void PlayerTower::Fire()
{
	printf("WakuWaku\n");

	SharedActor bullet = ObjectSpawner::SpawnObject<Actor>(
		transform.position+ GetUpVector()*10,
		core->GetAssetManager().GetLoadedTexture(CoreTexture::RedDot),
		Vector2d(10,10),
		"bullet"
	).lock();//spawn object you object spawner!

	bullet->SetRotation(transform.rotation).SetScale({.5f,3.0f});
	bullet->AccelerateAbsolute(bullet->GetUpVector() *10);
	
}

void PlayerTower::MoveRight()
{
	printf("RIGHT\n");
	
	AccelerateAbsolute(Vector2f::right * moveAcc);
	bAccelerating = true;
}

void PlayerTower::MoveLeft()
{
	printf("LEFT\n");

	AccelerateAbsolute(-Vector2f::right* moveAcc);
	bAccelerating = true;
}

void PlayerTower::OnSpawn()
{
	input = InputManager::Get();
	
	SetTexture(core->GetAssetManager().GetLoadedTexture(CoreTexture::GreenArrow));
	SetPosition({ 640,740});
	SetScale({ 2,5 }).SetRotation(0);

	textComp = &*AddComponent<Text>().lock();
	textComp->SetAndUpdateText("w").SetAnchor(Anchor::Top);
	textComp->SetScale({.3f,.3f});

	auto collider = AddComponent<Collider>().lock();

	RegisterAction(ECoreActionButton::LMB, [this](){this->Fire();}, EActionType::REPETABLE);
	RegisterAction(ECoreActionButton::A, BINDFUNC(MoveLeft), EActionType::CONTINUOUS);
	RegisterAction(ECoreActionButton::D, BINDFUNC(MoveRight), EActionType::CONTINUOUS);
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
	if((int)GetRotation() != (int)lookAtRotation)
	{
		SetRotation(lookAtRotation);
	}
	if (!bAccelerating)
	{
		speed *= .99f;
		if(speed.LengthSqr()< .01f) speed = Vector2f::zero;

	}
	bAccelerating = false;
}
