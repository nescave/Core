#pragma once
#include "Actor.h"

class Serf : public Actor
{
public:
	//Serf();
	void Begin() override;
	//void Update(double dTime) override;
	void OnSpawn() override;
};

