#pragma once
#include "Actor.h"
#include "Controlable.h"
#include "WeaponComponent.h"

class InputManager;
class Text;

class PlayerShip : public Controlable, public Actor
{
private:
	WeaponComponent* weaponComp;

	Vector2f MoveVector;
	float moveAcc;
	bool bAccelerating;
	
public:
	InputManager* input;
	PlayerShip();

	// void Fire();
	void PropelRight();
	void PropelLeft();
	void Test();
	
	// void Stear();
	
	void OnSpawn() override;
	void Begin() override;
	void Update(double dTime) override;
	
};

