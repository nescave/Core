#include "stdafx.h"
#include "GameSetup.h"
#include <AssetManager.h>
#include <SDL_mouse.h>

#include "GameEnums.h"
#include "Core.h"
#include "Actor.h"
#include "Camera.h"
#include "CoreActionButtons.h"
#include "CoreTextures.h"
#include "DebugDraw.h"
#include "InputManager.h"
#include "ObjectSpawner.h"
#include "UniversalSpawner.h"
#include "Text.h"

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
    core->Begin();
}

void GameSetup::SetupSpawners()
{
    // auto spawner1 = ObjectSpawner::SpawnObject<UniversalSpawner>();
    auto const camController = ObjectSpawner::SpawnObject<Actor>({0,0});
    auto act = ObjectSpawner::SpawnObject<Actor>({0,0}, AssetManager::Get()->GetLoadedTexture(CoreTextures::WHITE_DOT, true));
    ObjectSpawner::SpawnObject<Actor>({-320,-200}, AssetManager::Get()->GetLoadedTexture(CoreTextures::WHITE_DOT, true));
    ObjectSpawner::SpawnObject<Actor>({320,200}, AssetManager::Get()->GetLoadedTexture(CoreTextures::WHITE_DOT, true));

    act->SetPivot({.75f, .75f});
    auto cam = camController->AddComponent<Camera>();
    cam->SetMain();
    
    InputManager::Get()->RegisterAction(ECoreActionButton::DOWN, [=](){cam->zoom *= 0.99;}, EActionType::CONTINUOUS);
    InputManager::Get()->RegisterAction(ECoreActionButton::UP, [=](){cam->zoom *= 1.01;}, EActionType::CONTINUOUS);
    
    InputManager::Get()->RegisterAction(ECoreActionButton::W, [=]()
    {
        act->Translate(Vector2f::up* core->lastUpdateDuration*100);
    }, EActionType::CONTINUOUS);
    InputManager::Get()->RegisterAction(ECoreActionButton::S, [=]()
    {
        act->Translate(-Vector2f::up* core->lastUpdateDuration*100);
    }, EActionType::CONTINUOUS);
    InputManager::Get()->RegisterAction(ECoreActionButton::A, [=](){act->Translate(-Vector2f::right* core->lastUpdateDuration*100);}, EActionType::CONTINUOUS);
    InputManager::Get()->RegisterAction(ECoreActionButton::D, [=](){act->Translate(Vector2f::right* core->lastUpdateDuration*100);}, EActionType::CONTINUOUS);

    // DebugDraw::Point({0,0}, 40, -1, Color::cyan);
}

void GameSetup::LoadTextures()
{
    
}

