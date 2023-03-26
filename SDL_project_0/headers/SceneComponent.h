#pragma once
#include "Component.h"
#include "AnchorEnum.h"

class SceneComponent : public Component
{
protected:
	Transform transform;
	Anchor anchor;

	SceneComponent();
public:

	SceneComponent& SetTransform(Transform& t);
	SceneComponent& SetPosition(Vector2d& pos);
	SceneComponent& SetRotation(double rot);
	SceneComponent& SetScale(Vector2f& sc);

	SceneComponent& SetTransform(Transform&& t) { return SetTransform(t); }
	SceneComponent& SetPosition(Vector2d&& pos) { return SetPosition(pos); }
	SceneComponent& SetScale(Vector2f&& sc) { return SetScale(sc); }


	SceneComponent& SetAnchor(Anchor anch);

	virtual Transform GetWorldTransform();
	virtual Transform& GetLocalTransform();
	virtual Vector2d GetPosition();
	virtual double GetRotation();
	virtual Vector2f GetScale();

	Vector2d GetUpVector() const;
	Vector2d GetRightVector() const;

	Anchor GetAnchor() { return anchor; }

	void OnSpawn() override;
};
