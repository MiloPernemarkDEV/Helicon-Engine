////////////
// Vec3.h //
////////////

#pragma once

#include "math_defines.h"
#include <cmath>
#include <algorithm>
#include <cfloat>

struct Vec3 {

	float x, y, z;

	constexpr Vec3(float x, float y, float z)
		: x(x), y(y), z(z)
	{
	}

	constexpr Vec3()
		: x(0), y(0), z(0)
	{
	}

	// SPECIAL Vec3s
	HELI_FORCE_INLINE static Vec3 zero()
	{
		return Vec3(0.0f, 0.0f, 0.0f);
	}
	HELI_FORCE_INLINE static Vec3 one()
	{
		return Vec3(1.0f, 1.0f, 1.0f);
	}
	HELI_FORCE_INLINE static Vec3 up()
	{
		return Vec3(0.0f, 1.0f, 0.0f);
	}
	HELI_FORCE_INLINE static Vec3 down()
	{
		return Vec3(0.0f, -1.0f, 0.0f);
	}
	HELI_FORCE_INLINE static Vec3 right()
	{
		return Vec3(1.0f, 0.0f, 0.0f);
	}
	HELI_FORCE_INLINE static Vec3 left()
	{
		return Vec3(-1.0f, 0.0f, 0.0f);
	}
	HELI_FORCE_INLINE static Vec3 forward()
	{
		return Vec3(0.0f, 0.0f, 1.0f);
	}
	HELI_FORCE_INLINE static Vec3 back()
	{
		return Vec3(0.0f, 0.0f, -1.0f);
	}
	HELI_FORCE_INLINE static Vec3 unit()
	{
		return Vec3(0.57735f, 0.57735f, 0.57735f);
	}

	HELI_FORCE_INLINE constexpr Vec3 cross(const Vec3& other) const
	{
		return Vec3(
			(y * other.z) - (z * other.y),
			(z * other.x) - (x * other.z),
			(x * other.y) - (y * other.x)
		);
	}

	HELI_FORCE_INLINE constexpr float dot(const Vec3& other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	HELI_FORCE_INLINE constexpr float distance_squared(const Vec3& other) const
	{
		float distanceX = x - other.x;
		float distanceY = y - other.y;
		float distanceZ = z - other.z;

		return distanceX * distanceX +
			distanceY * distanceY +
			distanceZ * distanceZ;
	}

	HELI_FORCE_INLINE  float distance(const Vec3& other) const
	{
		return std::sqrt(distance_squared(other));
	}
	HELI_FORCE_INLINE float magnitude_squared() const
	{
		return (dot(*this));
	}
	HELI_FORCE_INLINE float magnitude() const
	{
		return std::sqrt(magnitude_squared());
	}

	HELI_FORCE_INLINE Vec3 normalize() const
	{
		float m = magnitude();
		if (m <= FLT_EPSILON) return Vec3::zero();
		return Vec3(
			x / m,
			y / m,
			z / m
		);
	}

	HELI_FORCE_INLINE bool is_normalized() const
	{
		return is_float_close_enough(magnitude_squared(), 1.0f);
	}

	HELI_FORCE_INLINE Vec3 lerp(const Vec3& other, float t) const
	{
		float clampedT = std::clamp(t, 0.0f, 1.0f);
		return Vec3(
			x + (clampedT * (other.x - x)),
			y + (clampedT * (other.y - y)),
			z + (clampedT * (other.z - z))
		);
	}

	HELI_FORCE_INLINE float theta(const Vec3& other) const
	{
		float magProduct = magnitude() * other.magnitude();
		if (magProduct <= FLT_EPSILON) return 0.0f;
		float dotProd = dot(other) / magProduct;
		return std::acos(std::clamp(dotProd, -1.0f, 1.0f));
	}

	HELI_FORCE_INLINE Vec3 reflect(const Vec3& other) const
	{
		// relfection of zero vector is zero vector
		if (std::abs(magnitude()) < FLT_EPSILON || std::abs(other.magnitude()) < FLT_EPSILON) return *this;
		Vec3 n = other.is_normalized() ? other : other.normalize();
		// Clamp to avoid NaN from precision errors in acos
		float s = 2.0f * dot(n);
		return *this - (n * s);
	}

	HELI_FORCE_INLINE constexpr Vec3 operator+(const Vec3& other) const
	{
		return Vec3(
			x + other.x,
			y + other.y,
			z + other.z
		);
	}


	HELI_FORCE_INLINE constexpr Vec3 operator-(const Vec3& other) const
	{
		return Vec3(
			x - other.x,
			y - other.y,
			z - other.z
		);
	}
	HELI_FORCE_INLINE constexpr Vec3 operator-() const
	{
		return Vec3(-x, -y, -z);
	}


	HELI_FORCE_INLINE Vec3 operator*(const Vec3& other) const
	{
		return Vec3(
			x * other.x,
			y * other.y,
			z * other.z
		);
	}

	HELI_FORCE_INLINE Vec3 operator*(float s) const
	{
		return Vec3(
			x * s,
			y * s,
			z * s
		);
	}

	HELI_FORCE_INLINE Vec3 operator/(float s) const
	{
		if (std::abs(s) <= FLT_EPSILON) return Vec3::zero();
		float inv = 1.0f / s;
		return Vec3(x * inv, y * inv, z * inv);
	}

	HELI_FORCE_INLINE bool operator ==(const Vec3& other) const
	{
		return (is_float_close_enough(x, other.x) && is_float_close_enough(y, other.y) && is_float_close_enough(z, other.z));
	}

	HELI_FORCE_INLINE  static bool is_float_close_enough(float a, float b, float precision = 1e-4f)
	{
		return std::abs(b - a) <= precision;
	}
};

HELI_FORCE_INLINE Vec3 operator*(float s, const Vec3& v)
{
	return v * s;
}