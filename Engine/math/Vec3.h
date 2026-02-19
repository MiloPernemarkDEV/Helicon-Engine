////////////
// Vec3.h //
////////////

#pragma once

// #include "core/MathDefines.h"

#include "core/Defines.h"
#include <cmath>
#include <algorithm>

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
	FORCE_INLINE static Vec3 zero()
	{
		return Vec3(0.0f, 0.0f, 0.0f);
	}
	FORCE_INLINE static Vec3 one()
	{
		return Vec3(1.0f, 1.0f, 1.0f);
	}
	FORCE_INLINE static Vec3 up()
	{
		return Vec3(0.0f, 1.0f, 0.0f);
	}
	FORCE_INLINE static Vec3 down()
	{
		return Vec3(0.0f, -1.0f, 0.0f);
	}
	FORCE_INLINE static Vec3 right()
	{
		return Vec3(1.0f, 0.0f, 0.0f);
	}
	FORCE_INLINE static Vec3 left()
	{
		return Vec3(-1.0f, 0.0f, 0.0f);
	}
	FORCE_INLINE static Vec3 forward()
	{
		return Vec3(0.0f, 0.0f, 1.0f);
	}
	FORCE_INLINE static Vec3 back()
	{
		return Vec3(0.0f, 0.0f, -1.0f);
	}
	FORCE_INLINE static Vec3 unit()
	{
		return Vec3(0.57735f, 0.57735f, 0.57735f);
	}

	FORCE_INLINE constexpr Vec3 cross(const Vec3& other) const
	{
		return Vec3(
			(y * other.z) - (z * other.y),
			(z * other.x) - (x * other.z),
			(x * other.y) - (y * other.x)
		);
	}

	FORCE_INLINE constexpr float dot(const Vec3& other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	FORCE_INLINE constexpr float distanceSquared(const Vec3& other) const
	{
		float distanceX = x - other.x;
		float distanceY = y - other.y;
		float distanceZ = z - other.z;

		return distanceX * distanceX +
			distanceY * distanceY +
			distanceZ * distanceZ;
	}

	FORCE_INLINE  float distance(const Vec3& other) const
	{
		return std::sqrt(distanceSquared(other));
	}
	FORCE_INLINE float magnitudeSquared() const
	{
		return (dot(*this));
	}
	FORCE_INLINE float magnitude() const
	{
		return std::sqrt(magnitudeSquared());
	}

	FORCE_INLINE Vec3 normalize() const
	{
		float m = magnitude();
		if (m <= FLT_EPSILON) return Vec3::zero();
		return Vec3(
			x / m,
			y / m,
			z / m
		);
	}

	FORCE_INLINE bool isNormalized() const
	{
		return isFloatCloseEnough(magnitudeSquared(), 1.0f);
	}

	FORCE_INLINE Vec3 lerp(const Vec3& other, const float& t) const
	{
		float clampedT = std::clamp(t, 0.0f, 1.0f);
		return Vec3(
			x + (clampedT * (other.x - x)),
			y + (clampedT * (other.y - y)),
			z + (clampedT * (other.z - z))
		);
	}

	FORCE_INLINE float theta(const Vec3& other) const
	{
		float magProduct = magnitude() * other.magnitude();
		if (magProduct <= FLT_EPSILON) return 0.0f;
		float dotProd = dot(other) / magProduct;
		return std::acos(std::clamp(dotProd, -1.0f, 1.0f));
	}

	FORCE_INLINE Vec3 reflection(const Vec3& other) const
	{
		// relfection of zero vector is zero vector
		if (std::abs(magnitude()) < FLT_EPSILON || std::abs(other.magnitude()) < FLT_EPSILON) return *this;
		Vec3 n = other.isNormalized() ? other : other.normalize();
		// Clamp to avoid NaN from precision errors in acos
		float s = 2.0f * dot(n);
		return *this - (n * s);
	}

	FORCE_INLINE constexpr Vec3 operator+(const Vec3& other) const
	{
		return Vec3(
			x + other.x,
			y + other.y,
			z + other.z
		);
	}


	FORCE_INLINE constexpr Vec3 operator-(const Vec3& other) const
	{
		return Vec3(
			x - other.x,
			y - other.y,
			z - other.z
		);
	}
	FORCE_INLINE constexpr Vec3 operator-() const
	{
		return Vec3(-x, -y, -z);
	}


	FORCE_INLINE Vec3 operator*(const Vec3& other) const
	{
		return Vec3(
			x * other.x,
			y * other.y,
			z * other.z
		);
	}

	FORCE_INLINE Vec3 operator*(const float& s) const
	{
		return Vec3(
			x * s,
			y * s,
			z * s
		);
	}

	FORCE_INLINE Vec3 operator/(const float& s) const
	{
		if (std::abs(s) <= FLT_EPSILON) return Vec3::zero();
		float inv = 1.0f / s;
		return Vec3(x * inv, y * inv, z * inv);
	}

	FORCE_INLINE bool operator ==(const Vec3& other) const
	{
		return (isFloatCloseEnough(x, other.x) && isFloatCloseEnough(y, other.y) && isFloatCloseEnough(z, other.z));
	}

	FORCE_INLINE  static bool isFloatCloseEnough(float a, float b, float precision = 1e-4f)
	{
		return std::abs(b - a) <= precision;
	}
};
FORCE_INLINE Vec3 operator*(const float& s, const Vec3& v)
{
	return v * s;
}