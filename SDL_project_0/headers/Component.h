#pragma once
#include "CoreTypes.h"
#include "SceneObject.h"

class Core;

class Component 
{
	friend class SceneObject;
protected:
	WeakSceneObject owner;
	Core* core;

	Component();
public:
	std::string componentName;
	
	virtual ~Component()=default;

	SharedSceneObject GetOwner() const { return owner.lock(); }
	virtual uint32_t GetOwnerId() { return owner.lock()->id; }
	virtual bool ShouldRender() { return false; }

	virtual void OnSpawn();
	virtual void Update(double dTime);
	virtual void OnDestroy();
};
