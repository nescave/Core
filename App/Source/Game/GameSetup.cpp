#include "stdafx.h"
#include "GameSetup.h"
#include <AssetManager.h>
#include <SDL_mouse.h>
#include "GameEnums.h"
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
    SharedSurface surf = AssetManager::Get()->LoadSurface("res/pngs/crosshair.png", GameTextures::CROSSHAIR, true); //TODO try deleting last argument... i dare you
    SDL_Cursor* cursor = SDL_CreateColorCursor(&*surf,(&*surf)->w/2,(&*surf)->h/2);
    if(!cursor)
    {
        printf("Failed! %s\n", SDL_GetError());
    }
    SDL_SetCursor(cursor);
}

void GameSetup::SetupSpawners()
{
    std::shared_ptr<UniversalSpawner> spawner1 = ObjectSpawner::SpawnObject<UniversalSpawner>();
    spawner1->StartSpawner<Asteroid>(spawner1->inititalTransform, 1,1,1,1);
}

