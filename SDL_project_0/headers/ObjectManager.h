#pragma once
#include "CoreTypes.h"

class ObjectManager
{
private:
	
    std::unordered_map<uint32_t, SharedObject> gameObjects;
    std::vector<WeakObject> createdObjects;

    //template unnecessary, stupid return 
    void AddObject(SharedObject obj);

public:
    friend class ObjectSpawner;
    ObjectManager();
    //bool Init();
    static ObjectManager* Get();

    uint32_t GetFreeObjectID();
    void DeleteObject(uint32_t Id);
    std::unordered_map<uint32_t, SharedObject>& GetGameObjects() { return gameObjects; } //temp
    std::vector<WeakObject> GetCreatedObjects() { return createdObjects; }
    void ClearCreatedObjects();
};

