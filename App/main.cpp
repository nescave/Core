#include "stdafx.h"
#include <stdio.h>
#include <Core.h>
#include <Entity.h>
#include <EntitySpawner.h>
#include <AssetManager.h>
#include <InputManager.h>
#include "CoreActionButtons.h"
#include "CoreFonts.h"
#include "Serf.h"
#include "Text.h"
//#undef main

void RotMe() {
    auto& objs = EntityManager::Get()->GetGameEntities();
    auto obj = static_cast<Actor*>(&*objs[0]);
    obj->Rotate(5);
}
void deleteObj() { //temp
    auto& objs = EntityManager::Get()->GetGameEntities();
    if(objs.begin()!= objs.end())
        objs.begin()->second->Destroy();
}

int main(int argc, char* args[])
{
    Core& core = Core::Get();
    if (!core.Init()) return 1;

    weak_Object a = EntitySpawner::SpawnObject<Serf>(Vector2i(120, 80));

    //InputManager::RegisterAction(ECoreActionButton::RMB, deleteObj);
    //InputManager::RegisterAction(ECoreActionButton::LMB, Serf_F);

    core.StartMainLoop();

    return 0;
}
