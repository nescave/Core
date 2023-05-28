#pragma once
#include "Vector2.h"

template<typename T>
struct Rect
{
    Vector2<T> position;
    Vector2<T> extents;

    Rect() : Rect(Vector2<T>(), Vector2<T>())
    {}
    Rect(Vector2<T> pos, Vector2<T> ext) :
        position(pos),
        extents(ext)
    {}
    
    //i dont want this to happen by accident cause loss of date can be severe
    explicit operator SDL_Rect()
    {
        SDL_Rect rect;
        rect.x = (int)this->position.x;
        rect.y = (int)this->position.y;
        rect.w = (int)this->extents.x;
        rect.h = (int)this->extents.y;
        return rect;
    }

};
