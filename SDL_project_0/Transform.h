#pragma once
#include "Vector2.h"
struct Transform
{
	Vector2i position;
	double rotation;
	Vector2f scale;
	Vector2f pivot = { .5f,.5f }; //only for SDL rotations | probably should move it to RenderObject

	//static const Transform same;

	Transform();
	
	bool operator ==(const Transform& rhT) {
		return rhT.position == this->position && rhT.rotation == this->rotation && rhT.scale == this->scale && rhT.pivot == this->pivot;
	}
	bool operator !=(const Transform& rhT) {
		return rhT.position != this->position || rhT.rotation != this->rotation || rhT.scale != this->scale || rhT.pivot != this->pivot;
	}

	Transform(Vector2i pos, double rot, Vector2f sc, Vector2f piv);
	explicit Transform(Vector2i pos);
	Transform(Vector2i pos, double rot);
	Transform(Vector2i pos, double rot, Vector2f sc);
	Transform(Vector2i pos, Vector2f sc);
	template <typename T>
	const Vector2<T> TransformPosition(Vector2<T>& pos);
	template <typename T>
	const Vector2<T> TransformVector(Vector2<T>& pos);
	Transform CombineTransform(Transform transf);
};

template<typename T>
inline const Vector2<T> Transform::TransformPosition(Vector2<T>& pos)
{
	Vector2<T> newPos = pos.Rotate(this->rotation)* scale + this->position;
	return newPos;
}

template<typename T>
inline const Vector2<T> Transform::TransformVector(Vector2<T>& vec)
{
	Vector2<T> newVec = vec.Rotate(this->rotation) * scale;
	return newVec;
}
