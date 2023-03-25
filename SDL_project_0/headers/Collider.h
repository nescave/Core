#pragma once
#include "Component.h"
#include "SceneComponent.h"

class Collider : 
	public SceneComponent,  public std::enable_shared_from_this<Collider>
{
private:
	float maxReach;
	Collider& SetMaxReach(SceneObject* own);
	Collider& SetMaxReach(float reach);

public:
	bool moved;
	std::unordered_map<uint32_t, WeakSceneObject> savedCollisions;

	Collider();
	//virtual ~Collider();
	virtual float GetReach() { return maxReach; }
	virtual void UpdateCollider(Vector2i size);

	virtual bool PointOverlaps(Vector2i&& point);
	virtual bool PointOverlaps(Vector2i& point);
	virtual bool ColliderOverlaps(Collider* other);
	//Vector2i GetPosition() override;
	//Transform GetTransform() override;

	void OnSpawn() override;

};
