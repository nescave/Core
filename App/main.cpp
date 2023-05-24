#include "stdafx.h"
#include <Core.h>
#include "GameSetup.h"


int main(int argc, char* args[])
{
    Core& core = Core::Get();
    if (!core.Init()) return 1;

    GameSetup gs;
    gs.Setup();
    // GameSetup::Setup();
    

    core.StartMainLoop();

    return 0;
}
