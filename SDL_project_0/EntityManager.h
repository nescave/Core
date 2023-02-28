#pragma once
#include "CoreTypes.h"

class EntityManager
{
private:
	
    std::unordered_map<int, shared_Entity> gameEntities;

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

    void DeleteEntity(int Id);
    std::unordered_map<int, shared_Entity>& GetGameEntities() { return gameEntities; } //temp
};

