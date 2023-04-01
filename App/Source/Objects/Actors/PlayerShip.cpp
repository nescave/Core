#include "stdafx.h"
#include "PlayerShip.h"
#include "Core.h"
#include "AssetManager.h"
#include "CoreTextures.h"
#include "Text.h"
#include "Collider.h"
#include "CoreActionButtons.h"
#include "DebugDraw.h"
#include "GameEnums.h"
#include "KineticWeapon.h"
#include "LaserWeapon.h"
#include "ObjectSpawner.h"
#include "PhysicsCore.h"

PlayerShip::PlayerShip() :
	input(nullptr),
	weaponComp(nullptr),
	moveAcc(.4f),
	bAccelerating(false)
{}
//
// void PlayerShip::Fire()
// {
// 	SharedActor bullet = ObjectSpawner::SpawnObject<Actor>(
// 		transform.position+ GetUpVector()*10,
// 		core->GetAssetManager().GetLoadedTexture(CoreTexture::RedDot, true),
// 		Vector2d(10,10),
// 		"bullet"
// 	);//spawn object you object spawner!
// 	ObjectSpawner::SpawnObject<Actor>(transform);
// 	bullet->AddComponent<Collider>();
// 	
// 	bullet->
// 	Accelerate(GetUpVector() *3000).
// 	SetRotation(transform.rotation).
// 	SetScale({.5f,3.0f}).
// 	Destroy(.4);
//
// }

void PlayerShip::PropelRight()
{
	AccelerateAbsolute(Vector2f::right * moveAcc);
	bAccelerating = true;
}

void PlayerShip::PropelLeft()
{
	AccelerateAbsolute(-Vector2f::right* moveAcc);
	bAccelerating = true;
}

void PlayerShip::Test()
{
	auto mousePos = input->GetPointerScreenPosition();
	auto startPos = GetAbsolutePosition()+GetUpVector()*10;
	auto direction = (mousePos-startPos).Normalize();
	auto hit = core->GetPhysicsCore().RayCast(startPos, direction, 800, ECollisionLayer::GAME);
	DebugDraw::Point(hit.second.hitPosition, 6, 2, Color::green);
	DebugDraw::Line(startPos, hit.second.hitPosition, 2.5, 2,Color::red);
	DebugDraw::Circle(transform.position, 100, 3, Color::cyan);
}

void PlayerShip::OnSpawn()
{
	Avatar::OnSpawn();
	input = InputManager::Get();
	
	SetTexture(core->GetAssetManager().GetLoadedTexture(GameTextures::MAIN_SHIP));

	SetPosition({ 640,740});
	SetScale({ .2f,.2f }).SetRotation(0);

	weaponComp = &*AddComponent<KineticWeapon>();
	
	// textComp = &*AddComponent<Text>().lock();
	// textComp->SetAndUpdateText("w").SetAnchor(Anchor::Top);
	// textComp->SetScale({.3f,.3f});

	// auto collider = AddComponent<Collider>().lock();
	ObjectSpawner::SpawnObject<Actor>(transform.position);
	// RegisterAction(ECoreActionButton::LMB, [this](){this->weaponComp->Fire();}, weaponComp->GetWeaponProperties().fireType);
	RegisterAction(ECoreActionButton::LMB, [this](){this->weaponComp->Fire();}, weaponComp->GetWeaponProperties().fireType);
	RegisterAction(ECoreActionButton::A, BINDFUNC(PropelLeft), EActionType::CONTINUOUS);
	RegisterAction(ECoreActionButton::D, BINDFUNC(PropelRight), EActionType::CONTINUOUS);
}

void PlayerShip::Begin()
{
	Avatar::Begin();
	// SetActive(false);
}

void PlayerShip::Update(double dTime)
{
	Avatar::Update(dTime);
	const double lookAtRotation = GetLookAtRotation(input->GetPointerScreenPosition()); 
	SetRotation(lookAtRotation);
	if (!bAccelerating)
	{
		speed *= .999f;
		if(speed.LengthSqr()< .01f) speed = Vector2f::zero;

	}
	bAccelerating = false;
	weaponComp->ExhaustHeat(dTime);
}