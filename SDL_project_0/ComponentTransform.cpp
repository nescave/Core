#include "stdafx.h"
#include "ComponentTransform.h"
#include "RenderObject.h"

ComponentTransform::ComponentTransform(weak_Object own, std::string n) :
	Component(own, n),
	transform(),
	anchor(Anchor::Center)
{}

ComponentTransform::ComponentTransform(weak_Object own) :
	ComponentTransform(own, "")
{}

ComponentTransform::ComponentTransform() :
	ComponentTransform(weak_Object())
{}

ComponentTransform& ComponentTransform::SetTransform(Transform & t)
{
	transform = t;
	return *this;
}

ComponentTransform& ComponentTransform::SetPosition(Vector2i& pos)
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
	auto lOwner = owner.lock();
	RenderObject* rObj = static_cast<RenderObject*>(&*lOwner);
	if (!rObj) {
		return transform.CombineTransform(lOwner->GetWorldTransform());
	}
	Transform anchorTransf = Transform(lOwner->GetWorldTransform());
	anchorTransf.position += rObj->GetAnchorOffset(anchor);
	return transform.CombineTransform(anchorTransf);
}

Transform& ComponentTransform::GetLocalTransform()
{
	return transform;
}

Vector2i ComponentTransform::GetPosition()
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
