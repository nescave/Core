#include "stdafx.h"
#include "Core.h"
#include "Entity.h"
#include "EntityManager.h"

Entity::Entity(std::string n) :
	destroyed(false),
	bUpdate(true),
	id(EntityManager::Get()->GetFreeEntityID()),
	name(n)
{}

Entity::Entity() :
	Entity(((std::string)typeid(this).name()).append("_" + std::to_string(EntityManager::Get()->GetFreeEntityID())))
{}

void Entity::OnSpawn()
{
	printf("%s Spawns!\n", name.c_str());
}

void Entity::Begin() {
	printf("%s Begins!\n", name.c_str());

}
void Entity::Update(double dTime) {
}

void Entity::OnDestroy()
{
	printf("%s deleted!\n", name.c_str());
}

void Entity::Destroy()
{
	destroyed = true;
	OnDestroy();
	Core::Get().GetEntityManager().DeleteEntity(id);
}

bool Entity::IsValid()
{
	return destroyed;
}
