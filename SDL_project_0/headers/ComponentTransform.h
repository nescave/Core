#pragma once
#include "Component.h"
#include "AnchorEnum.h"

class ComponentTransform : public Component
{
protected:
	Transform transform;
	Anchor anchor;

	ComponentTransform();
public:

	ComponentTransform& SetTransform(Transform& t);
	ComponentTransform& SetPosition(Vector2d& pos);
	ComponentTransform& SetRotation(double rot);
	ComponentTransform& SetScale(Vector2f& sc);

	ComponentTransform& SetTransform(Transform&& t) { return SetTransform(t); }
	ComponentTransform& SetPosition(Vector2d&& pos) { return SetPosition(pos); }
	ComponentTransform& SetScale(Vector2f&& sc) { return SetScale(sc); }


	ComponentTransform& SetAnchor(Anchor anch);

	virtual Transform GetWorldTransform();
	virtual Transform& GetLocalTransform();
	virtual Vector2d GetPosition();
	virtual double GetRotation();
	virtual Vector2f GetScale();

	Anchor GetAnchor() { return anchor; }

	void OnSpawn() override;
};
