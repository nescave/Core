#include "stdafx.h"
#include "Object.h"
#include "Core.h"
#include "Collider.h"
#include "RenderableComponent.h"
#include "PhysicsCore.h"
#include "EntityManager.h"

Object::Object() :
	transform(Transform()),
	parent(weak_Object()),
	children(std::map<const uint32_t, weak_Object>()),
	core(&Core::Get())
{}

Transform& Object::GetTransform()
{
	return transform;
}
Vector2i& Object::GetLocalPosition()
{
	return transform.position;
}
double Object::GetLocalRotation()
{
	return transform.rotation;
}
Vector2f& Object::GetLocalPivot()
{
	return transform.pivot;
}
Transform Object::GetWorldTransform() //transform probably should be passed by reference but thats problematic
{
	auto lParent = parent.lock();
	if (!lParent) return transform;
	return transform.CombineTransform(lParent->GetWorldTransform());
}

Vector2i Object::GetWorldPosition()
{

	return GetWorldTransform().position;
}

double Object::GetWorldRotation()
{
	return GetWorldTransform().rotation;
}

const Vector2f Object::GetUpVector()
{
	Vector2f vec = Vector2f::up;
	vec.Rotate(transform.rotation);
	return vec;
}

const Vector2f Object::GetRightVector()
{
	Vector2f vec = Vector2f::right;
	vec.Rotate(transform.rotation);
	return vec;
}

bool Object::IsChild(weak_Object child)
{
	if(!HasChildren()) return false;
	const uint32_t searched = child.lock()->id;
	if (children.find(searched) != children.end()) return true;
	
	return false;
}

Object& Object::SetTransform(Transform t)
{
	transform = t;
	return *this;
}
Object& Object::SetPosition(Vector2i pos)
{
	transform.position = pos;
	return *this;
}
void Object::ClearParent()
{
	parent = weak_Object();
}

void Object::ApplyTransform() {
	transform = GetWorldTransform();
}

bool Object::ClearChildren()
{
	for (auto tpl : children) {
		tpl.second.lock()->SetParent(weak_Object());
	}
	children.clear();
	return children.empty();
}

bool Object::AddChild(weak_Object child) {

	if (IsChild(child)) {
		printf("Can't add child: it is a child already!\n");
		return false;
	}
	children.insert({ child.lock()->id, child });
	return true;
}
bool Object::RemoveChild(weak_Object child) {
	
	const uint32_t id = child.lock()->id;
	if (!IsChild(child)) {
		printf("Can't remove child: Given object is not on a children list!\n");
		return false;
	}
	children.erase(id);
	return true;
}

//bool Object::IsInChildHierarchy(shared_Object obj)
//{
	//if (!this->HasChildren()) return false;
	//for (auto child : children) {
	//	auto tested = child.lock();
	//	if (tested == obj) return true;
	//	if (tested->IsInChildHierarchy(obj)) return true;
	//}
	//return false;
//}

bool Object::IsParentPossible(weak_Object par)
{
	auto parentToCheck = par.lock();
	while (parentToCheck) {
		if (this == parentToCheck.get()) {
			printf("Detected parent - child circural dependency!\n");
			return false;
		}
		parentToCheck = parentToCheck->GetParent().lock();
	}
	return true;
}

void Object::RegisterCollider(std::weak_ptr<Collider> col)
{
	Core::Get().GetPhysicsCore().AddCollider(col);
}

Object& Object::SetParent(weak_Object par, const bool applyPreviousTransform) {
	auto oldParent = parent.lock();
	auto newParent = par.lock();
	
	if (oldParent == newParent) return *this;
	if (oldParent) {
		oldParent->RemoveChild(weak_from_this());
		if (applyPreviousTransform)ApplyTransform();
	}
	if (!newParent) {
		this->ClearParent();
		return *this;
	}
	if (!this->IsParentPossible(newParent)) {
		printf("%s, or one of it's parents, is in %s's children hierarchy!\n", newParent->name.c_str(), this->name.c_str());
		return *this;
	}
	newParent->AddChild(weak_from_this());
	parent = newParent;
	printf("%s set as a parent of %s\n", newParent->name.c_str(), this->name.c_str());
	return *this;
}

bool Object::HasRenderableComponents()
{
	if(!HasComponents()) return false;
	for (auto& tpl : components) {
		if (std::dynamic_pointer_cast<RenderableComponent>(tpl.second)) return true;
	}
	return false;
}

std::vector<RenderableComponent*> Object::GetRenderableComponents()
{
	std::vector<RenderableComponent*> rComps;
	if (!HasRenderableComponents()) return rComps;
	for (auto& tpl : components) {
		auto comp = std::dynamic_pointer_cast<RenderableComponent>(tpl.second);
		if (comp) rComps.push_back(&*comp);
	}
	return rComps;
}

bool Object::HasCollider()
{
	//if (!this->GetComponentOfClass<Collider>(false).expired()) return true;
	return false;
}

bool Object::RemoveComponent(std::type_index compClass)
{
	auto lComp = components[(uint32_t)compClass.hash_code()];
	if (!lComp) {
		printf("No component of class %s!\n", compClass.name());
		return false;
	}
	components[(uint32_t)compClass.hash_code()] = nullptr;
	components.erase((uint32_t)compClass.hash_code());
	return true;
}

void Object::OnBeginOverlap(Collider* col)
{
	printf("%s collided with %s \n", this->name.c_str(), col->GetOwner()->name.c_str());
}

void Object::OnEndOverlap(Collider* col)
{
	if (col)
		printf("%s ended collision with %s \n", this->name.c_str(), col->GetOwner()->name.c_str());
	else
		printf("%s ended collision with destroyed actor \n", this->name.c_str());
}
