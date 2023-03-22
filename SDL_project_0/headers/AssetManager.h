#pragma once
#include "CoreTypes.h"
enum class ECoreTexture;
enum class ECoreFont;
class AssetManager
{
private:
    std::set<SharedTexture> lockedTextures;
    std::unordered_map<uint16_t, WeakTexture> textures; //65k textures and fonts should be enough
    std::unordered_map<uint16_t, SharedFont> fonts;

public:
    AssetManager();
    //~AssetManager();
    bool Init(bool LoadCoreResources);
    static AssetManager* Get();
    
    SharedTexture SetTextureLock(uint16_t texEnum, bool lock = false);
    SharedTexture SetTextureLock(SharedTexture texture, bool lock = false);
    SharedTexture LoadTexture(const char* path, bool lock = false);
    SharedTexture LoadTexture(const char* path, int texEnum, bool lock = false);
    SharedTexture GetLoadedTexture(uint16_t texEnum);

    SharedFont LoadFont(const char* path, uint16_t fontEnum, uint16_t fontSizeID);
    SharedFont GetLoadedFont(uint16_t fontEnum) { return fonts[fontEnum]; }

    SharedTexture  MakeTextureFromText(uint16_t fontEnum, const char* text, const SDL_Color color);
    void LoadCoreTextures();
};

