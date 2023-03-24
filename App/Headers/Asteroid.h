#pragma once
#include <Actor.h>

// class Collider;

class Asteroid : public Actor
{
public:
    void OnSpawn() override;
private:
    Collider* collider;
};
