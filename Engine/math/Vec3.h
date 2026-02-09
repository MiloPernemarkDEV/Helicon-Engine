#pragma once

#include "../macroIncludes.h"
#include <cmath>

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

	FORCE_INLINE float magnitude() const
	{
		return std::sqrt(this->dot(*this));
	}

	FORCE_INLINE Vec3 normalize(const Vec3& other) const
	{

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


	FORCE_INLINE Vec3 operator*(const Vec3& other) const
	{
		return Vec3(
			x * other.x,
			y * other.y,
			z * other.z
		);
	}

	FORCE_INLINE constexpr Vec3 operator/(const Vec3& other) const
	{
		return Vec3(
			x / other.x,
			y / other.y,
			z / other.z
		);
	}
};







