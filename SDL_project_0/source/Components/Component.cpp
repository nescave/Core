#include "stdafx.h"
#include "Component.h"
#include "Core.h"

Component::Component() :
	owner(WeakSceneObject()),
	core(&Core::Get())
{}

void Component::OnSpawn(){}

void Component::Update(double dTime)
{
}

void Component::OnDestroy()
{
}
