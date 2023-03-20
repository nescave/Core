#pragma once
#include "CoreTypes.h"
#include "Object.h"

class Component 
{
protected:
	weak_Object owner;

public:
	std::string componentName;
	
	Component(weak_Object own, std::string name);
	Component(weak_Object own);
	Component();
	virtual ~Component()=default;

	shared_Object GetOwner() { return owner.lock(); }
	virtual uint32_t GetOwnerId() { return owner.lock()->id; }
	virtual bool ShouldRender() { return false; }

};
