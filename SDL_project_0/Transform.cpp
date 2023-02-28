#include "stdafx.h"
#include "Transform.h"

Transform::Transform(Vector2i pos, double rot, Vector2f sc, Vector2f piv) :
	position(pos),
	rotation(rot),
	scale(sc),
	pivot(piv)
{}
Transform::Transform(Vector2i pos, double rot, Vector2f sc) : 
	position(pos),
	rotation(rot),
	scale(sc) 
{}
Transform::Transform() : Transform(Vector2i::zero, 0, Vector2f::one)
{}
Transform::Transform(Vector2i pos) :Transform(pos, 0, Vector2f::one)
{}
Transform::Transform(Vector2i pos, double rot) : Transform(pos, rot, Vector2f::one)
{}
Transform::Transform(Vector2i pos, Vector2f sc) : Transform(pos, 0, sc)
{}

Transform Transform::CombineTransform(Transform transf)
{
	Transform newTransform = Transform();
	newTransform.position = transf.TransformPosition(this->position);
	newTransform.rotation = fmod(this->rotation + transf.rotation, 360.0);
	newTransform.scale = this->scale * transf.scale;
	return newTransform;
}
