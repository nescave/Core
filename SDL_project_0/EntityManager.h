#pragma once
#include "CoreTypes.h"

class EntityManager
{
private:
	
    std::unordered_map<uint32_t, shared_Entity> gameEntities;
    std::vector<weak_Entity> createdEntities;

    //template unnecessary, stupid return 
    void AddEntity(shared_Entity ent);

public:
    friend class EntitySpawner;
    EntityManager();
    //bool Init();
    static EntityManager* Get();

    uint32_t GetFreeEntityID();
    void DeleteEntity(uint32_t Id);
    std::unordered_map<uint32_t, shared_Entity>& GetGameEntities() { return gameEntities; } //temp
    std::vector<weak_Entity> GetCreatedEntities() { return createdEntities; }
    void ClearCreatedEntities();
};

