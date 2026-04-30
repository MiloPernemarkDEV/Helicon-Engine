#pragma once 

#include "math_defines.h"
#include <cmath>

namespace MathUtil {
	HELI_FORCE_INLINE static bool is_nearly_equal(float a, float b, float epsilon = 1e-5f)
	{
		return std::abs(a - b) <= epsilon;
	}

    HELI_FORCE_INLINE static Vec3 normalize(const Vec3& v) noexcept
    {
        float length_sq = v.x * v.x + v.y * v.y + v.z * v.z;

        // Avoid division by zero
        if (length_sq <= 0.00001f)
            return Vec3(0.0f, 0.0f, 0.0f);

        float inv_len = 1.0f / std::sqrt(length_sq);

        return Vec3(
            v.x * inv_len,
            v.y * inv_len,
            v.z * inv_len
        );
    }

    HELI_FORCE_INLINE static Vec3 cross(const Vec3& a, const Vec3& b) noexcept
    {
        return Vec3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }

    HELI_FORCE_INLINE static float dot(const Vec3& a, const Vec3& b) noexcept
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
}


