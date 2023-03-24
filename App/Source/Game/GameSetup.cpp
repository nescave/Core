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
    LoadTextures();
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
    // spawner1->SetSpawningState(false);
    spawner1->StartSpawner<Asteroid>(Transform({50,250}, 90, {.3f,.3f}), .2f,2,.5f,1.3f);
}

void GameSetup::LoadTextures()
{
    core->GetAssetManager().LoadTexture("res/pngs/asteroid.png", GameTextures::ASTEROID, true);
    core->GetAssetManager().LoadTexture("res/pngs/main_ship.png", GameTextures::MAIN_SHIP, true);
    core->GetAssetManager().LoadTexture("res/pngs/enemy_ship_small_0.png", GameTextures::ENEMY_SHIP_SMALL, true);

}

