#pragma once
#include <math.h>
#include "Random.h"

template<typename T>
struct Vector2
{
	T x;
	T y;

	static const Vector2 zero;
	static const Vector2 one;
	static const Vector2 up;
	static const Vector2 right;

	Vector2() :
		x(T()),
		y(T())
	{}

	Vector2(T X, T Y) :
		x(X),
		y(Y)
	{}
	
	template <typename T2>
	operator Vector2<T2>() { return Vector2<T2>((T2)this->x, (T2)this->y); }
	
	operator SDL_Point() { 
		SDL_Point point;
		point.x = this->x;
		point.y = this->y;
		return  point;
	}
	operator SDL_Point*() {
		return (SDL_Point*)this;
	}
	Vector2 operator+(const Vector2& rVec) const {
		Vector2 vec(this->x + rVec.x, this->y + rVec.y);
		return vec;
	}
	Vector2& operator+=(const Vector2& rVec) {
		this->x += rVec.x;
		this->y += rVec.y;
		return *this;
	}
	Vector2 operator-(const Vector2& rVec) const {
		Vector2 vec(this->x - rVec.x, this->y - rVec.y);
		return vec;
	}
	Vector2 operator-() const {
		Vector2 vec(-this->x, -this->y);
		return vec;
	}
	Vector2& operator-=(const Vector2& rVec) {
		this->x -= rVec.x;
		this->y -= rVec.y;
		return *this;
	}
	Vector2 operator*(double scale) const {
		Vector2 vec(this->x * scale, this->y * scale);
		return vec;
	}
	Vector2& operator*=(const Vector2& rVec) {
		this->x *= rVec.x;
		this->y *= rVec.y;
		return *this;
	}
	template <typename T2>
	Vector2& operator*=(const T2& rV) {
		this->x *= rV;
		this->y *= rV;
		return *this;
	}
	Vector2 operator/(const double scale) const {
		Vector2 vec(this->x / scale, this->y / scale);
		return vec;
	}
	template <typename T2>
	Vector2 operator/(T2 rVec) const {
		Vector2 vec(this->x / rVec.x, this->y / rVec.y);
		return vec;
	}
	template <typename T2>
	Vector2 operator*(const Vector2<T2>& rVec) const {
		Vector2 vec((T)((double)this->x * (double)rVec.x), (T)((double)this->y * (double)rVec.y));
		return vec;
	}
	bool operator==(const Vector2& rVec) const {
		return this->x == rVec.x && this->y == rVec.y;
	}
	bool operator!=(const Vector2& rVec) const {
		return this->x != rVec.x || this->y != rVec.y;
	}
	T LengthSqr() {
		return (T)(pow(this->x, 2) + pow(this->y, 2));
	}
	double Length() {
		return sqrt(this->LengthSqr());
	}
	Vector2 Rotate(double angle) {
		T x = (T)((double)this->x * cos(angle) + (double)this->y * sin(angle));
		T y = (T)((double)this->x * sin(-angle) + (double)this->y * cos(angle));
		return Vector2<T>(x,y);
	}
	static Vector2 Random(T xMin, T xMax, T yMin, T yMax) {
		T x = Random::FromRange(xMin, xMax);
		T y = Random::FromRange(yMin, yMax);
		return Vector2<T>(x, y);
	}
	static double Distance(Vector2 a, Vector2 b) {
		Vector2 c = b - a;
		return c.Length();
	}

};

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;

template<typename T>
const Vector2<T> Vector2<T>::zero = Vector2((T)0, (T)0);
template<typename T>
const Vector2<T> Vector2<T>::one = Vector2((T)1, (T)1);
template<typename T>
const Vector2<T> Vector2<T>::up = Vector2((T)0, (T)-1);
template<typename T>
const Vector2<T> Vector2<T>::right = Vector2((T)1, (T)0);
