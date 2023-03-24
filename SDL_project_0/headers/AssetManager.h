#pragma once
#include "CoreTypes.h"
enum class ECoreFont;
class AssetManager
{
private:
    std::set<SharedTexture> lockedTextures;
    std::set<SharedSurface> lockedSurfaces;
    std::unordered_map<uint16_t, WeakTexture> textures; //65k textures and fonts should be enough
    std::unordered_map<uint16_t, WeakSurface> surfaces; 
    std::unordered_map<uint16_t, SharedFont> fonts;

    void LoadCoreTextures();
public:
    AssetManager();
    bool Init(bool LoadCoreResources);
    static AssetManager* Get();
    
    SharedTexture SetTextureLock(uint16_t texEnum, bool lock = false);
    SharedTexture SetTextureLock(SharedTexture texture, bool lock = false);

    SharedSurface SetSurfaceeLock(uint16_t surfEnum, bool lock = false);
    SharedSurface SetSurfaceeLock(SharedSurface surface, bool lock = false);
    
    SharedTexture LoadTexture(const char* path, bool lock = false);
    SharedTexture LoadTexture(const char* path, uint16_t texEnum, bool lock = false);
    SharedTexture GetLoadedTexture(uint16_t texEnum);

    SharedSurface LoadSurface(const char* path, uint16_t texEnum, bool lock = false);
    SharedSurface LoadSurface(const char* path, bool lock = false);
    SharedSurface GetLoadedSurface(uint16_t surfEnum);


    SharedFont LoadFont(const char* path, uint16_t fontEnum, uint16_t fontSizeID);
    SharedFont GetLoadedFont(uint16_t fontEnum) { return fonts[fontEnum]; }

    SharedTexture  MakeTextureFromText(uint16_t fontEnum, const char* text, const SDL_Color color);
};

