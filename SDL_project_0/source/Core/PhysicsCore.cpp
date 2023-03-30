#include "stdafx.h"
#include "PhysicsCore.h"
#include "Collider.h"

//bool PhysicsCore::TestPointOverlap(Vector2i& point, std::shared_ptr<Collider> col)
//{
//	return Vector2i::Distance(point, col->GetPosition()) < col->GetReach();
//}

bool PhysicsCore::IsPairIdentical(Vector2i lIdPair, Vector2i rIdPair)
{
	return lIdPair == rIdPair || lIdPair.x == rIdPair.y && lIdPair.y == rIdPair.x;
}

void PhysicsCore::CleanCollisonMap()
{
	for(auto it = collisionMap.begin(); it != collisionMap.end();)
	{
		if(it->second.expired())
		{
			it = collisionMap.erase(it);
		}else
		{
			++it;
		}
	}
	//
	// std::vector<int> clearTable;
	// for (auto& tpl : collisionMap) {
	// 	if (tpl.second.expired()) clearTable.push_back(tpl.first);
	// }
	// for (auto id : clearTable) {
	// 	collisionMap.erase(id);
	// }
}

void PhysicsCore::UpdateCollisonMap()
{
	CleanCollisonMap();
	while (collidersToAdd.size() > 0) {
		auto col = collidersToAdd.front().lock();
		if (col)
			collisionMap[col->GetOwnerId()] = col;
		collidersToAdd.pop();
	}
}

std::set<SharedSceneObject> PhysicsCore::GetOverlapingObjects(Collider* col)
{
	std::set<SharedSceneObject> overlapingObjects;
	for (auto& tpl : collisionMap) {
		auto collider = &*tpl.second.lock();
		if (col == collider) continue;
		if (collider->ColliderOverlaps(col)) {
			overlapingObjects.insert(collider->GetOwner());
		}
	}
	return overlapingObjects;
}

std::set<SharedSceneObject> PhysicsCore::GetOverlapingObjects(Vector2i point)
{
	std::set<SharedSceneObject> overlapingObjects;
	for (auto& tpl : collisionMap)
	{
		auto collider = &*tpl.second.lock();
		if(collider->PointOverlaps(point))
		{
			overlapingObjects.insert(collider->GetOwner());
		}
	}
	return overlapingObjects;
}

//std::vector<std::shared_ptr<Collider>> PhysicsCore::GetOverlapingColliders(Vector2i point)
//{
//	std::vector<std::shared_ptr<Collider>> overlapingColliders;
//	for (auto& tpl : collisionMap) {
//		auto col = tpl.second.lock();
//		if (col->PointOverlaps(point)) {
//			overlapingColliders.push_back(col);
//		}
//	}
//	return std::vector<std::shared_ptr<Collider>>();
//}

bool PhysicsCore::Init()
{
	return true;
}

void PhysicsCore::AddCollider(std::weak_ptr<Collider> col)
{
	collidersToAdd.push(col);
}

std::pair<bool, CollisionData> PhysicsCore::RayCast(
	const Vector2d& start,
	Vector2d& direction,
	const float range,
	ECollisionLayer layer
	)
{
	Vector2d testPos = start+direction;
	std::set<SharedSceneObject> foundObjects;
	float traveledDist = 0;
	do
	{
		foundObjects = GetOverlapingObjects(testPos);
		testPos += direction;	
		traveledDist +=1;
	}
	while (foundObjects.empty() && traveledDist<range);
	auto collisionData = CollisionData();
	collisionData.distance = traveledDist;
	collisionData.hitPosition = start+direction*traveledDist;
	if(foundObjects.empty()) return std::make_pair(false, collisionData);
	const SharedSceneObject foundObject = *foundObjects.begin();
	collisionData.object = foundObject;
	return std::make_pair(true, collisionData);
}

std::pair<bool, CollisionData> PhysicsCore::RayCast(
	const Vector2d& start,
	Vector2d&& direction,
	float range,
	ECollisionLayer layer
	)
{
	return RayCast(start, direction, range, layer);
}

void PhysicsCore::Update()
{
	//std::vector<std::weak_ptr<Collider>> colliderList;
	UpdateCollisonMap();

	for (auto& tpl : collisionMap) {
		auto col = &*tpl.second.lock();
		if (!col) continue;
		auto& savedColls = col->savedCollisions;
		auto overlapingObjects = GetOverlapingObjects(col);
		if (col->moved) {
			for (auto& tickedObject : overlapingObjects) {
				//tickedCol->owner.lock()->OnBeginOverlap(col);
				auto tickedColID = tickedObject->id;
				if (savedColls.find(tickedColID) == savedColls.end()) {
					col->GetOwner()->OnBeginOverlap(tickedObject);
					savedColls.insert(std::make_pair(tickedColID, tickedObject));
				}
				// else {
				// 	savedColls.erase(tickedColID);
				// }
				
			}
		}
		if(savedColls.empty()) continue;
		// auto savedCollsCopy = savedColls;
		for(auto it = savedColls.begin(); it != savedColls.end();)
		{
			if(overlapingObjects.find(it->second.lock()) == overlapingObjects.end())
			{
				col->GetOwner()->OnEndOverlap(it->second.lock());
				it = savedColls.erase(it);
			}else
			{
				++it;
			}
		}
	}
}
