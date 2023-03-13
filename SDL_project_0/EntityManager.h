#pragma once
#include "CoreTypes.h"

class EntityManager
{
private:
	
    std::unordered_map<uint32_t, shared_Entity> gameEntities;

    template <typename T>
    std::weak_ptr<T> AddEntity(std::shared_ptr<T> ent) {
        gameEntities.insert({ ent->id, ent });
        return ent;
    }

public:
    friend class EntitySpawner;
    EntityManager();
    //bool Init();
    static EntityManager* Get();

    void DeleteEntity(uint32_t Id);
    std::unordered_map<uint32_t, shared_Entity>& GetGameEntities() { return gameEntities; } //temp
};

