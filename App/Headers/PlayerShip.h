#pragma once
#include "Avatar.h"

class InputManager;
class Text;

class PlayerShip : public Avatar
{
private:
	InputManager* input;
	Text* textComp;

	Vector2f MoveVector;
	float moveAcc;
	bool bAccelerating;
	
public:
	PlayerShip();

	void Fire();
	void PropelRight();
	void PropelLeft();

	// void Stear();
	
	void OnSpawn() override;
	void Begin() override;
	void Update(double dTime) override;
	
};

