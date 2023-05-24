#pragma once
#include "RendererUtils.h"
#include "CoreTypes.h"
#include "Animation.h"

class Renderable
{
protected:
    SharedTexture texture;
    Vector2d size;
    SDL_BlendMode blendMode;        //for it to work i need single texture user
    int16_t sortingPriority;
    
    Vector2i GetSizeFromTexture(SharedTexture tex = nullptr);
    Renderable();

public:
    std::unique_ptr<Animation> animation;
    virtual Vector2d GetSize();
    SharedTexture GetTexture() { return texture; }
    SDL_BlendMode GetBlendMode() const { return blendMode; }
    int16_t GetSortingPriority() const { return sortingPriority; }

    bool hidden;
    
    virtual SDL_Rect GetDstRect();
    virtual SDL_Rect GetSrcRect();

    Renderable& SetSortingPriority(ESortingPriority priority, int16_t offset = 0);
    Renderable& SetBlendMode(SDL_BlendMode mode);
    Renderable& SetTexture(SharedTexture tx);
    Renderable& SetupAnimation(
        uint16_t rows,
        uint16_t columns,
        bool looping = false,
        uint16_t startFr = 0,
        uint16_t endFr = 0,
        uint16_t fps = 24,
        bool reverse = false
    );

    virtual Renderable& SetSize(Vector2d s, bool = true);
};
