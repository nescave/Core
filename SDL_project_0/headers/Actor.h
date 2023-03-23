#pragma once
#include "RenderableObject.h"


class Actor :
    public RenderableObject
{
    friend class ObjectSpawner;
protected:
    float maxSpeed;
    Vector2f speed;

public:
    Actor();

    virtual void OnSpawn() override;
    virtual void Update(double dTime) override;

    Actor& Translate(Vector2f& vector);
    Actor& TranslateAbsolute(Vector2f& vector);

    Actor& Rotate(double angle);
    Actor& Scale(Vector2f scale);
    Actor& Scale(float scale);
    
    Actor& Accelerate(Vector2f force);
    Actor& AccelerateAbsolute(Vector2f force);
    Actor& Stop();

    Vector2f GetCurrentSpeed() const {return speed;}
};
