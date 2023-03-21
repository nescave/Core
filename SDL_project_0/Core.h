#pragma once
#include <Windows.h>
#include "RendererUtils.h"
#include "CoreTypes.h"

constexpr int screen_width = 1280;
constexpr int screen_height = 800;
class RendererCore;
class PhysicsCore;
class AssetManager;
class EntityManager;
class Clock;
class InputManager;
class Actor;
class Text;

class Core
{
private:
    std::unique_ptr<RendererCore> rendererCore;
    std::unique_ptr<PhysicsCore> physicsCore;
    std::unique_ptr<AssetManager> assetManager;
    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<InputManager> input;
    std::unique_ptr<Clock> clock;

    DrawQueue_t drawList;

    Core() = default;

public:
    //Core();
    bool Init();

    static Core& Get();
    RendererCore& GetRendererCore() { return *rendererCore; }
    PhysicsCore& GetPhysicsCore() { return *physicsCore; }
    AssetManager& GetAssetManager() { return *assetManager; }
    EntityManager& GetEntityManager() { return *entityManager; }
    //InputManager& GetInputManager() { return *input; }

    void Begin();
    void Update();
    void StartMainLoop();
};
