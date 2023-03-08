#pragma once
#include "Component.h"

class Collider : public Component, public std::enable_shared_from_this<Collider>
{
private:
	float maxReach;
	Transform transform;
public:
	bool moved;
	std::unordered_set<int> savedCollisions;

	Collider(std::string name, weak_Object own);
	//virtual ~Collider();
	virtual float GetReach() { return maxReach; }
	virtual void UpdateCollider(Vector2i size);

	virtual bool PointOverlaps(Vector2i&& point);
	virtual bool PointOverlaps(Vector2i& point);
	//virtual bool ColliderOverlaps()
	Vector2i GetPosition();
};
