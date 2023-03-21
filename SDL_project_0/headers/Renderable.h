#pragma once
#include "RendererUtils.h"
#include "CoreTypes.h"

class Renderable
{
protected:
    shared_Texture texture;
    Vector2d size;
    SDL_BlendMode blendMode;
    int_fast16_t sortingPriority;

    Vector2i GetSizeFromTexture(shared_Texture tex = nullptr);
    Renderable();

public:
    Vector2d GetSize() { return size; }
    shared_Texture GetTexture() { return texture; }
    SDL_BlendMode GetBlendMode() { return blendMode; }
    int_fast16_t GetSortingPriority() { return sortingPriority; }

    Renderable& SetSortingPriority(ESortingPriority priority, int_fast16_t offset = 0);
    Renderable& SetBlendMode(SDL_BlendMode mode);
    Renderable& SetTexture(shared_Texture tx);


    virtual Renderable& SetSize(Vector2d s, bool = true);
};

