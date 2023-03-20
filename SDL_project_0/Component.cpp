#include "stdafx.h"
#include "Component.h"


Component::Component(weak_Object own, std::string name) :
	componentName(name),
	owner(own)
{
	// if nullptr
	if (componentName == "") componentName = owner.lock()->name.append("_component");
}

Component::Component(weak_Object own) :
	Component(own, "")
{}

Component::Component() : 
	Component(weak_Object())
{}
