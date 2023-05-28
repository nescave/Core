#include "stdafx.h"
#include "Actor.h"

Actor::Actor() : maxSpeed(5)
{}

void Actor::OnSpawn()
{
	RenderableObject::OnSpawn();
	printf("%s spawned \n", name.c_str());
}

void Actor::Update(double dTime) {
	RenderableObject::Update(dTime);

	Translate(speed*dTime); //hehe fyshix brrrr
}

void Actor::OnDestroy()
{
	RenderableObject::OnDestroy();
}

Actor& Actor::Translate(const Vector2f& vector)
{
	transform.position += vector;
	return *this;
}

Actor& Actor::Translate(Vector2f&& vector){
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
