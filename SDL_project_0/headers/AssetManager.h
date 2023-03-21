#pragma once
#include "CoreTypes.h"
enum class ECoreTexture;
enum class ECoreFont;
class AssetManager
{
private:
    std::set<shared_Texture> lockedTextures;
    std::unordered_map<uint16_t, weak_Texture> textures; //65k textures and fonts should be enough
    std::unordered_map<uint16_t, shared_Font> fonts;

public:
    AssetManager();
    //~AssetManager();
    bool Init(bool LoadCoreResources);
    static AssetManager* Get();
    
    shared_Texture SetTextureLock(uint16_t texEnum, bool lock = false);
    shared_Texture SetTextureLock(shared_Texture texture, bool lock = false);
    shared_Texture LoadTexture(const char* path, bool lock = false);
    shared_Texture LoadTexture(const char* path, int texEnum, bool lock = false);
    shared_Texture GetLoadedTexture(uint16_t texEnum);

    shared_Font LoadFont(const char* path, uint16_t fontEnum, uint16_t fontSizeID);
    shared_Font GetLoadedFont(uint16_t fontEnum) { return fonts[fontEnum]; }

    shared_Texture  MakeTextureFromText(uint16_t fontEnum, const char* text, const SDL_Color color);
    void LoadCoreTextures();
};

