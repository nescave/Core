#pragma once
#include "Object.h"
#include "Renderable.h"
#include "CoreTypes.h"

class RenderObject : public Object, public Renderable
{
protected:
    RenderObject();
public:

    bool ShouldRender() override { return texture != nullptr; } 

    virtual Renderable& SetScreenSize(Vector2i s, bool resetScale = true) override;
    Vector2i GetAnchorOffset(Anchor anch) override;
};
