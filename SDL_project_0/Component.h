#pragma once
#include "CoreTypes.h"
#include "Object.h"

class Component 
{
private:

public:
	const std::string componentName;
	const weak_Object owner;
	
	Component(std::string name, weak_Object own);
	virtual ~Component()=default;
	virtual uint32_t GetOwnerId() { return owner.lock()->id; }

};
