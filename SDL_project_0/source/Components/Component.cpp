#include "stdafx.h"
#include "Component.h"


Component::Component() :
	owner(WeakSceneObject())
{}

void Component::OnSpawn(){}
