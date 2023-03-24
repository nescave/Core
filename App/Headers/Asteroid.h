#pragma once
#include <Actor.h>

// class Collider;

class Asteroid : public Actor
{
private:
    Collider* collider;
public:
    Asteroid();
    void OnSpawn() override;
    void Update(double dTime) override;
};

