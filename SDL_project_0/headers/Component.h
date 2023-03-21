#pragma once
#include "CoreTypes.h"
#include "Object.h"

class Component 
{
	friend class Object;
protected:
	weak_Object owner;

	Component();
public:
	std::string componentName;
	
	virtual ~Component()=default;

	shared_Object GetOwner() { return owner.lock(); }
	virtual uint32_t GetOwnerId() { return owner.lock()->id; }
	virtual bool ShouldRender() { return false; }

	virtual void OnSpawn();

};
