#include "stdafx.h"
#include "EntityManager.h"

static EntityManager* emInst;
EntityManager::EntityManager()
{
    if (emInst == nullptr) emInst = this;

}

EntityManager* EntityManager::Get()
{
    return emInst;
}

void EntityManager::DeleteEntity(int id)
{
    if (gameEntities.find(id) != gameEntities.end()) {
        gameEntities.erase(gameEntities.find(id));
    }
}
