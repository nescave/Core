#include "stdafx.h"
#include "UniversalSpawner.h"

UniversalSpawner::UniversalSpawner() :
    spawnRate(0),
    spawnRandomness(0),
    maxScale(0),
    minScale(0),
    bSpawning(true)
{}

void UniversalSpawner::SetSpawningState(const bool state)
{
    bSpawning = state;
}
