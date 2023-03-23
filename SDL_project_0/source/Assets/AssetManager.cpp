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

bool AssetManager::Init(bool LoadCoreResources)
{
    rendererCore = &Core::Get().GetRendererCore();
    if (!rendererCore) return false;
    if (LoadCoreResources) {
        LoadFont("res/calibrib.ttf", CoreFont::CALIBRI, 16);

        //coreTexturesLoading
        
        LoadTexture("../SDL_project_0/res/pngs/redDot.png", CoreTexture::RedDot, true);
        LoadTexture("../SDL_project_0/res/pngs/greenSquare.png", CoreTexture::GreenSquare, true);
        LoadTexture("../SDL_project_0/res/pngs/orangeTriangle.png", CoreTexture::OrangeTriangle, true);
        LoadTexture("../SDL_project_0/res/pngs/greenArrow.png", CoreTexture::GreenArrow, true);
        LoadTexture("../SDL_project_0/res/pngs/redArrow.png", CoreTexture::RedArrow, true);
        
        //coreTexturesLoading

    }
    return true;
}

AssetManager* AssetManager::Get() {
    return amInst;
}

SharedTexture AssetManager::SetTextureLock(uint16_t texEnum, bool lock)
{
    return SetTextureLock(textures[texEnum].lock(), lock);
}

SharedTexture AssetManager::SetTextureLock(SharedTexture texture, bool lock)
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

SharedTexture AssetManager::LoadTexture(const char* path, bool lock) {
    uint16_t i = (uint16_t)GetFirstFreeID(textures);
    return LoadTexture(path, i, lock);
}

SharedTexture AssetManager::LoadTexture(const char* path, uint16_t texEnum, bool lock) {
    SDL_Texture* sdlTexture = IMG_LoadTexture(rendererCore->GetRenderer(), path);
    if (!sdlTexture) {
        printf("Failed to load image from path: %s! SDL Error: %s\n", path, SDL_GetError());
        return nullptr;
    }
    SharedTexture texture(sdlTexture, TextureDeleter());
    textures[texEnum] = texture;
    if (lock) SetTextureLock(textures[texEnum].lock(), lock);
    return textures[texEnum].lock();
}

SharedTexture AssetManager::GetLoadedTexture(uint16_t texEnum) {
    return textures[texEnum].lock();
}

SharedFont AssetManager::LoadFont(const char* path, uint16_t fontEnum, uint16_t fontSizeID) {
    TTF_Font* sdlFont = TTF_OpenFont(path, fontSizeID);
    if (!sdlFont) {
        printf("Failed to load font from path: %s! SDL Error: %s\n", path, SDL_GetError());
        return nullptr;
    }
    SharedFont font(sdlFont, FontDeleter());
    fonts[fontEnum] = font;
    return fonts[fontEnum];
}

SharedTexture AssetManager::MakeTextureFromText(uint16_t fontEnum = 0, const char* text = "TEXT", const SDL_Color color = {255,255,255,255}) {
    uint16_t i = (uint16_t)GetFirstFreeID(textures);
    SDL_Surface* surface = TTF_RenderText_Solid(fonts[0].get(), text, color);
    SharedTexture texture(SDL_CreateTextureFromSurface(rendererCore->GetRenderer(), surface), TextureDeleter());
    textures[i] = texture;
    return texture;
}