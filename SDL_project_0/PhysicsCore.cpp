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
	std::vector<int> clearTable;
	for (auto& tpl : collisionMap) {
		if (tpl.second.expired()) clearTable.push_back(tpl.first);
	}
	for (auto id : clearTable) {
		collisionMap.erase(id);
	}
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

std::vector<Collider*> PhysicsCore::GetOverlapingColliders(Collider* col)
{
	std::vector<Collider*> overlapingColliders;
	for (auto& tpl : collisionMap) {
		auto lCol = &*tpl.second.lock();
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

void PhysicsCore::AddCollider(std::weak_ptr<Collider> col)
{
	collidersToAdd.push(col);
}

void PhysicsCore::Update()
{
	//std::vector<std::weak_ptr<Collider>> colliderList;
	UpdateCollisonMap();

	for (auto& tpl : collisionMap) {
		auto col = &*tpl.second.lock();
		if (!col) continue;
		std::unordered_set<uint32_t> savedColsCpy = col->savedCollisions;

		if (col->moved) {
			auto overlapingColliders = GetOverlapingColliders(col);
			for (auto& tickedCol : overlapingColliders) {
				//tickedCol->owner.lock()->OnBeginOverlap(col);
				auto tickedColID = tickedCol->GetOwnerId();
				if (savedColsCpy.find(tickedColID) == savedColsCpy.end()) {
					col->GetOwner()->OnBeginOverlap(tickedCol);
					col->savedCollisions.insert(tickedColID);
				}
				else {
					savedColsCpy.erase(tickedColID);
				}
				
			}
		}
		for (auto id : savedColsCpy) {
			auto detachedCol = collisionMap[id].expired() ? nullptr : &*collisionMap[id].lock();
			col->GetOwner()->OnEndOverlap(detachedCol);
			col->savedCollisions.erase(id);
		}
	}
}
