#include "stdafx.h"
#include "Core.h"
#include "RendererCore.h"
#include "AssetManager.h"
#include "CoreTextures.h"
#include "CoreFonts.h"
#include "CoreFunctions.h"

static AssetManager* amInst;
RendererCore* rendererCore;

void AssetManager::LoadCoreTextures()
{
    LoadTexture("../SDL_project_0/res/pngs/redDot.png", CoreTexture::RedDot, true);
    LoadTexture("../SDL_project_0/res/pngs/greenSquare.png", CoreTexture::GreenSquare, true);
    LoadTexture("../SDL_project_0/res/pngs/orangeTriangle.png", CoreTexture::OrangeTriangle, true);
    LoadTexture("../SDL_project_0/res/pngs/greenArrow.png", CoreTexture::GreenArrow, true);
    LoadTexture("../SDL_project_0/res/pngs/redArrow.png", CoreTexture::RedArrow, true);
        
}

AssetManager::AssetManager() {
    if(amInst==nullptr) amInst = this;
}

bool AssetManager::Init(bool LoadCoreResources)
{
    rendererCore = &Core::Get().GetRendererCore();
    if (!rendererCore) return false;
    if (LoadCoreResources) {
        LoadFont("res/calibrib.ttf", CoreFont::CALIBRI, 16);
        LoadCoreTextures();
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
    if(lock)
    {
        if (!lockedTextures.insert(texture).second)
        {
            printf("texture already locked\n");
        }
    }else{
        if(!lockedTextures.erase(texture)){
            printf("texture not on a locked list\n");
        }
    }
    return texture;
}

SharedSurface AssetManager::SetSurfaceeLock(uint16_t surfEnum, bool lock)
{
    return SetSurfaceeLock(surfaces[surfEnum].lock(), lock);
}

SharedSurface AssetManager::SetSurfaceeLock(SharedSurface surface, bool lock)
{
    if(lock)
    {
        if (!lockedSurfaces.insert(surface).second)
        {
            printf("texture already locked\n");
        }
    }else{
        if(!lockedSurfaces.erase(surface)){
            printf("texture not on a locked list\n");
        }
    }
    return surface;
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

SharedTexture AssetManager::LoadTexture(const char* path, bool lock) {
    uint16_t i = (uint16_t)GetFirstFreeID(textures);
    return LoadTexture(path, i, lock);
}

SharedTexture AssetManager::GetLoadedTexture(uint16_t texEnum) {
    return textures[texEnum].lock();
}

SharedSurface AssetManager::LoadSurface(const char* path, uint16_t texEnum, bool lock)
{
    SDL_Surface* sdlSurface = IMG_Load(path);
    if (!sdlSurface) {
        printf("Failed to load image from path: %s! SDL Error: %s\n", path, SDL_GetError());
        return nullptr;
    }
    SharedSurface surface(sdlSurface, SurfaceDeleter());
    surfaces[texEnum] = surface;
    if (lock) SetTextureLock(textures[texEnum].lock(), lock);
    return surface; 
    // return surfaces[texEnum].lock();
}

SharedSurface AssetManager::LoadSurface(const char* path, bool lock)
{
    uint16_t i = (uint16_t)GetFirstFreeID(surfaces);
    return LoadSurface(path, i, lock);
}

SharedSurface AssetManager::GetLoadedSurface(uint16_t surfEnum)
{
    return surfaces[surfEnum].lock();
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