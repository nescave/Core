#include "stdafx.h"
#include <Core.h>
#include <Object.h>
#include <ObjectSpawner.h>
#include <AssetManager.h>
#include <InputManager.h>
#include "PlayerShip.h"
#include "GameSetup.h"
//#undef main

void RotMe() {
    auto& objs = ObjectManager::Get()->GetGameObjects();
    auto obj = static_cast<Actor*>(&*objs[0]);
    obj->Rotate(5);
}
void deleteObj() { //temp
    auto& objs = ObjectManager::Get()->GetGameObjects();
    if(objs.begin()!= objs.end())
        objs.begin()->second->Destroy();
}

int main(int argc, char* args[])
{
    Core& core = Core::Get();
    if (!core.Init()) return 1;

    GameSetup gs;
    gs.Setup();
    // GameSetup::Setup();
    
    ObjectSpawner::SpawnObject<PlayerShip>(Vector2i(120, 80));

    //InputManager::RegisterAction(ECoreActionButton::RMB, deleteObj);
    //InputManager::RegisterAction(ECoreActionButton::LMB, Serf_F);

    core.StartMainLoop();

    return 0;
}
