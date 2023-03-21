#pragma once
#include "Object.h"
#include "CoreTypes.h"
#include "AnchorEnum.h"

class Core;
class RenderableComponent;

class SceneObject : public Object, public std::enable_shared_from_this<SceneObject>
{
	friend class Collider;
protected:
	Transform transform;
	weak_Object parent;
	Core* core;

	std::map<const uint32_t, weak_Object> children;
	std::map<const uint32_t, shared_Component> components;

	void ClearParent();
	void ApplyTransform();
	bool ClearChildren();
	bool AddChild(weak_Object child);
	bool RemoveChild(weak_Object child);
	bool IsParentPossible(weak_Object par);

	void RegisterCollider(std::weak_ptr<Collider> col);

public:
	SceneObject();
	Transform& GetTransform(); // { return transform; }
	Vector2d& GetLocalPosition(); //{ return transform.position; }
	double GetLocalRotation(); // { return transform.rotation; }
	virtual Vector2f& GetLocalPivot(); // { return transform.pivot; }
	
	Transform GetWorldTransform();

	Vector2d GetWorldPosition();
	double GetWorldRotation();
	//Vector2f GetWorldPivot();

	const Vector2d GetUpVector();
	const Vector2d GetRightVector();

	weak_Object GetParent() { return parent; }
	std::map<const uint32_t, weak_Object>& GetChildren() { return children; }
	bool HasChildren() { return !children.empty(); }
	bool IsChild(weak_Object child);

	virtual SceneObject& SetTransform(Transform t);
	virtual SceneObject& SetPosition(Vector2d pos);
	virtual SceneObject& SetRotation(float rot) { transform.rotation = fmod(rot, 360); return *this; }
	virtual SceneObject& SetScale(Vector2f sc) { transform.scale = sc; return *this; }
	virtual SceneObject& SetPivot(Vector2f piv) { transform.pivot = piv; return *this; }
	
	SceneObject& SetParent(weak_Object par, const bool applyPreviousTransform = false);

	bool HasComponents() { return !components.empty(); }
	bool HasRenderableComponents();
	std::vector<RenderableComponent*> GetRenderableComponents();
	virtual bool HasCollider() override;
	bool RemoveComponent(std::type_index compClass);

	virtual void OnSpawn() { Object::OnSpawn(); }				//happens during actor spawning before actor is fully initialized (constructor behaviour)
	virtual void Begin() { Object::Begin(); }					//happens after full initialization
	virtual void Update(double dTime) { Object::Update(dTime); }
	virtual void OnBeginOverlap(Collider* col);
	virtual void OnEndOverlap(Collider* col);

	virtual Vector2d GetAnchorOffset(Anchor anch) {return Vector2d::zero;}

	template <
		typename T,
		class = std::enable_if_t<std::is_base_of_v<Component, T>>
	>
	std::weak_ptr<T> AddComponent() {
		uint32_t hash = (uint32_t)typeid(T).hash_code();
		
		auto comp = std::make_shared<T>();

		comp->owner = weak_from_this();
		comp->componentName = name.append("_component_").append(std::to_string(components.size()));
		components.insert({ hash, comp });

		comp->OnSpawn();
		return comp;
	}
	template<
		typename T,
		class = std::enable_if_t<std::is_base_of_v<Component, T>>
	>
	std::weak_ptr<T> GetComponentOfClass(bool log = true) {
		//std::weak_ptr<T> oComp = &*components[typeid(T).hash_code()];
		uint32_t hash = (uint32_t)typeid(T).hash_code();
		if (components.find(hash) == components.end()) {
			if (log) printf("No component matches %s class!\n", typeid(T).name());
			return std::weak_ptr<T>();
		}

		auto oComp = (std::weak_ptr<T>) components[typeid(T).hash_code()];
		return oComp;
	}
};
