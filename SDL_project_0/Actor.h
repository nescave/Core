#pragma once
#include "RenderObject.h"

class Actor :
    public RenderObject
{
private:

    //void UpdateRect();

public:
    Actor(int iD, std::string n, Transform t, Vector2i s, shared_Texture tex);
    //Actor(Vector2i pos, Vector2i s, shared_Texture tex);
    //Actor(Vector2i pos, Vector2i s);
    //Actor();

    virtual void Update(double dTime) override;

    //Vector2i GetLocalPosition();
    //double GetRotation();
    //Vector2i GetSize();
    //Vector2f GetLocalPivot();
    //SDL_Rect* GetRect();

    Actor& Translate(Vector2i vector);
    Actor& Rotate(double angle);
    Actor& Scale(Vector2f scale);
    Actor& Scale(float scale);

    Actor& Accelerate(Vector2i force);
    Vector2f GetCurrentSpeed();
};
