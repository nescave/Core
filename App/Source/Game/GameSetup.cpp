#include "stdafx.h"
#include "GameSetup.h"
#include <AssetManager.h>
#include <SDL_mouse.h>
#include <SDL_render.h>

#include "Asteroid.h"
#include "Core.h"
#include "ObjectSpawner.h"
#include "UniversalSpawner.h"

GameSetup::GameSetup() :
    core(&Core::Get())
{}

void GameSetup::Setup()
{
    SetupCursor();
    SetupSpawners();
}

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
    }
    SDL_SetCursor(cursor);
}

void GameSetup::SetupSpawners()
{
    std::shared_ptr<UniversalSpawner> spawner1 = ObjectSpawner::SpawnObject<UniversalSpawner>().lock();
    spawner1->StartSpawner<Asteroid>(spawner1->GetTransform(), 1,1,1,1);
}

