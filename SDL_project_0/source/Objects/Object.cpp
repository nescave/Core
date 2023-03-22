#include "stdafx.h"
#include "Core.h"
#include "Object.h"
#include "ObjectManager.h"

Object::Object() :
	destroyed(false),
	bUpdate(true),
	id(ObjectManager::Get()->GetFreeObjectID()),
	name(((std::string)typeid(this).name()).append("_" + std::to_string(ObjectManager::Get()->GetFreeObjectID())))
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
	Core::Get().GetObjectManager().DeleteObject(id);
}

bool Object::IsValid()
{
	return destroyed;
}
