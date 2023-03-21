#include "stdafx.h"
#include "Core.h"
#include "RendererCore.h"
#include "PhysicsCore.h"
#include "AssetManager.h"
#include "EntityManager.h"
#include "InputManager.h"
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
    input = std::make_unique<InputManager>();
    clock = std::make_unique<Clock>();

    if (!rendererCore->Init(screen_width, screen_height)) return false;
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
    const double dTime = clock->GetDeltaTime();
    for (auto& ent : entityManager->GetCreatedEntities()) 
    {
        ent.lock()->Begin();
    }
    entityManager->ClearCreatedEntities();
    for (auto& tpl : entityManager->GetGameEntities())
    {
        auto& ent = tpl.second;
        if (ent->ShouldRender()) {
            auto rObj = dynamic_cast<RenderObject*>(&*ent);
            if (rObj) {
                drawList.push(DrawCall(rObj, rObj->GetWorldTransform()));
            }
            for (auto comp : rObj->GetRenderableComponents()) {
                drawList.push(DrawCall(comp, comp->GetWorldTransform()));
            }
        }
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
