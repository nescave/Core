#pragma once
#include "Avatar.h"

#define BINDFUNC(f) [this](){this->f();}

class InputManager;
class Text;

class PlayerTower : public Avatar
{
private:
	InputManager* input;
	Text* textComp;

	Vector2f MoveVector;
	float moveAcc;
	bool bAccelerating;
	
public:
	PlayerTower();

	void Waku();
	void MoveRight();
	void MoveLeft();

	// void Stear();
	
	void OnSpawn() override;
	void Begin() override;
	void Update(double dTime) override;
	
};

