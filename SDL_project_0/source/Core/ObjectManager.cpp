#include "stdafx.h"
#include "ObjectManager.h"
#include "CoreFunctions.h"
#include "Object.h"

static ObjectManager* omInst;
void ObjectManager::AddObject(SharedObject obj)
{
    gameObjects.insert({ obj->id, obj });
    createdObjects.push_back(obj);
}
ObjectManager::ObjectManager()
{
    if (omInst == nullptr) omInst = this;
}

ObjectManager* ObjectManager::Get()
{
    return omInst;
}

uint32_t ObjectManager::GetFreeObjectID()
{
    return GetFirstFreeID(gameObjects);
}

void ObjectManager::DeleteObject(uint32_t id)
{
    objectsToDelete.insert(id);
}

void ObjectManager::ApplyDelete()
{
    for(auto id : objectsToDelete)
    {
        gameObjects.erase(id);
    }
    objectsToDelete.clear();
}

void ObjectManager::ClearCreatedObjects()
{
    createdObjects.clear();
}
