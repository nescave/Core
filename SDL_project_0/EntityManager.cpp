#include "stdafx.h"
#include "EntityManager.h"
#include "CoreFunctions.h"
#include "Entity.h"

static EntityManager* emInst;
void EntityManager::AddEntity(shared_Entity ent)
{
    gameEntities.insert({ ent->id, ent });
    createdEntities.push_back(ent);
}
EntityManager::EntityManager()
{
    if (emInst == nullptr) emInst = this;
}

EntityManager* EntityManager::Get()
{
    return emInst;
}

uint32_t EntityManager::GetFreeEntityID()
{
    return GetFirstFreeID(gameEntities);
}

void EntityManager::DeleteEntity(uint32_t id)
{
    if (gameEntities.find(id) != gameEntities.end()) {
        gameEntities.erase(gameEntities.find(id));
    }
}

void EntityManager::ClearCreatedEntities()
{
    createdEntities.clear();
}
