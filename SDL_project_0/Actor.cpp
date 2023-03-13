#include "stdafx.h"
#include "Actor.h"
#include "EntityManager.h"

//Actor::Actor(uint32_t iD, std::string n, Transform t, Vector2i s, shared_Texture tex) :
//	RenderObject(iD, n, t, s, tex)
//{}

Actor::Actor() : RenderObject(EntityManager::Get()->GetFreeEntityID(), ((std::string)typeid(this).name()).append("_" + std::to_string(EntityManager::Get()->GetFreeEntityID())), Transform(), Vector2i::zero, nullptr)
{
	Actor::OnSpawn();
}

void Actor::OnSpawn()
{
}

void Actor::Update(double dTime) {
	Object::Update(dTime);
}

Actor& Actor::Translate(Vector2i vector){
	transform.position += vector;
	return *this;
}
Actor& Actor::Rotate(double angle) {
	transform.rotation = fmod((transform.rotation + angle), 360);
	return *this;
}
Actor& Actor::Scale(Vector2f scale) {
	transform.scale *= scale;
	return *this;
}
Actor& Actor::Scale(float scale) {
	transform.scale *= scale;
	return *this;
}

