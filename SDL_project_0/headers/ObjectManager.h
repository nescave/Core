#pragma once
#include "CoreTypes.h"

class ObjectManager
{
private:
	
    std::unordered_map<uint32_t, SharedObject> gameObjects;
    std::vector<WeakObject> createdObjects;
    std::set<uint32_t> objectsToDelete;

    void AddObject(SharedObject obj);

public:
    friend class ObjectSpawner;
    ObjectManager();
    //bool Init();
    static ObjectManager* Get();

    uint32_t GetFreeObjectID();
    void DeleteObject(uint32_t id);
    std::unordered_map<uint32_t, SharedObject>& GetGameObjects() { return gameObjects; } //temp
    std::vector<WeakObject>& GetCreatedObjects() { return createdObjects; }
    void ApplyDelete();
    void ClearCreatedObjects();

    //TODO better way of getting single object ptr (this or from id)
    // template <typename T>
    // std::shared_ptr<T> GetObject(uint32_t id)
    // {
    //     if(gameObjects[id])
    //     {
    //         return std::dynamic_pointer_cast<T>()
    //     }
    // }
};

