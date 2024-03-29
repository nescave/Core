#include "stdafx.h"
#include "SceneComponent.h"
#include "RenderableObject.h"

SceneComponent::SceneComponent() :
	transform(),
	anchor(Anchor::Center)
{}

SceneComponent& SceneComponent::SetTransform(Transform& t)
{
	transform = t;
	return *this;
}

SceneComponent& SceneComponent::SetPosition(Vector2d& pos)
{
	transform.position = pos;
	return *this;
}

SceneComponent& SceneComponent::SetRotation(double rot)
{
	transform.rotation = rot;
	return *this;
}

SceneComponent& SceneComponent::SetScale(Vector2f& sc)
{
	transform.scale = sc;
	return *this;
}

SceneComponent& SceneComponent::SetAnchor(Anchor anch)
{
	anchor = anch;
	return *this;
}

Transform SceneComponent::GetAbsoluteTransform()
{
	auto ownerPtr = owner.lock();
	RenderableObject* rObj = dynamic_cast<RenderableObject*>(&*ownerPtr);
	if (!rObj) {
		return transform.CombineTransform(ownerPtr->GetAbsoluteTransform());
	}
	Transform anchorTransf = rObj->GetAbsoluteTransform();
	anchorTransf.position += rObj->GetAnchorOffset(anchor);
	return transform.CombineTransform(anchorTransf);
}

Transform& SceneComponent::GetLocalTransform()
{
	return transform;
}

Vector2d SceneComponent::GetPosition()
{
	return GetAbsoluteTransform().position;
}

double SceneComponent::GetRotation()
{
	return GetAbsoluteTransform().rotation;
}

Vector2f SceneComponent::GetScale()
{
	return GetAbsoluteTransform().scale;
}

Vector2d SceneComponent::GetUpVector() const
{
	return GetOwner()->GetUpVector();
}
Vector2d SceneComponent::GetRightVector() const
{
	return GetOwner()->GetRightVector();
}

void SceneComponent::OnSpawn()
{
	Component::OnSpawn();
}
