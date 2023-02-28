#pragma once
#include "CoreTypes.h"

class PhysicsCore
{
private:
	//std::unordered_map<std::tuple<int,int>, std::unordered_multimap<int, Collider>> collisionSectors;
	//right now i will support only one collider component per object so this should be ok
	//later multimap and some more logic may be needed here
	std::unordered_map<int, Collider*> collisionMap;
	
	//planed for later to add begin and end overlap detection
	//std::vector<Vector2i, bool> continousCollisionPairs;

	std::tuple<int, int> GetSectorForPoint(Vector2i& wPoint);
	std::vector<Vector2i> GetSectorsForCollider(Collider* col);

	//bool TestPointOverlap(Vector2i& point, std::shared_ptr<Collider>);
	bool IsPairIdentical(Vector2i lIdPair, Vector2i rIdPair);
	bool IsCollisionContinous(Vector2i idPair);
	

	void CleanCollisonMap();
	void UpdateCollisonMap(ColliderList_t newCol);
	std::vector<Collider*> GetOverlapingColliders(Collider* col);
	std::vector<Collider*> GetOverlapingColliders(Vector2i point);

public:
	
	bool Init();

	void Update(ObjectList_t newCol);

};

