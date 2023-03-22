#pragma once
#include "Actor.h"

class InputManager;
class Text;

class Serf : public Actor
{
private:
	InputManager* input;
	Text* textComp;
public:
	Serf();
	void Serf_F();
	void OnSpawn() override;
	void Begin() override;
	void Update(double dTime) override;
	
};

