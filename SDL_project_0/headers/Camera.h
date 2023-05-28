#pragma once
#include "Rect.h"
#include "SceneComponent.h"

class Camera : public SceneComponent
{
public:
    // Vector2i renderRect;
    double zoom;
    // bool forceCorrectAspectRatio;

    bool renderToScreen;
    bool clearAfterRender;
    SDL_Texture* renderTarget;

    Camera();
    ~Camera();
    Rect<double> GetRenderRect();

    // bool ShouldRender();

};
