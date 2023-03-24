#pragma once
#include "SceneObject.h"
#include "Renderable.h"

class RenderableObject : public SceneObject, public Renderable
{
protected:
    RenderableObject();
public:

    bool ShouldRender() override { return texture != nullptr; } 

    Renderable& SetSize(Vector2d s, bool resetScale = false) override;
    Vector2d GetAnchorOffset(Anchor anch) override;

    void OnSpawn() override;
};
