#pragma once
#include <Windows.h>
#include "RendererUtils.h"
#include "CoreTypes.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
class RendererCore;
class PhysicsCore;
class AssetManager;
class EntityManager;
class Clock;
class Input;
class Actor;
class Text;

class Core
{
private:
    std::unique_ptr<RendererCore> rendererCore;
    std::unique_ptr<PhysicsCore> physicsCore;
    std::unique_ptr<AssetManager> assetManager;
    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<Input> input;
    std::unique_ptr<Clock> clock;

    DrawQueue_t drawList;
    ObjectList_t colliderList;

    Core() = default;

public:
    //Core();
    bool Init();

    static Core& Get();
    RendererCore& GetRendererCore() { return *rendererCore; }
    PhysicsCore& GetPhysicsCore() { return *physicsCore; }
    AssetManager& GetAssetManager() { return *assetManager; }
    EntityManager& GetEntityManager() { return *entityManager; }


    void Begin();
    void Update();
    void StartMainLoop();
};
