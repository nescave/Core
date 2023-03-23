#include "stdafx.h"
#include "GameSetup.h"
#include <AssetManager.h>
#include <SDL_mouse.h>
#include <SDL_render.h>

#include "Core.h"


void GameSetup::SetupCursor()
{
    SDL_Surface* surf =  IMG_Load("res/pngs/crosshair.png");
    if(!surf)
    {
        printf("Failed to load image; SDL Error: %s\n", SDL_GetError());
    }
    // Core& core = Core::Get();
    // SharedTexture tex = core.GetAssetManager().LoadTexture("res/pngs/crosshair.png", true);
    // SDL_LockTextureToSurface(&*tex, NULL, &surf);
    // //
    SDL_Cursor* cursor = SDL_CreateColorCursor(surf,surf->w/2,surf->h/2);
    if(!cursor)
    {
        printf("Failed! %s\n", SDL_GetError());
    }// SDL_Cursor* cursor2 = SDL_CreateSystemCursor(SDL_SystemCursor::SDL_SYSTEM_CURSOR_CROSSHAIR);
    SDL_SetCursor(cursor);
    //
    // SDL_ShowCursor(0);
}

void GameSetup::Setup()
{
    SetupCursor();
}
