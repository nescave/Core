#pragma once
#include "Object.h"
#include "CoreTypes.h"
#include "AnchorEnum.h"

class RenderableComponent;

class SceneObject : public Object
{
	WeakSceneObject weakThis;

protected:
	Transform transform;
	WeakSceneObject parent;
	
	std::map<const uint32_t, WeakSceneObject> children;
	std::map<const size_t, SharedComponent> components;

	void ClearParent();
	void ApplyTransform();
	bool ClearChildren();
	bool AddChild(WeakSceneObject child);
	bool RemoveChild(WeakSceneObject child);
	bool IsParentPossible(WeakSceneObject par);

	void RegisterCollider(std::weak_ptr<Collider> col);

	SceneObject();

public:
	friend class Collider;

	Transform& GetTransform(); 
	Vector2d& GetPosition(); 
	double GetRotation();
	Vector2f& GetScale();
	
	virtual Vector2f& GetPivot(); 
	
	Transform GetAbsoluteTransform();
	Vector2d GetAbsolutePosition();
	double GetAbsoluteRotation();
	Vector2f GetAbsoluteScale();

	Vector2d GetUpVector() const;
	Vector2d GetRightVector() const;

	double GetLookAtRotation(const Vector2d& pos);
	
	WeakSceneObject GetParent() const { return parent; }
	WeakSceneObject GetWeakThis() const { return weakThis; }
	std::map<const uint32_t, WeakSceneObject>& GetChildren() { return children; }
	bool HasChildren() const { return !children.empty(); }
	bool IsChild(WeakSceneObject child) const;

	virtual SceneObject& SetTransform(Transform t);
	virtual SceneObject& SetPosition(Vector2d pos);
	virtual SceneObject& SetRotation(double rot) { transform.rotation = fmod(rot, 360); return *this; }
	virtual SceneObject& SetScale(Vector2f sc) { transform.scale = sc; return *this; }
	virtual SceneObject& SetPivot(Vector2f piv) { transform.pivot = piv; return *this; }
	
	SceneObject& SetParent(WeakSceneObject par, const bool applyPreviousTransform = false);

	bool HasComponents() const { return !components.empty(); }
	bool HasRenderableComponents();
	std::vector<RenderableComponent*> GetRenderableComponents();
	bool RemoveComponent(std::type_index compClass);
	bool HasCollider() override;

	void OnSpawn() override; 				//happens during actor spawning before actor is fully initialized (constructor behaviour)
	void Begin() override { Object::Begin(); }					//happens after full initialization
	void Update(double dTime) override;
	virtual void OnBeginOverlap(SharedSceneObject other);
	virtual void OnEndOverlap(SharedSceneObject other);

	virtual Vector2d GetAnchorOffset(Anchor anch) {return Vector2d::zero;}

	template <
		typename T,
		class = std::enable_if_t<std::is_base_of_v<Component, T>>
	>
	std::shared_ptr<T> AddComponent() {
		uint32_t hash = (uint32_t)typeid(T).hash_code();
		
		auto comp = std::make_shared<T>();
		comp->owner = weakThis;
		comp->componentName = name;
		comp->componentName.append("_").append(typeid(T).name()).append("_component_").append(std::to_string(components.size()));
		components.insert({ hash, comp });

		comp->OnSpawn();
		return comp;
	}
	template<
		typename T,
		class = std::enable_if_t<std::is_base_of_v<Component, T>>
	>
	std::weak_ptr<T> GetComponentOfClass(bool log = true) {
		auto const hash = typeid(T).hash_code();
		if (components.find(hash) == components.end()) {
			if (log) printf("No component matches %s class!\n", typeid(T).name());
			return std::weak_ptr<T>();
		}

		auto oComp = std::static_pointer_cast<T>(components[hash]);
		return oComp;
	}
};
