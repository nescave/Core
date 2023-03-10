#include "stdafx.h"
#include <stdio.h>
#include <Core.h>
#include <Entity.h>
#include <EntitySpawner.h>
#include <AssetManager.h>
#include <Input.h>
#include "CoreActionButtons.h"
#include "CoreFonts.h"
#include "Serf.h"

//#undef main

void deleteObj() { //temp
    auto& objs = EntityManager::Get()->GetGameEntities();
    if(objs.begin()!= objs.end())
        objs.begin()->second->Destroy();
}

int main(int argc, char* args[])
{
    Core& core = Core::Get();
    if (!core.Init()) return 1;

    EntitySpawner::SpawnActor<Serf>(Vector2i(120, 80));

    core.StartMainLoop();

    return 0;
}
