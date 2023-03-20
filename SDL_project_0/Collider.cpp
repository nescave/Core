#include "stdafx.h"
#include "Collider.h"
#include "Core.h"
#include "PhysicsCore.h"
#include "RenderObject.h"

Collider& Collider::SetMaxReach(Object* own)
{
	auto rObj = static_cast<RenderObject*>(&*own);
	if (!rObj) return *this;
	Vector2i scrSize = rObj->GetScreenSize();
	return SetMaxReach((float)((scrSize * rObj->GetTransform().pivot).Length()));
}

Collider& Collider::SetMaxReach(float reach)
{
	maxReach = reach;
	return *this;
}

Collider::Collider() :
	maxReach(10),
	moved(true)
{}

void Collider::UpdateCollider(Vector2i size)
{
	//auto lTransform = transform.CombineTransform(owner.lock()->GetUnifiedTransform());
	//Vector2i center = lTransform.position + size * lTransform.pivot;
	//int dx = fmax(center.x, size.x - center.x);
	//int dy = fmax(center.y, size.y - center.y);
	//maxReach = sqrt(pow(dx, 2) + pow(dy, 2));

	transform.position = size*transform.pivot;
	maxReach = (float)size.Length();
}

bool Collider::PointOverlaps(Vector2i&& point)
{
	return PointOverlaps(point);
}

bool Collider::PointOverlaps(Vector2i& point)
{
	double dist = Vector2i::Distance(point, this->GetPosition());
	return dist < this->GetReach();
}

void Collider::OnSpawn()
{
	auto ownerPtr = owner.lock();
	if (!ownerPtr) return;
	ownerPtr->RegisterCollider(weak_from_this());
	
	SetMaxReach(&*ownerPtr);
	
	//Vector2f lPivot = { .5,.5 };
	//lPivot = lOwner->GetTransform().pivot;
}

//Vector2i Collider::GetPosition() {
//	auto oTransform = transform.CombineTransform(owner.lock()->GetUnifiedTransform());
//	return oTransform.position;
//}
