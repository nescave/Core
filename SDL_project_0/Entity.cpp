#include "stdafx.h"
#include "Core.h"
#include "Entity.h"
#include "EntityManager.h"

Entity::Entity(int iD, std::string n) :
	destroyed(false),
	bUpdate(true),
	id(iD),
	name(n)
{}

void Entity::Begin() {
	printf("%d checked!\n", id);

}
void Entity::Update(double dTime) {
	if (destroyed && !bUpdate) return;
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
