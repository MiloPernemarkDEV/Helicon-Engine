////////////
// Vec2.h //
////////////
#pragma once
#include "core/mathDefines.h"
#include <cmath>
#include <algorithm>
struct Vec2
{
	float x, y;
	constexpr Vec2(float x, float y) : x(x), y(y)
	{
	}
	constexpr Vec2() : x(0), y(0)
	{
	}
	// Special Vec2s
	FORCE_INLINE static Vec2 zero()
	{
		return Vec2(0.0f, 0.0f);
	}
	FORCE_INLINE static Vec2 one()
	{
		return Vec2(1.0f, 1.0f);
	}
	FORCE_INLINE static Vec2 up()
	{
		return Vec2(0.0f, 1.0f);
	}
	FORCE_INLINE static Vec2 down()
	{
		return Vec2(0.0f, -1.0f);
	}
	FORCE_INLINE static Vec2 right()
	{
		return Vec2(1.0f, 0.0f);
	}
	FORCE_INLINE static Vec2 left()
	{
		return Vec2(-1.0f, 0.0f);
	}
	FORCE_INLINE static Vec2 unit()
	{
		return Vec2(0.707107f, 0.707107f);
	}
	FORCE_INLINE constexpr float dot(const Vec2& other) const
	{
		return x * other.x + y * other.y;
	}
	FORCE_INLINE float distanceSquared(const Vec2& other) const
	{
		float distanceX = x - other.x;
		float distanceY = y - other.y;
		return distanceX * distanceX + distanceY * distanceY;
	}
	FORCE_INLINE float distance(const Vec2& other) const
	{
		return std::sqrt(distanceSquared(other));
	}
	FORCE_INLINE float magnitudeSquared() const
	{
		return dot(*this);
	}
	FORCE_INLINE float magnitude() const
	{
		return std::sqrt(magnitudeSquared());
	}
	FORCE_INLINE Vec2 normalize() const
	{
		float m = magnitude();
		if (m <= FLT_EPSILON) return Vec2::zero();
		return Vec2(
			x / m,
			y / m
		);
	}
	FORCE_INLINE bool isNormalized() const
	{
		return isFloatCloseEnough(magnitudeSquared(), 1.0f);
	}
	FORCE_INLINE Vec2 lerp(const Vec2& other, const float& t) const
	{
		float clampedT = std::clamp(t, 0.0f, 1.0f);
		return Vec2(
			x + (clampedT * (other.x - x)),
			y + (clampedT * (other.y - y))
		);
	}
	FORCE_INLINE float theta(const Vec2& other) const
	{
		float magProduct = magnitude() * other.magnitude();
		if (magProduct <= FLT_EPSILON) return 0.0f;

		// Clamp to avoid NaN from precision errors in acos
		float dotProd = dot(other) / magProduct;
		return std::acos(std::clamp(dotProd, -1.0f, 1.0f));
	}
	FORCE_INLINE Vec2 reflection(const Vec2& other) const
	{
		// other is surface normal
		if (std::abs(magnitude()) < FLT_EPSILON || std::abs(other.magnitude()) < FLT_EPSILON) return *this;

		Vec2 n = other.isNormalized() ? other : other.normalize();
		float s = 2.0f * dot(n);
		return *this - (n * s);
	}
	FORCE_INLINE constexpr Vec2 operator+(const Vec2& other) const
	{
		return Vec2(
			x + other.x,
			y + other.y
		);
	}
	FORCE_INLINE constexpr Vec2 operator-(const Vec2& other) const
	{
		return Vec2(
			x - other.x,
			y - other.y
		);
	}
	FORCE_INLINE Vec2 operator-() const
	{
		return Vec2(-x, -y);
	}
	FORCE_INLINE Vec2 operator*(const Vec2& other) const
	{
		return Vec2(
			x * other.x,
			y * other.y
		);
	}
	FORCE_INLINE Vec2 operator*(const float& s) const
	{
		return Vec2(
			x * s,
			y * s
		);
	}
	FORCE_INLINE Vec2 operator/(const float& s) const
	{
		if (std::abs(s) <= FLT_EPSILON) {
			return Vec2::zero();
		}
		float inv = 1.0f / s;
		return Vec2(x * inv, y * inv);
	}
	
	FORCE_INLINE bool operator ==(const Vec2& other) const
	{
		return (isFloatCloseEnough(x, other.x) && isFloatCloseEnough(y, other.y));
	}
	FORCE_INLINE static bool isFloatCloseEnough(float a, float b, float precision = 1e-4f)
	{
		return std::abs(b - a) <= precision;
	}
};
FORCE_INLINE Vec2 operator*(float s, const Vec2& v)
{
	return v * s;
}
