#pragma once
#include "CoreTypes.h"
#include "CollisionLayers.h"
#include "CollisionData.h"

class PhysicsCore
{
private:

	//right now i will support only one collider component per object so this should be ok
	std::unordered_map<uint32_t, std::weak_ptr<Collider>> collisionMap;
	//later multimap and some more logic may be needed here
	
	std::queue<std::weak_ptr<Collider>> collidersToAdd;

	std::tuple<int, int> GetSectorForPoint(Vector2i& wPoint);
	std::vector<Vector2i> GetSectorsForCollider(Collider* col);

	bool IsPairIdentical(Vector2i lIdPair, Vector2i rIdPair);
	

	void CleanCollisonMap();
	void UpdateCollisonMap();
	std::set<SharedSceneObject> GetOverlapingObjects(Collider* col);
	std::set<SharedSceneObject> GetOverlapingObjects(Vector2i point);

public:
	
	bool Init();

	void AddCollider(std::weak_ptr<Collider> col);
	std::pair<bool, CollisionData> RayCast(const Vector2d& start, Vector2d& direction, float range, ECollisionLayer layer);
	std::pair<bool, CollisionData> RayCast(const Vector2d& start, Vector2d&& direction, float range, ECollisionLayer layer);

	void Update();

};

