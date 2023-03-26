#pragma once
#include "Avatar.h"
#include "WeaponComponent.h"

class InputManager;
class Text;

class PlayerShip : public Avatar
{
private:
	InputManager* input;
	WeaponComponent* weaponComp;

	Vector2f MoveVector;
	float moveAcc;
	bool bAccelerating;
	
public:
	PlayerShip();

	// void Fire();
	void PropelRight();
	void PropelLeft();

	// void Stear();
	
	void OnSpawn() override;
	void Begin() override;
	void Update(double dTime) override;
	
};

