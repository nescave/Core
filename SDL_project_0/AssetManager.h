#pragma once
#include "CoreTypes.h"
enum class ECoreTexture;
enum class ECoreFont;
class AssetManager
{
private:
    std::set<shared_Texture> lockedTextures;
    std::unordered_map<int, weak_Texture> textures;
    std::unordered_map<int, shared_Font> fonts;

public:

    AssetManager();
    //~AssetManager();
    bool Init();
    static AssetManager* Get();
    
    //shared_Texture LoadTextureBMP(const char* path);
    //shared_Texture LoadTextureBMP(const char* path, int texEnum);
    shared_Texture SetTextureLock(int texEnum, bool lock = false);
    shared_Texture SetTextureLock(shared_Texture texture, bool lock = false);
    shared_Texture LoadTexture(const char* path, bool lock = false);
    shared_Texture LoadTexture(const char* path, int texEnum, bool lock = false);
    shared_Texture GetLoadedTexture(int texEnum);

    shared_Font LoadFont(const char* path, int fontEnum, int fontSizeID);
    shared_Font GetLoadedFont(int fontEnum) { return fonts[fontEnum]; }

    shared_Texture  MakeTextureFromText(int fontEnum, const char* text, const SDL_Color color);

};

