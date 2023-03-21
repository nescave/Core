#include "stdafx.h"
#include "Core.h"
#include "Object.h"
#include "ObjectManager.h"

Object::Object() :
	destroyed(false),
	bUpdate(true),
	id(EntityManager::Get()->GetFreeEntityID()),
	name(((std::string)typeid(this).name()).append("_" + std::to_string(EntityManager::Get()->GetFreeEntityID())))
{}

void Object::OnSpawn()
{
	printf("%s Spawns!\n", name.c_str());
}

void Object::Begin() {
	printf("%s Begins!\n", name.c_str());

}
void Object::Update(double dTime) {
}

void Object::OnDestroy()
{
	printf("%s deleted!\n", name.c_str());
}

void Object::Destroy()
{
	destroyed = true;
	OnDestroy();
	Core::Get().GetEntityManager().DeleteEntity(id);
}

bool Object::IsValid()
{
	return destroyed;
}
