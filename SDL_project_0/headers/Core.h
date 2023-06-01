#pragma once
#include "RendererUtils.h"
#include "CoreTypes.h"

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 800;
class RendererCore;
class PhysicsCore;
class AssetManager;
class ObjectManager;
class Clock;
class TaskManager;
class InputManager;
class Actor;
class Text;

class Core
{
private:
    std::unique_ptr<RendererCore> rendererCore;
    std::unique_ptr<PhysicsCore> physicsCore;
    std::unique_ptr<AssetManager> assetManager;
    std::unique_ptr<ObjectManager> objectManager;
    std::unique_ptr<InputManager> input;
    std::unique_ptr<Clock> clock;
    std::unique_ptr<TaskManager> taskManager;


    Core() = default;

public:
    //Core();
    bool Init();

    double lastUpdateDuration;
    
    static Core& Get();
    RendererCore& GetRendererCore() { return *rendererCore; }
    PhysicsCore& GetPhysicsCore() { return *physicsCore; }
    AssetManager& GetAssetManager() { return *assetManager; }
    ObjectManager& GetObjectManager() { return *objectManager; }
    TaskManager& GetTaskManager() { return *taskManager; }

    void Begin();
    void AddToDrawList(std::vector<DrawCall>& drawList, const std::shared_ptr<Object>& obj);
    void Update();
    void StartMainLoop();
};
