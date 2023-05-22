#pragma once
#include "SceneObject.h"
#include "Renderable.h"

class RenderableObject : public SceneObject, public Renderable
{
    friend class ObjectSpawner; 
protected:
    RenderableObject();
public:

    bool ShouldRender() override { return texture != nullptr; } 
    
    SDL_Rect GetDstRect() override;
    SDL_Rect GetSrcRect() override;
    
    Renderable& SetSize(Vector2d s, bool resetScale = false) override;
    Vector2d GetAnchorOffset(Anchor anch) override;

    void OnSpawn() override;
    void Update(double dTime) override;
};
