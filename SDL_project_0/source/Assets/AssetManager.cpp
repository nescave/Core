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
    LoadTexture("../SDL_project_0/res/pngs/white_dot.png", CoreTexture::WHITE_DOT, true, true);
    LoadTexture("../SDL_project_0/res/pngs/greenSquare.png", CoreTexture::GREEN_SQUARE, true, true);
    LoadTexture("../SDL_project_0/res/pngs/orangeTriangle.png", CoreTexture::ORANGE_TRIANGLE, true, true);
    LoadTexture("../SDL_project_0/res/pngs/greenArrow.png", CoreTexture::GREEN_ARROW, true, true);
    LoadTexture("../SDL_project_0/res/pngs/redArrow.png", CoreTexture::RED_ARROW, true, true);
        
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

SharedTexture AssetManager::SetTextureLock(int texEnum, bool lock)
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

SharedSurface AssetManager::SetSurfaceeLock(int surfEnum, bool lock)
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

SharedTexture AssetManager::LoadTexture(const char* path, int texEnum, bool lock, bool isCoreRes) {
    SDL_Texture* sdlTexture = IMG_LoadTexture(rendererCore->GetRenderer(), path);
    if (!sdlTexture) {
        printf("Failed to load image from path: %s! SDL Error: %s\n", path, SDL_GetError());
        return nullptr;
    }
    SharedTexture texture(sdlTexture, TextureDeleter());
    texEnum = isCoreRes ? texEnum : texEnum + CoreTexture::SIZE; 
    textures[texEnum] = texture;
    if (lock) SetTextureLock(textures[texEnum].lock(), lock);
    return textures[texEnum].lock();
}

SharedTexture AssetManager::LoadTexture(const char* path, bool lock, bool isCoreRes) {
    uint16_t i;
    if(isCoreRes)
        i = (uint16_t)GetFirstFreeID(textures, CoreTexture::SIZE );
    else
        i = (uint16_t)GetFirstFreeID(textures);
    return LoadTexture(path, i, lock, isCoreRes);
}

SharedTexture AssetManager::GetLoadedTexture(int texEnum, bool isCoreRes) {
    texEnum = isCoreRes ? texEnum : texEnum + CoreTexture::SIZE; 
    return textures[texEnum].lock();
}

SharedSurface AssetManager::LoadSurface(const char* path, int texEnum, bool lock)
{
    SDL_Surface* sdlSurface = IMG_Load(path);
    if (!sdlSurface) {
        printf("Failed to load image from path: %s! SDL Error: %s\n", path, SDL_GetError());
        return nullptr;
    }
    SharedSurface surface(sdlSurface, SurfaceDeleter());
    surfaces[(uint16_t)texEnum] = surface;
    if (lock) SetTextureLock(textures[(uint16_t)texEnum].lock(), lock);
    return surface; 
    // return surfaces[texEnum].lock();
}

SharedSurface AssetManager::LoadSurface(const char* path, bool lock)
{
    uint16_t i = (uint16_t)GetFirstFreeID(surfaces);
    return LoadSurface(path, i, lock);
}

SharedSurface AssetManager::GetLoadedSurface(int surfEnum)
{
    return surfaces[(uint16_t)surfEnum].lock();
}

SharedTexture AssetManager::CreateFlatTexture(uint32_t width, uint32_t height, SDL_Color color, int texEnum)
{
    SDL_Surface* surf = SDL_CreateRGBSurface(0,width,height,8,0, 0, 0, 0);
    SDL_SetSurfaceColorMod(surf, color.r, color.g, color.b);
    SDL_Texture* sdlTexture =  SDL_CreateTextureFromSurface(rendererCore->GetRenderer(), surf);
    SDL_FreeSurface(surf);
    SharedTexture texture(sdlTexture, TextureDeleter());
    if(texEnum<0)
        textures[(uint16_t)GetFirstFreeID(textures,CoreTexture::SIZE)] = texture;
    return texture;
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