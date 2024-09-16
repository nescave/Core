#pragma once
#include "CollisionLayers.h"
#include "Component.h"
#include "SceneComponent.h"

struct ColliderExtents
{
	float right;
	float left;
	float bot;
	float top;

	[[nodiscard]] float GetMaxValue() const{ return std::max(right, std::max(left, std::max(bot,top)));}
	template<typename T>
	ColliderExtents& operator =(const T& rVal)
	{
		this->right = this->left = this->bot = this->top = (float)rVal;
		return *this;
	}
};

class Collider : 
	public SceneComponent,  public std::enable_shared_from_this<Collider>
{
protected:
	ColliderExtents extents;
	uint32_t layerMask;
	// virtual Collider& SetExtents(SceneObject* own) = 0;

public:
	bool moved;
	std::unordered_map<uint32_t, WeakSceneObject> savedCollisions;

	Collider();
	virtual Collider& SetExtents();
	virtual Collider& SetExtents(ColliderExtents ext);

	virtual ColliderExtents GetExtents() { return extents; }

	virtual bool PointOverlaps(Vector2i&& point);
	virtual bool PointOverlaps(Vector2i& point) = 0;
	virtual bool ColliderOverlaps(Collider* other) = 0;

	uint32_t GetLayerMask();
	Collider& SetLayerMask(uint32_t mask);
	Collider& AddToLayer(uint32_t layer);
	Collider& RemoveFromLayer(uint32_t layer);
	bool IsOnLayers(uint32_t layers);

	
	void OnSpawn() override;
};
