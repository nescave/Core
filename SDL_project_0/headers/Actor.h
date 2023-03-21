#pragma once
#include "RenderableObject.h"


class Actor :
    public RenderableObject
{
private:

public:

    virtual void OnSpawn() override;
    virtual void Update(double dTime) override;

    Actor& Translate(Vector2d vector);
    Actor& Rotate(double angle);
    Actor& Scale(Vector2f scale);
    Actor& Scale(float scale);
    
    Actor& Accelerate(Vector2i force);
    Vector2f GetCurrentSpeed();
};
