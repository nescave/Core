#include "stdafx.h"
#include "Actor.h"
#include "ObjectManager.h"

//Actor::Actor(uint32_t iD, std::string n, Transform t, Vector2i s, shared_Texture tex) :
//	RenderObject(iD, n, t, s, tex)
//{}

Actor::Actor() : maxSpeed(5)
{}

void Actor::OnSpawn()
{
	RenderableObject::OnSpawn();
}

void Actor::Update(double dTime) {
	SceneObject::Update(dTime);

	Translate(speed*dTime);
}

void Actor::OnDestroy()
{
	RenderableObject::OnDestroy();
}

Actor& Actor::Translate(Vector2f& vector){
	transform.position += vector;
	return *this;
}

Actor& Actor::Translate(Vector2f&& vector)
{
	return Translate(vector);
}

Actor& Actor::TranslateAbsolute(Vector2f& vector)
{
	return Translate(vector.RotateThis(GetAbsoluteRotation()));
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

Actor& Actor::Accelerate(Vector2f force)
{
	speed+= force.Rotate(GetAbsoluteRotation());
	return *this;
}

Actor& Actor::AccelerateAbsolute(Vector2f force)
{
	speed+= force;
	return *this;
}

Actor& Actor::Stop()
{
	speed = Vector2f::zero; return *this;
}
