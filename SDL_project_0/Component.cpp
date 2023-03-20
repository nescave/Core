#include "stdafx.h"
#include "Component.h"


Component::Component() :
	componentName(""),
	owner(weak_Object())
{}

void Component::OnSpawn(){}
