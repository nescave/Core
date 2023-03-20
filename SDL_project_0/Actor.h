#pragma once
#include "RenderObject.h"


class Actor :
    public RenderObject
{
private:

public:

    virtual void OnSpawn() override;
    virtual void Update(double dTime) override;

    Actor& Translate(Vector2i vector);
    Actor& Rotate(double angle);
    Actor& Scale(Vector2f scale);
    Actor& Scale(float scale);
    
    Actor& Accelerate(Vector2i force);
    Vector2f GetCurrentSpeed();
};
