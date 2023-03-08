#include "stdafx.h"
#include "Collider.h"
#include "Core.h"
#include "PhysicsCore.h"

Collider::Collider(std::string name, weak_Object own) :
	Component(name, own),
	maxReach(10),
	transform(Vector2i::zero, 0, Vector2f::one, owner.lock()->GetTransform().pivot),
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

Vector2i Collider::GetPosition() {
	auto oTransform = transform.CombineTransform(owner.lock()->GetUnifiedTransform());
	return oTransform.position;
}
