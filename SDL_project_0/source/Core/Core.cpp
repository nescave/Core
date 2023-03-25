#include "stdafx.h"
#include "Core.h"
#include "RendererCore.h"
#include "PhysicsCore.h"
#include "AssetManager.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "Clock.h"
#include "Text.h"
#include "Actor.h"
#include "Collider.h"
#include "ObjectSpawner.h"
#include "TaskManager.h"

bool Core::Init() {
    rendererCore = std::make_unique<RendererCore>();
    physicsCore = std::make_unique<PhysicsCore>();
    assetManager = std::make_unique<AssetManager>();
    objectManager = std::make_unique<ObjectManager>();
    input = std::make_unique<InputManager>();
    clock = std::make_unique<Clock>();
    taskManager = std::make_unique<TaskManager>();

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
    const double dTime = clock->GetDeltaTime();

    taskManager->UpdateTasks(dTime);
    
    for (auto& obj : objectManager->GetCreatedObjects()) 
    {
        obj.lock()->Begin();
    }
    objectManager->ClearCreatedObjects();
    for (auto& tpl : objectManager->GetGameObjects())
    {
        auto& obj = tpl.second;
        if (obj->ShouldRender()) {
            auto rObj = dynamic_cast<RenderableObject*>(&*obj);
            if (rObj) {
                drawList.push(DrawCall(rObj, rObj->GetAbsoluteTransform()));
            }
            for (auto comp : rObj->GetRenderableComponents()) {
                drawList.push(DrawCall(comp, comp->GetWorldTransform()));
            }
        }
        obj->Update(dTime);
    }
}

void Core::StartMainLoop(){
    Begin(); //not sure if it's needed

    bool quit = false;
    while (!quit) {
        input->ProcessInput();
        Update();
        Sleep(2);
        physicsCore->Update();
        rendererCore->Update(drawList);

        objectManager->ApplyDelete();
        quit = input->GetQuitEvent();
    }
}
