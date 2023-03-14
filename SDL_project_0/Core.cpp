#include "stdafx.h"
#include "Core.h"
#include "RendererCore.h"
#include "PhysicsCore.h"
#include "AssetManager.h"
#include "EntityManager.h"
#include "Input.h"
#include "Clock.h"
#include "Text.h"
#include "Actor.h"
#include "Collider.h"
#include "EntitySpawner.h"
#include "CoreFunctions.h"

bool Core::Init() {
    rendererCore = std::make_unique<RendererCore>();
    physicsCore = std::make_unique<PhysicsCore>();
    assetManager = std::make_unique<AssetManager>();
    entityManager = std::make_unique<EntityManager>();
    input = std::make_unique<Input>();
    clock = std::make_unique<Clock>();

    if (!rendererCore->Init(SCREEN_WIDTH, SCREEN_HEIGHT)) return false;
    if (!physicsCore->Init()) return false;
    if (!assetManager->Init(true)) return false;
    if (!input->Init()) return false;
    
    return true;
}
Core& Core::Get() {
    static Core instance;
    return instance;
}

void Core::Begin() {}

void Core::Update() {
    double dTime = clock->GetDeltaTime();
    for (auto& ent : entityManager->GetCreatedEntities()) 
    {
        ent.lock()->Begin();
    }
    entityManager->ClearCreatedEntities();
    for (auto& tpl : entityManager->GetGameEntities())
    {
        auto& ent = tpl.second;
        if (ent->ShouldRender()) drawList.push((RenderObject*)&*ent);
        ent->Update(dTime);
    }
}

void Core::StartMainLoop(){
    Begin(); //not sure if it's needed

    bool quit = false;
    while (!quit) {
        input->ProcessInput();

        Update();
        //Sleep(5);
        physicsCore->Update();
        rendererCore->Update(drawList);
        quit = input->GetQuitEvent();
    }
}
