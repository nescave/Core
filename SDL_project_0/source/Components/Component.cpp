#include "stdafx.h"
#include "Component.h"


Component::Component() :
	componentName(""),
	owner(WeakSceneObject())
{}

void Component::OnSpawn(){}
