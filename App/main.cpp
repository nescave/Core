#include "stdafx.h"
#include <stdio.h>
#include <Core.h>
#include <Entity.h>
#include <EntityManager.h>
#include <AssetManager.h>
#include <Input.h>
#include "CoreActionButtons.h"
#include "CoreFonts.h"

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
    AssetManager::Get()->SetTextureLock(core.GetAssetManager().LoadTexture("res/knight.bmp", 5), true);
    SDL_Color color = { 255,255,255,255 };

    Input::RegisterAction(ECoreActionButton::LMB, deleteObj);//temp

    core.StartMainLoop();

    return 0;
}
