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
	collisionMap.clear();
	//std::vector<int> clearTable;
	//for (auto& tpl : collisionMap) {
	//	if (tpl.second.expired()) clearTable.push_back(tpl.first);
	//}
	//for (auto id : clearTable) {
	//	collisionMap.erase(id);
	//}
}

void PhysicsCore::UpdateCollisonMap(ColliderList_t newCol)
{
	CleanCollisonMap();
	for (auto& col : newCol) {
		collisionMap[col->GetOwnerId()] = col;
	}
}

std::vector<Collider*> PhysicsCore::GetOverlapingColliders(Collider* col)
{
	std::vector<Collider*> overlapingColliders;
	for (auto& tpl : collisionMap) {
		auto lCol = tpl.second;
		if (col == lCol) continue;
		if (lCol->PointOverlaps(col->GetPosition())) {
			overlapingColliders.push_back(lCol);
		}
	}
	return overlapingColliders;
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

void PhysicsCore::Update(ObjectList_t objs)
{
	ColliderList_t colliderList;
	for (auto& obj : objs) {
		colliderList.push_back(obj->GetComponentOfClass<Collider>());
	}
	UpdateCollisonMap(colliderList);
	for (auto& tpl : collisionMap) {
		auto col = tpl.second;
		if (col->moved) {
			auto overlapingColliders = GetOverlapingColliders(col);
			for (auto& tickedCol : overlapingColliders) {
				tickedCol->owner.lock()->OnBeginOverlap(col);
				col->owner.lock()->OnBeginOverlap(tickedCol);
			}
		}
	}
}
