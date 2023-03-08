#include "stdafx.h"
#include "Object.h"
#include "Core.h"
#include "Collider.h"
#include "PhysicsCore.h"

Object::Object(int iD, std::string n, Transform t) :
	Entity(iD, n),
	transform(t),
	parent(weak_Object()),
	children(std::map<const int, weak_Object>())
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
Transform Object::GetUnifiedTransform() //transform probably should be passed by reference but thats problematic
{
	auto lParent = parent.lock();
	if (!lParent) return transform;
	return transform.CombineTransform(lParent->GetUnifiedTransform());
}

Vector2i Object::GetWorldPosition()
{

	return GetUnifiedTransform().position;
}

double Object::GetWorldRotation()
{
	return GetUnifiedTransform().rotation;
}

bool Object::IsChild(weak_Object child)
{
	if(!HasChildren()) return false;
	int searched = child.lock()->id;
	if (children.find(searched) != children.end()) return true;
	
	return false;
}

void Object::ClearParent()
{
	parent = weak_Object();
}

void Object::ApplyTransform() {
	transform = GetUnifiedTransform();
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
	
	const int id = child.lock()->id;
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

bool Object::HasCollider()
{
	//if (!this->GetComponentOfClass<Collider>(false).expired()) return true;
	return false;
}

bool Object::RemoveComponent(std::type_index compClass)
{
	auto lComp = components[compClass.hash_code()];
	if (!lComp) {
		printf("No component of class %s!\n", compClass.name());
		return false;
	}
	components[compClass.hash_code()] = nullptr;
	components.erase(compClass.hash_code());
	return true;
}

void Object::OnBeginOverlap(Collider* col)
{
	printf("%s collided with %s \n", this->name.c_str(), col->owner.lock()->name.c_str());
}

void Object::OnEndOverlap(Collider* col)
{
	if (col)
		printf("%s ended collision with %s \n", this->name.c_str(), col->owner.lock()->name.c_str());
	else
		printf("%s ended collision with nullptr \n", this->name.c_str());
}
