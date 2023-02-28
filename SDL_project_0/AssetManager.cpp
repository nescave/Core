#include "stdafx.h"
#include "Core.h"
#include "RendererCore.h"
#include "AssetManager.h"
#include "CoreTextures.h"
#include "CoreFonts.h"
#include "CoreFunctions.h"

static AssetManager* amInst;
RendererCore* rendererCore;
AssetManager::AssetManager() {
    if(amInst==nullptr) amInst = this;
}

bool AssetManager::Init()
{
    rendererCore = &Core::Get().GetRendererCore();
    if (!rendererCore) return false;
    LoadFont("res/calibri.ttf", CoreFont::CALIBRI, 54);
    return true;
}

AssetManager* AssetManager::Get() {
    return amInst;
}

//shared_Texture AssetManager::LoadTextureBMP(const char* path) {
//    int i = GetFirstFreeID(textures);
//
//    return LoadTextureBMP(path, i);
//}
//shared_Texture AssetManager::LoadTextureBMP(const char* path, int texEnum) {
//    SDL_Surface* surface = SDL_LoadBMP(path);
//    if (!surface) {
//        printf("Failed to load image from path: %s! SDL Error: %s\n", path, SDL_GetError());
//        return nullptr;
//    }
//    surface = SDL_ConvertSurface(surface, rendererCore->GetScreenSurface()->format, 0);
//    SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(rendererCore->GetRenderer(), surface);
//    shared_Texture texture = std::make_shared<SDL_Texture>(*sdlTexture);
//    textures.emplace(texEnum, texture);
//    return textures[texEnum];
//}

shared_Texture AssetManager::SetTextureLock(int texEnum, bool lock)
{
    return SetTextureLock(textures[texEnum].lock(), lock);
}

shared_Texture AssetManager::SetTextureLock(shared_Texture texture, bool lock)
{
    auto it = lockedTextures.find(texture);
    if (it == lockedTextures.end()) {
        if (lock) {
            lockedTextures.insert(texture);
        }
        else {
            printf("texture already not on a locked list\n");
        }
    }
    else {
        if (lock) {
            printf("texture already locked\n");
        }
        else {
            lockedTextures.erase(it);
        }
    }
    return texture;
}

shared_Texture AssetManager::LoadTexture(const char* path, bool lock) {
    int i = GetFirstFreeID(textures);
    return LoadTexture(path, i, lock);
}

shared_Texture AssetManager::LoadTexture(const char* path, int texEnum, bool lock) {
    SDL_Texture* sdlTexture = IMG_LoadTexture(rendererCore->GetRenderer(), path);
    if (!sdlTexture) {
        printf("Failed to load image from path: %s! SDL Error: %s\n", path, SDL_GetError());
        return nullptr;
    }
    shared_Texture texture(sdlTexture, TextureDeleter());
    textures.emplace(texEnum, texture);
    if (lock) SetTextureLock(textures[texEnum].lock(), lock);
    return textures[texEnum].lock();
}

shared_Texture AssetManager::GetLoadedTexture(int texEnum) {
    return textures[texEnum].lock();
}

shared_Font AssetManager::LoadFont(const char* path, int fontEnum, int fontSizeID) {
    TTF_Font* sdlFont = TTF_OpenFont(path, fontSizeID);
    if (!sdlFont) {
        printf("Failed to load font from path: %s! SDL Error: %s\n", path, SDL_GetError());
        return nullptr;
    }
    shared_Font font(sdlFont, FontDeleter());
    fonts.emplace(fontEnum, font);
    return fonts[fontEnum];
}

shared_Texture AssetManager::MakeTextureFromText(int fontEnum = 0, const char* text = "TEXT", const SDL_Color color = {255,255,255,255}) {    
    int i = GetFirstFreeID(textures);
    SDL_Surface* surface = TTF_RenderText_Solid(fonts[0].get(), text, color);
    shared_Texture texture(SDL_CreateTextureFromSurface(rendererCore->GetRenderer(), surface), TextureDeleter());
    textures[i] = texture;
    return texture;
}