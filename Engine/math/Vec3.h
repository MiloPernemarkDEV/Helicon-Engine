////////////
// Vec3.h //
////////////

#pragma once

#include "core/mathDefines.h"
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

	FORCE_INLINE float magnitude() const
	{
		//return std::sqrt(this->dot(*this));
		return std::sqrt(magnitudeSquared());
	}
	FORCE_INLINE float magnitudeSquared() const
	{
		return (dot(*this));
	}

	FORCE_INLINE Vec3 normalize() const
	{
		if (abs(magnitude()) <= FLT_EPSILON) return Vec3::zero();
		return Vec3(
			x / magnitude(),
			y / magnitude(),
			z / magnitude()
		);
	}

	FORCE_INLINE bool isNormalized() const
	{
		return isFloatCloseEnough(magnitudeSquared(), 1.0f, 0.001f);
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
		// returns the angle in radians between this and other

		// if one of the vectors is zero, then angle has no meaning. return 0?
		if (isFloatCloseEnough(magnitude(), 0.0f, 0.001f) || isFloatCloseEnough(other.magnitude(), 0.0f, 0.001f)) return 0.0f;
		
		if (!isNormalized() || !other.isNormalized()) {
			// already zero-checked above
			float thisinvMag = 1.0f / magnitude();
			float otherInvMag = 1.0f / other.magnitude();
			Vec3 thisN = Vec3(x * thisinvMag, y * thisinvMag, z * thisinvMag);
			Vec3 otherN = Vec3(other.x * otherInvMag, other.y * otherInvMag, other.z * otherInvMag);
			return acos(thisN.dot(otherN));
		}
		else {
			return acos(dot(other));
		}
		
	}

	FORCE_INLINE Vec3 reflection(const Vec3& other) const
	{
		// relfection of zero vector is zero vector
		if (abs(magnitude()) < FLT_EPSILON) return Vec3::zero();
		
		//Formula: reflected = V - 2 * (V · N) * N
		// other is the surface normal -- other must be normalized;
		Vec3 n = other.isNormalized() ? other : other.normalize();
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
		// per component zero checks
		if (abs(other.x) <= FLT_EPSILON || abs(other.y) <= FLT_EPSILON || abs(other.z) <= FLT_EPSILON) return Vec3::zero();
		return Vec3(
			x / other.x,
			y / other.y,
			z / other.z
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

	FORCE_INLINE bool operator ==(const Vec3& other) const
	{
		return isFloatCloseEnough(distanceSquared(other), 0.0f, FLT_EPSILON * FLT_EPSILON);
	}

};

FORCE_INLINE  static bool isFloatCloseEnough(float a, float b, float precision = 1e-4f)
{
	return abs(b-a) <= precision;
}


