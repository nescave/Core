#pragma once
#include "Component.h"
#include "SceneComponent.h"

class Collider : 
	public ComponentTransform,  public std::enable_shared_from_this<Collider>
{
private:
	float maxReach;
	Collider& SetMaxReach(Object* own);
	Collider& SetMaxReach(float reach);

public:
	bool moved;
	std::unordered_set<uint32_t> savedCollisions;

	Collider();
	//virtual ~Collider();
	virtual float GetReach() { return maxReach; }
	virtual void UpdateCollider(Vector2i size);

	virtual bool PointOverlaps(Vector2i&& point);
	virtual bool PointOverlaps(Vector2i& point);
	//virtual bool ColliderOverlaps()
	//Vector2i GetPosition() override;
	//Transform GetTransform() override;

	void OnSpawn() override;

};
