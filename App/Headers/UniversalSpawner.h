#pragma once
#include "Core.h"
#include "SceneObject.h"
#include "ObjectSpawner.h"
#include "CoreTypes.h"


class Core;

class UniversalSpawner : public Object
{
public:
    float spawnRate;
    float spawnRandomness;
    float maxScale;
    float minScale;
    Transform inititalTransform;

    UniversalSpawner();
    
    void SetSpawningState(const bool state);
    bool IsSpawning() const {return bSpawning;}
    template<
        typename T,
        class = std::enable_if_t<std::is_base_of_v<Actor, T>> 
    >
    void StartSpawner(Transform initTransform, float sRate, float sRandomness, float maxSc, float minSc)
    {
        inititalTransform = initTransform;
        spawnRate = sRate;
        spawnRandomness = sRandomness;
        maxScale = maxSc;
        minScale = minSc;
        Spawn<T>();
        // SetupTask(5, BINDFUNC(Spawn<T>));
    }
    template<
        typename T,
        class = std::enable_if_t<std::is_base_of_v<Actor, T>> 
    >
    void Spawn()
    {
        // printf("wakuwaku\n");
        ObjectSpawner::SpawnObject<T>(inititalTransform);
        if(bSpawning) SetupTask(3, BINDFUNC(Spawn<T>));
    }
    
private:
    bool bSpawning;

};
