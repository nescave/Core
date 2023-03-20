#pragma once
#include "Object.h"
#include "Renderable.h"
#include "CoreTypes.h"

class RenderObject : public Object, public Renderable
{
protected:

public:
    RenderObject(std::string n, Transform& t, const Vector2i s, shared_Texture tx);
    RenderObject(Transform& t, const Vector2i s, shared_Texture tx);
    RenderObject(Vector2i s, shared_Texture tx);
    RenderObject(shared_Texture tx);
    RenderObject();

    //virtual ~RenderObject();

    bool ShouldRender() override { return texture != nullptr; } //for now keep it simple

    virtual Renderable& SetScreenSize(Vector2i s, bool resetScale = true) override;
    Vector2i GetAnchorOffset(Anchor anch) override;
};
