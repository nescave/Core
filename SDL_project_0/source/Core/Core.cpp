#include "stdafx.h"
#include "Core.h"
#include <Windows.h>
#include "Actor.h"
#include "AssetManager.h"
#include "Clock.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "ObjectSpawner.h"
#include "PhysicsCore.h"
#include "RendererCore.h"
#include "TaskManager.h"
#include "Text.h"


bool Core::Init() {
    rendererCore = std::make_unique<RendererCore>();
    physicsCore = std::make_unique<PhysicsCore>();
    assetManager = std::make_unique<AssetManager>();
    objectManager = std::make_unique<ObjectManager>();
    input = std::make_unique<InputManager>();
    clock = std::make_unique<Clock>();
    taskManager = std::make_unique<TaskManager>();

    lastUpdateDuration = 0;
    
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
    lastUpdateDuration = dTime;
    taskManager->UpdateTasks(dTime);
    
    for (auto& obj : objectManager->GetCreatedObjects()) 
    {
        obj.lock()->Begin();
    }
    objectManager->ClearCreatedObjects();
    for (auto& tpl : objectManager->GetGameObjects())
    {
        auto& obj = tpl.second;
        const auto rObj = dynamic_cast<RenderableObject*>(&*obj);
        if(!rObj) continue;
        if(rObj->hidden) continue;
        drawList.push(DrawCall(rObj, rObj->GetAbsoluteTransform()));
        auto rComponents = rObj->GetRenderableComponents(); 
        if (!rComponents.empty()) {
            for (auto comp : rComponents) {
                drawList.push(DrawCall(comp, comp->GetAbsoluteTransform()));
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
