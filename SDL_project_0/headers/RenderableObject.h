#pragma once
#include "SceneObject.h"
#include "Renderable.h"
#include "CoreTypes.h"

class RenderObject : public Object, public Renderable
{
protected:
    RenderObject();
public:

    bool ShouldRender() override { return texture != nullptr; } 

    virtual Renderable& SetSize(Vector2d s, bool resetScale = true) override;
    Vector2d GetAnchorOffset(Anchor anch) override;
};
