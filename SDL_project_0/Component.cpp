#include "stdafx.h"
#include "Component.h"


Component::Component(std::string name, weak_Object own) :
	componentName(name),
	owner(own)
{}