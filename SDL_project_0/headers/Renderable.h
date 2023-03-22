#pragma once
#include "RendererUtils.h"
#include "CoreTypes.h"

class Renderable
{
protected:
    SharedTexture texture;
    Vector2d size;
    SDL_BlendMode blendMode;
    int_fast16_t sortingPriority;

    Vector2i GetSizeFromTexture(SharedTexture tex = nullptr);
    Renderable();

public:
    Vector2d GetSize() { return size; }
    SharedTexture GetTexture() { return texture; }
    SDL_BlendMode GetBlendMode() { return blendMode; }
    int_fast16_t GetSortingPriority() { return sortingPriority; }

    Renderable& SetSortingPriority(ESortingPriority priority, int_fast16_t offset = 0);
    Renderable& SetBlendMode(SDL_BlendMode mode);
    Renderable& SetTexture(SharedTexture tx);


    virtual Renderable& SetSize(Vector2d s, bool = true);
};

