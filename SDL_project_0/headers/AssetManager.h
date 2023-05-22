#pragma once
#include "CoreTypes.h"
#include "Color.h"

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
    
    SharedTexture SetTextureLock(int texEnum, bool lock = false);
    SharedTexture SetTextureLock(SharedTexture texture, bool lock = false);

    SharedSurface SetSurfaceeLock(int surfEnum, bool lock = false);
    SharedSurface SetSurfaceeLock(SharedSurface surface, bool lock = false);
    
    SharedTexture LoadTexture(const char* path, bool lock = false, bool isCoreRes = false);
    SharedTexture LoadTexture(const char* path, int texEnum, bool lock = false, bool isCoreRes = false);
    SharedTexture GetLoadedTexture(int texEnum, bool isCoreRes = false);

    SharedSurface LoadSurface(const char* path, int texEnum, bool lock = false);
    SharedSurface LoadSurface(const char* path, bool lock = false);
    SharedSurface GetLoadedSurface(int surfEnum);

    SharedTexture CreateFlatTexture(uint32_t width, uint32_t height, Color color, int texEnum =-1, bool coreRes = false);

    SharedFont LoadFont(const char* path, uint16_t fontEnum, uint16_t fontSizeID);
    SharedFont GetLoadedFont(uint16_t fontEnum) { return fonts[fontEnum]; }

    SharedTexture  MakeTextureFromText(uint16_t fontEnum, const char* text, const SDL_Color color);
};

