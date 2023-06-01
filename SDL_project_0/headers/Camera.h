#pragma once
#include "Rect.h"
#include "RendererUtils.h"
#include "SceneComponent.h"

class Camera : public SceneComponent
{
public:
    // Vector2i renderRect;
    double zoom;
    // bool forceCorrectAspectRatio;

    bool clearAfterRender;
    bool mainCamera;
    SDL_Texture* renderTarget;

    Camera();
    ~Camera();
    Rect<double> GetRenderRect();
    void SetMain();
    // bool ShouldRender();

};
