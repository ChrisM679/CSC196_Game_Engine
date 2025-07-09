#pragma once
#include "Math.h"
#include <cassert>

namespace viper
{
	template<typename T>
	struct Vector2
	{
		T x, y;

		Vector2() = default;
		Vector2(T x, T y) : x{ x }, y{ y } {}

		T operator [] (unsigned int index) const { assert(index < 2); return (&x)[index]; }
		T& operator [] (unsigned int index) { assert(index < 2); return (&x)[index]; }

		Vector2 operator + (const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
		Vector2 operator - (const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
		Vector2 operator * (const Vector2& v) const { return Vector2(x * v.x, y * v.y); }
		Vector2 operator / (const Vector2& v) const { return Vector2(x / v.x, y / v.y); }

		Vector2 operator + (float s) const { return Vector2(x + s, y + s); }
		Vector2 operator - (float s) const { return Vector2(x - s, y - s); }
		Vector2 operator * (float s) const { return Vector2(x * s, y * s); }
		Vector2 operator / (float s) const { return Vector2(x / s, y / s); }

		Vector2& operator += (const Vector2& v) { x += v.x, y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { x -= v.x, y -= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { x *= v.x, y *= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { x /= v.x, y /= v.y; return *this; }

		Vector2& operator += (float s) { x += s, y += s; return *this; }
		Vector2& operator -= (float s) { x -= s, y -= s; return *this; }
		Vector2& operator *= (float s) { x *= s, y *= s; return *this; }
		Vector2& operator /= (float s) { x /= s, y /= s; return *this; }

		/// <summary>
		/// Calculates the squared length (magnitude) of a 2D vector.
		/// </summary>
		/// <returns>The sum of the squares of the x and y components of the vector.</returns>
		float LengthSqr() const  { return (x * x) + (y * y); }

		/// <summary>
		/// Calculates the length (magnitude) of the vector.
		/// </summary>
		/// <returns>The length of the vector as a floating-point value.</returns>
		float Length() const { return viper::math::sqrtf(LengthSqr()); }
	};

	using ivec2 = Vector2<int>;
	using vec2 = Vector2<float>;
}