#include "stdafx.h"
#include "Core.h"
#include "Object.h"
#include "ObjectManager.h"
#include "TaskManager.h"

Object::Object() :
	destroyed(false),
	bUpdate(true),
	core(&Core::Get()),
	id(ObjectManager::Get()->GetFreeObjectID())
{}

void Object::SetupTask(double delay, const std::function<void()>& func)
{
	core->GetTaskManager().AddTask(shared_from_this(), Task(delay, func));
}

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

void Object::Destroy(double delay)
{
	SetupTask(delay, BINDFUNC(Destroy));
}

bool Object::IsValid()
{
	return destroyed;
}
