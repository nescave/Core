#include "stdafx.h"
#include "SceneComponent.h"
#include "RenderableObject.h"

ComponentTransform::ComponentTransform() :
	transform(),
	anchor(Anchor::Center)
{}

ComponentTransform& ComponentTransform::SetTransform(Transform & t)
{
	transform = t;
	return *this;
}

ComponentTransform& ComponentTransform::SetPosition(Vector2d& pos)
{
	transform.position = pos;
	return *this;
}

ComponentTransform& ComponentTransform::SetRotation(double rot)
{
	transform.rotation = rot;
	return *this;
}

ComponentTransform& ComponentTransform::SetScale(Vector2f& sc)
{
	transform.scale = sc;
	return *this;
}

ComponentTransform& ComponentTransform::SetAnchor(Anchor anch)
{
	anchor = anch;
	return *this;
}

Transform ComponentTransform::GetWorldTransform()
{
	auto ownerPtr = owner.lock();
	RenderObject* rObj = dynamic_cast<RenderObject*>(&*ownerPtr);
	if (!rObj) {
		return transform.CombineTransform(ownerPtr->GetWorldTransform());
	}
	Transform anchorTransf = rObj->GetWorldTransform();
	anchorTransf.position += rObj->GetAnchorOffset(anchor);
	return transform.CombineTransform(anchorTransf);
}

Transform& ComponentTransform::GetLocalTransform()
{
	return transform;
}

Vector2d ComponentTransform::GetPosition()
{
	return GetWorldTransform().position;
}

double ComponentTransform::GetRotation()
{
	return GetWorldTransform().rotation;
}

Vector2f ComponentTransform::GetScale()
{
	return GetWorldTransform().scale;
}

void ComponentTransform::OnSpawn()
{
	Component::OnSpawn();
}
