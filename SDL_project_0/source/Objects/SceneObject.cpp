#include "stdafx.h"
#include "SceneObject.h"
#include "Core.h"
#include "Collider.h"
#include "RenderableComponent.h"
#include "PhysicsCore.h"
#include "ObjectManager.h"

SceneObject::SceneObject() :
	transform(Transform()),
	parent(WeakSceneObject()),
	children(std::map<const uint32_t, WeakSceneObject>()),
	core(&Core::Get())
{}

Transform& SceneObject::GetTransform()
{
	return transform;
}
Vector2d& SceneObject::GetLocalPosition()
{
	return transform.position;
}
double SceneObject::GetLocalRotation()
{
	return transform.rotation;
}
Vector2f& SceneObject::GetLocalPivot()
{
	return transform.pivot;
}
Transform SceneObject::GetWorldTransform() //transform probably should be passed by reference but thats problematic
{
	auto lParent = parent.lock();
	if (!lParent) return transform;
	return transform.CombineTransform(lParent->GetWorldTransform());
}

Vector2d SceneObject::GetWorldPosition()
{

	return GetWorldTransform().position;
}

double SceneObject::GetWorldRotation()
{
	return GetWorldTransform().rotation;
}

const Vector2d SceneObject::GetUpVector()
{
	Vector2f vec = Vector2f::up;
	vec.Rotate(transform.rotation);
	return vec;
}

const Vector2d SceneObject::GetRightVector()
{
	Vector2f vec = Vector2f::right;
	vec.Rotate(transform.rotation);
	return vec;
}

bool SceneObject::IsChild(WeakSceneObject child)
{
	if(!HasChildren()) return false;
	const uint32_t searched = child.lock()->id;
	if (children.find(searched) != children.end()) return true;
	
	return false;
}

SceneObject& SceneObject::SetTransform(Transform t)
{
	transform = t;
	return *this;
}
SceneObject& SceneObject::SetPosition(Vector2d pos)
{
	transform.position = pos;
	return *this;
}
void SceneObject::ClearParent()
{
	parent = WeakSceneObject();
}

void SceneObject::ApplyTransform() {
	transform = GetWorldTransform();
}

bool SceneObject::ClearChildren()
{
	for (auto tpl : children) {
		tpl.second.lock()->SetParent(WeakSceneObject());
	}
	children.clear();
	return children.empty();
}

bool SceneObject::AddChild(WeakSceneObject child) {

	if (IsChild(child)) {
		printf("Can't add child: it is a child already!\n");
		return false;
	}
	children.insert({ child.lock()->id, child });
	return true;
}
bool SceneObject::RemoveChild(WeakSceneObject child) {
	
	const uint32_t id = child.lock()->id;
	if (!IsChild(child)) {
		printf("Can't remove child: Given object is not on a children list!\n");
		return false;
	}
	children.erase(id);
	return true;
}

bool SceneObject::IsParentPossible(WeakSceneObject par)
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

void SceneObject::RegisterCollider(std::weak_ptr<Collider> col)
{
	Core::Get().GetPhysicsCore().AddCollider(col);
}

SceneObject& SceneObject::SetParent(WeakSceneObject par, const bool applyPreviousTransform) {
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

bool SceneObject::HasRenderableComponents()
{
	if(!HasComponents()) return false;
	for (auto& tpl : components) {
		if (std::dynamic_pointer_cast<RenderableComponent>(tpl.second)) return true;
	}
	return false;
}

std::vector<RenderableComponent*> SceneObject::GetRenderableComponents()
{
	std::vector<RenderableComponent*> rComps;
	if (!HasRenderableComponents()) return rComps;
	for (auto& tpl : components) {
		auto comp = std::dynamic_pointer_cast<RenderableComponent>(tpl.second);
		if (comp) rComps.push_back(&*comp);
	}
	return rComps;
}

bool SceneObject::HasCollider()
{
	//if (!this->GetComponentOfClass<Collider>(false).expired()) return true;
	return false;
}

bool SceneObject::RemoveComponent(std::type_index compClass)
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

void SceneObject::OnBeginOverlap(Collider* col)
{
	printf("%s collided with %s \n", this->name.c_str(), col->GetOwner()->name.c_str());
}

void SceneObject::OnEndOverlap(Collider* col)
{
	if (col)
		printf("%s ended collision with %s \n", this->name.c_str(), col->GetOwner()->name.c_str());
	else
		printf("%s ended collision with destroyed actor \n", this->name.c_str());
}
