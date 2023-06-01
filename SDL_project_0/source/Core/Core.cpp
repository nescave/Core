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

void Core::AddToDrawList(std::vector<DrawCall>& drawList, const std::shared_ptr<Object>& obj)
{
    const auto rObj = dynamic_cast<RenderableObject*>(&*obj);
    if(!rObj) return;
    if(rObj->hidden) return;
    if(rObj->GetTexture() != nullptr) drawList.emplace_back(rObj, rObj->GetAbsoluteTransform());
    if (const auto rComponents = rObj->GetRenderableComponents(); !rComponents.empty()) {
        for (auto comp : rComponents) {
            drawList.emplace_back(comp, comp->GetAbsoluteTransform());
        }
    }
}

void Core::Update() {

    std::vector<DrawCall> drawList;
    
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
        AddToDrawList(drawList, obj);
        obj->Update(dTime);
    }

    Sleep(2);
    physicsCore->Update();
    
    rendererCore->Update(drawList);

}

void Core::StartMainLoop(){
    Begin(); //not sure if it's needed

    bool quit = false;
    while (!quit) {
        input->ProcessInput();
        Update();

        objectManager->ApplyDelete();
        quit = input->GetQuitEvent();
    }
}
