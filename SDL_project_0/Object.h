#pragma once
#include "Entity.h"
#include "CoreTypes.h"

class Object : public Entity, public std::enable_shared_from_this<Object>
{
protected:
	Transform transform;
	weak_Object parent;

	std::map<const int, weak_Object> children;
	std::map<const int, shared_Component> components;

	void ClearParent();
	void ApplyTransform();
	bool ClearChildren();
	bool AddChild(weak_Object child);
	bool RemoveChild(weak_Object child);
	//bool IsInChildHierarchy(shared_Object obj);
	bool IsParentPossible(weak_Object par);

	void RegisterCollider(std::weak_ptr<Collider> col);

public:
	Object(int iD, std::string n, Transform t);
	//virtual ~Object();
	Transform& GetTransform(); // { return transform; }
	Vector2i& GetLocalPosition(); //{ return transform.position; }
	double GetLocalRotation(); // { return transform.rotation; }
	virtual Vector2f& GetLocalPivot(); // { return transform.pivot; }
	
	Transform GetUnifiedTransform();

	Vector2i GetWorldPosition();
	double GetWorldRotation();
	Vector2f GetWorldPivot();

	Vector2f GetUpVector();
	Vector2f GetRightVector();

	weak_Object GetParent() { return parent; }
	std::map<const int, weak_Object>& GetChildren() { return children; }
	bool HasChildren() { return !children.empty(); }
	bool IsChild(weak_Object child);

	virtual Object& SetTransform(Transform t) { transform = t; return *this; }
	virtual Object& SetPosition(Vector2i pos) { transform.position = pos; return *this; }
	virtual Object& SetRotation(float rot) { transform.rotation = fmod(rot, 360); return *this; }
	virtual Object& SetScale(Vector2f sc) { transform.scale = sc; return *this; }
	virtual Object& SetPivot(Vector2f piv) { transform.pivot = piv; return *this; }
	
	Object& SetParent(weak_Object par, const bool applyPreviousTransform = false);

	virtual bool HasCollider() override;
	bool RemoveComponent(std::type_index compClass);


	virtual void Begin(double dTime) { Entity::Begin(); }
	virtual void Update(double dTime) { Entity::Update(dTime); }
	virtual void OnBeginOverlap(Collider* col);
	virtual void OnEndOverlap(Collider* col);

	template <
		typename T,
		class = std::enable_if_t<std::is_base_of_v<Component, T>>
	>
	std::weak_ptr<T> AddComponent(const std::string name) {
		auto hash = typeid(T).hash_code();
		if (components.find(hash) != components.end()){
			printf("Component of type <%s> already added to this object! %s\n",typeid(T).name(), name.c_str());
			return std::weak_ptr<T>();
		}
		auto sPtr = std::make_shared<T>(name, weak_from_this());
		components.insert({ hash, sPtr });
		if (typeid(T) == typeid(Collider)) RegisterCollider(sPtr);
		return sPtr;
	}
	template<
		typename T,
		class = std::enable_if_t<std::is_base_of_v<Component, T>>
	>
	std::weak_ptr<T> GetComponentOfClass(bool log = true) {
		//std::weak_ptr<T> oComp = &*components[typeid(T).hash_code()];
		auto hash = typeid(T).hash_code();
		if (components.find(hash) == components.end()) {
			if (log) printf("No component matches %s class!\n", typeid(T).name());
			return std::weak_ptr<T>();
		}

		auto oComp = (std::weak_ptr<T>) components[typeid(T).hash_code()];
		return oComp;
	}
};
