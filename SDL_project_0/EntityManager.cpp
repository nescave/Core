#include "stdafx.h"
#include "EntityManager.h"
#include "CoreFunctions.h"

static EntityManager* emInst;
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
