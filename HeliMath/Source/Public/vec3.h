////////////
// Vec3.h //
////////////

#pragma once

#include "math_defines.h"
#include <cmath>
#include <algorithm>
#include <cfloat>

struct vec3 {

	float x, y, z;

	constexpr vec3(float x, float y, float z)
		: x(x), y(y), z(z)
	{
	}

	constexpr vec3()
		: x(0), y(0), z(0)
	{
	}

	// SPECIAL Vec3s
	FORCE_INLINE static vec3 zero()
	{
		return vec3(0.0f, 0.0f, 0.0f);
	}
	FORCE_INLINE static vec3 one()
	{
		return vec3(1.0f, 1.0f, 1.0f);
	}
	FORCE_INLINE static vec3 up()
	{
		return vec3(0.0f, 1.0f, 0.0f);
	}
	FORCE_INLINE static vec3 down()
	{
		return vec3(0.0f, -1.0f, 0.0f);
	}
	FORCE_INLINE static vec3 right()
	{
		return vec3(1.0f, 0.0f, 0.0f);
	}
	FORCE_INLINE static vec3 left()
	{
		return vec3(-1.0f, 0.0f, 0.0f);
	}
	FORCE_INLINE static vec3 forward()
	{
		return vec3(0.0f, 0.0f, 1.0f);
	}
	FORCE_INLINE static vec3 back()
	{
		return vec3(0.0f, 0.0f, -1.0f);
	}
	FORCE_INLINE static vec3 unit()
	{
		return vec3(0.57735f, 0.57735f, 0.57735f);
	}

	FORCE_INLINE constexpr vec3 cross(const vec3& other) const
	{
		return vec3(
			(y * other.z) - (z * other.y),
			(z * other.x) - (x * other.z),
			(x * other.y) - (y * other.x)
		);
	}

	FORCE_INLINE constexpr float dot(const vec3& other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	FORCE_INLINE constexpr float distanceSquared(const vec3& other) const
	{
		float distanceX = x - other.x;
		float distanceY = y - other.y;
		float distanceZ = z - other.z;

		return distanceX * distanceX +
			distanceY * distanceY +
			distanceZ * distanceZ;
	}

	FORCE_INLINE  float distance(const vec3& other) const
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

	FORCE_INLINE vec3 normalize() const
	{
		float m = magnitude();
		if (m <= FLT_EPSILON) return vec3::zero();
		return vec3(
			x / m,
			y / m,
			z / m
		);
	}

	FORCE_INLINE bool isNormalized() const
	{
		return isFloatCloseEnough(magnitudeSquared(), 1.0f);
	}

	FORCE_INLINE vec3 lerp(const vec3& other, float t) const
	{
		float clampedT = std::clamp(t, 0.0f, 1.0f);
		return vec3(
			x + (clampedT * (other.x - x)),
			y + (clampedT * (other.y - y)),
			z + (clampedT * (other.z - z))
		);
	}

	FORCE_INLINE float theta(const vec3& other) const
	{
		float magProduct = magnitude() * other.magnitude();
		if (magProduct <= FLT_EPSILON) return 0.0f;
		float dotProd = dot(other) / magProduct;
		return std::acos(std::clamp(dotProd, -1.0f, 1.0f));
	}

	FORCE_INLINE vec3 reflect(const vec3& other) const
	{
		// relfection of zero vector is zero vector
		if (std::abs(magnitude()) < FLT_EPSILON || std::abs(other.magnitude()) < FLT_EPSILON) return *this;
		vec3 n = other.isNormalized() ? other : other.normalize();
		// Clamp to avoid NaN from precision errors in acos
		float s = 2.0f * dot(n);
		return *this - (n * s);
	}

	FORCE_INLINE constexpr vec3 operator+(const vec3& other) const
	{
		return vec3(
			x + other.x,
			y + other.y,
			z + other.z
		);
	}


	FORCE_INLINE constexpr vec3 operator-(const vec3& other) const
	{
		return vec3(
			x - other.x,
			y - other.y,
			z - other.z
		);
	}
	FORCE_INLINE constexpr vec3 operator-() const
	{
		return vec3(-x, -y, -z);
	}


	FORCE_INLINE vec3 operator*(const vec3& other) const
	{
		return vec3(
			x * other.x,
			y * other.y,
			z * other.z
		);
	}

	FORCE_INLINE vec3 operator*(float s) const
	{
		return vec3(
			x * s,
			y * s,
			z * s
		);
	}

	FORCE_INLINE vec3 operator/(float s) const
	{
		if (std::abs(s) <= FLT_EPSILON) return vec3::zero();
		float inv = 1.0f / s;
		return vec3(x * inv, y * inv, z * inv);
	}

	FORCE_INLINE bool operator ==(const vec3& other) const
	{
		return (isFloatCloseEnough(x, other.x) && isFloatCloseEnough(y, other.y) && isFloatCloseEnough(z, other.z));
	}

	FORCE_INLINE  static bool isFloatCloseEnough(float a, float b, float precision = 1e-4f)
	{
		return std::abs(b - a) <= precision;
	}
};

FORCE_INLINE vec3 operator*(float s, const vec3& v)
{
	return v * s;
}