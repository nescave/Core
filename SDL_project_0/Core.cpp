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
    if (!assetManager->Init()) return false;
    if (!input->Init()) return false;
    
    return true;
}
Core& Core::Get() {
    static Core instance;
    return instance;
}

void Core::Begin() {
    for (auto& tpl : entityManager->GetGameEntities())
    {
        auto& obj = tpl.second;
        if (obj == nullptr) return;

        obj->Begin();
    }
}

void Core::Update() {
    double dTime = clock->GetDeltaTime();
    for (auto& tpl : entityManager->GetGameEntities())
    {
        auto& ent = tpl.second;
        if (ent->ShouldRender()) drawList.push((RenderObject*)&*ent);
        if (ent->HasCollider()) colliderList.push_back((Object*)&*ent);
        ent->Update(dTime);
    }
}

void Core::StartMainLoop(){
    Begin();

    auto act1 = EntitySpawner::SpawnActor({ 300,260 }, { 180,120 }, GetAssetManager().GetLoadedTexture(5), "johny1").lock();
    auto act2 = EntitySpawner::SpawnActor({ 0,0 }, { 120,80 }, GetAssetManager().LoadTexture("res/png.PNG")).lock();
    auto txt1 = EntitySpawner::SpawnText({ 215, 420 }, Vector2i::zero, "", "Best", CoreFont::CALIBRI, { 255,0,0 }).lock();
    auto txt2 = EntitySpawner::SpawnText({ 15, 420 }, Vector2i::zero, "", "Core").lock();

    act1->SetSortingPriority(ESortingPriority::EPIC);
    act2->SetSortingPriority(ESortingPriority::LOW);

    act2->SetParent(act1);
    act1->Rotate(45);
    act2->Rotate(45);

    act2->SetParent(weak_Object(), true);

    act2->AddComponent<Collider>("dokidoki");
    act1->AddComponent<Collider>("wakuwaku");

    if (act2->HasCollider()) printf("%s has collider \n", act2->name.c_str());
    if (act1->HasCollider())printf("%s has collider \n", act1->name.c_str());

    bool quit = false;
    while (!quit) {
        input->ProcessInput();

        auto mouse_pos = input->GetPointerPosition();
        //printf("(%d, %d) \n", mouse_pos.x, mouse_pos.y);
        auto xMouse = std::to_string(mouse_pos.x);
        auto yMouse = std::to_string(mouse_pos.y);

        if (txt2->GetText() != xMouse)txt2->SetText(xMouse).UpdateText();
        if (txt1->GetText() != yMouse)txt1->SetText(yMouse).UpdateText();

        Update();
        //Sleep(5);
        physicsCore->Update(colliderList);
        rendererCore->Update(drawList);
        quit = input->GetQuitEvent();
    }
}
