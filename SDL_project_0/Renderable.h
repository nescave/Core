#pragma once
#include "RendererUtils.h"
#include "CoreTypes.h"

class Renderable
{
protected:
    shared_Texture texture;
    Vector2i screenSize;
    SDL_BlendMode blendMode;
    int_fast16_t sortingPriority;

    const Vector2i GetSizeFromTexture(shared_Texture tex = nullptr);

public:
    Renderable(shared_Texture tx, const Vector2i s);
    Renderable(shared_Texture tx);
    Renderable();
    const Vector2i& GetScreenSize() { return screenSize; }
    shared_Texture GetTexture() { return texture; }
    SDL_BlendMode GetBlendMode() { return blendMode; }
    int_fast16_t GetSortingPriority() { return sortingPriority; }

    Renderable& SetSortingPriority(ESortingPriority priority, int_fast16_t offset = 0);
    Renderable& SetBlendMode(SDL_BlendMode mode);
    Renderable& SetTexture(shared_Texture tx);


    virtual Renderable& SetScreenSize(Vector2i s, bool = true);
};

