#pragma once
#include "Object.h"
#include "RendererUtils.h"
#include "CoreTypes.h"

class RenderObject : public Object
{
protected:
    shared_Texture texture;
    Vector2i screenSize;
    SDL_Rect rect;
    SDL_BlendMode blendMode;
    int_fast16_t sortingPriority;
    virtual void UpdateRect();
public:
    RenderObject(uint32_t iD, std::string n, Transform t, Vector2i s, shared_Texture tx);
    //virtual ~RenderObject();

    bool ShouldRender() override { return texture != nullptr; } //for now keep it simple
    Vector2i GetSDLPivot() { return transform.pivot * screenSize; }

    SDL_Rect* GetRect() { UpdateRect(); return &rect; }
    shared_Texture GetTexture(){ return texture;}
    SDL_BlendMode GetBlendMode() { return blendMode; }
    int_fast16_t GetSortingPriority() { return sortingPriority; }

    RenderObject& SetBlendMode(SDL_BlendMode mode);
    RenderObject& SetSortingPriority(ESortingPriority priority, int_fast16_t offset = 0);

    virtual RenderObject& SetTexture(shared_Texture tx) { texture = tx; return *this; }
    
    virtual RenderObject& SetScreenSize(Vector2i s, bool resetScale = true) { 
        screenSize = s; 
        if (resetScale) transform.scale = Vector2f::one; 
        return *this; 
    }

};
