#pragma once

class Core;

class GameSetup
{
public:
    GameSetup();
    void Setup();
    
private:
    Core* core;
    
    void SetupCursor();
    void SetupSpawners();
    void LoadTextures();
};
