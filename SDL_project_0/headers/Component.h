#pragma once
#include "CoreTypes.h"
#include "SceneObject.h"

class Component 
{
	friend class SceneObject;
protected:
	WeakSceneObject owner;

	Component();
public:
	std::string componentName;
	
	virtual ~Component()=default;

	SharedSceneObject GetOwner() { return owner.lock(); }
	virtual uint32_t GetOwnerId() { return owner.lock()->id; }
	virtual bool ShouldRender() { return false; }

	virtual void OnSpawn();

};
