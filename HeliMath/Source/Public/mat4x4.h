#pragma once 

#include <cmath>
#include <ostream>
#include "math_defines.h"
#include "math_util.h" 
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

// First take on a square 4x4 matrix, later a lot of the calculations 
// such as the matrix multiplication will be optimized 
struct Mat4x4 {
	float m11, m12, m13, m14,
		m21, m22, m23, m24,
		m31, m32, m33, m34,
		m41, m42, m43, m44;

	// Initializes to identity matrix (no transform)
	// The identity matrix is the equivalent of 1 in scalar multiplication
	HELI_FORCE_INLINE Mat4x4()
		: m11(1.0f), m12(0.0f), m13(0.0f), m14(0.0f),
		m21(0.0f), m22(1.0f), m23(0.0f), m24(0.0f),
		m31(0.0f), m32(0.0f), m33(1.0f), m34(0.0f),
		m41(0.0f), m42(0.0f), m43(0.0f), m44(1.0f)
	{

	}

	// Transposing a matrix flips it diagonally 
	// Because we use row major vectors and opengl uses column vectors 
	// We need to transpose the matrices before we send them to the GPU 
	HELI_FORCE_INLINE void transpose() noexcept {
		Mat4x4 r;

		r.m11 = m11; r.m12 = m21; r.m13 = m31; r.m14 = m41;
		r.m21 = m12; r.m22 = m22; r.m23 = m32; r.m24 = m42;
		r.m31 = m13; r.m32 = m23; r.m33 = m33; r.m34 = m43;
		r.m41 = m14; r.m42 = m24; r.m43 = m34; r.m44 = m44;
			
		*this = r;
	}
	
	// Each element is computed as a dot product between a row of 'this'
	// and a column of the other matrix
	HELI_FORCE_INLINE Mat4x4 operator*(const Mat4x4& o) const noexcept
	{
		Mat4x4 r{};
		r.m11 = m11 * o.m11 + m12 * o.m21 + m13 * o.m31 + m14 * o.m41;
		r.m12 = m11 * o.m12 + m12 * o.m22 + m13 * o.m32 + m14 * o.m42;
		r.m13 = m11 * o.m13 + m12 * o.m23 + m13 * o.m33 + m14 * o.m43;
		r.m14 = m11 * o.m14 + m12 * o.m24 + m13 * o.m34 + m14 * o.m44;

		r.m21 = m21 * o.m11 + m22 * o.m21 + m23 * o.m31 + m24 * o.m41;
		r.m22 = m21 * o.m12 + m22 * o.m22 + m23 * o.m32 + m24 * o.m42;
		r.m23 = m21 * o.m13 + m22 * o.m23 + m23 * o.m33 + m24 * o.m43;
		r.m24 = m21 * o.m14 + m22 * o.m24 + m23 * o.m34 + m24 * o.m44;

		r.m31 = m31 * o.m11 + m32 * o.m21 + m33 * o.m31 + m34 * o.m41;
		r.m32 = m31 * o.m12 + m32 * o.m22 + m33 * o.m32 + m34 * o.m42;
		r.m33 = m31 * o.m13 + m32 * o.m23 + m33 * o.m33 + m34 * o.m43;
		r.m34 = m31 * o.m14 + m32 * o.m24 + m33 * o.m34 + m34 * o.m44;

		r.m41 = m41 * o.m11 + m42 * o.m21 + m43 * o.m31 + m44 * o.m41;
		r.m42 = m41 * o.m12 + m42 * o.m22 + m43 * o.m32 + m44 * o.m42;
		r.m43 = m41 * o.m13 + m42 * o.m23 + m43 * o.m33 + m44 * o.m43;
		r.m44 = m41 * o.m14 + m42 * o.m24 + m43 * o.m34 + m44 * o.m44;

		return r;
	}

	// Scalar multiplication 
	HELI_FORCE_INLINE Mat4x4 operator*(const float s) const noexcept
	{
		Mat4x4 r = *this;
		r.m11 *= s; r.m12 *= s; r.m13 *= s; r.m14 *= s;
		r.m21 *= s; r.m22 *= s; r.m23 *= s; r.m24 *= s;
		r.m31 *= s; r.m32 *= s; r.m33 *= s; r.m34 *= s;
		r.m41 *= s; r.m42 *= s; r.m43 *= s; r.m44 *= s;
		return r;
	}

	HELI_FORCE_INLINE bool operator==(const Mat4x4& m) const noexcept
	{
		return
			MathUtil::is_nearly_equal(m11, m.m11) && MathUtil::is_nearly_equal(m12, m.m12) &&
			MathUtil::is_nearly_equal(m13, m.m13) && MathUtil::is_nearly_equal(m14, m.m14) &&

			MathUtil::is_nearly_equal(m21, m.m21) && MathUtil::is_nearly_equal(m22, m.m22) &&
			MathUtil::is_nearly_equal(m23, m.m23) && MathUtil::is_nearly_equal(m24, m.m24) &&

			MathUtil::is_nearly_equal(m31, m.m31) && MathUtil::is_nearly_equal(m32, m.m32) &&
			MathUtil::is_nearly_equal(m33, m.m33) && MathUtil::is_nearly_equal(m34, m.m34) &&

			MathUtil::is_nearly_equal(m41, m.m41) && MathUtil::is_nearly_equal(m42, m.m42) &&
			MathUtil::is_nearly_equal(m43, m.m43) && MathUtil::is_nearly_equal(m44, m.m44);
	}

	HELI_FORCE_INLINE static Mat4x4 create_scale_2d(const Vec2& v) noexcept {
		Mat4x4 r = {};
		r.m11 = v.x;
		r.m22 = v.y;

		return r;
	}

	// uniform and nonuniform scaling
	HELI_FORCE_INLINE static Mat4x4 scale(const Vec3& v) noexcept {
		Mat4x4 r{};
		r.m11 = v.x;
		r.m22 = v.y;
		r.m33 = v.z;
		return r;
	}

	// Counter clockwise rotation = positive, clockwise rotation = negative 
	HELI_FORCE_INLINE static Mat4x4 rotate_2d(const float angle) noexcept {
		float cos_angle = std::cos(angle);
		float sin_angle = std::sin(angle);

		Mat4x4 r{};

		r.m11 = cos_angle; r.m12 = -sin_angle;
		r.m21 = sin_angle; r.m22 = cos_angle;

		return r;
	}

	HELI_FORCE_INLINE static Mat4x4 euler(const Vec3& v) noexcept {
		float cos_x = std::cos(v.x);
		float sin_x = std::sin(v.x);

		float cos_y = std::cos(v.y);
		float sin_y = std::sin(v.y);

		float cos_z = std::cos(v.z);
		float sin_z = std::sin(v.z);

		Mat4x4 r{};

		r.m11 = cos_y * cos_z + sin_y * sin_x * sin_z;
		r.m12 = cos_z * sin_y * sin_x - cos_y * sin_z;
		r.m13 = cos_x * sin_y;

		r.m21 = cos_x * sin_z;
		r.m22 = cos_x * cos_z;
		r.m23 = -sin_x;

		r.m31 = cos_y * sin_x * sin_z - cos_z * sin_y;
		r.m32 = sin_y * sin_z + cos_y * cos_z * sin_x;
		r.m33 = cos_x * cos_y;

		return r;
	}

	// Projects a 3D point onto the axis by zeroing out the other axes   
	// m11(x), m22(y), m33(z) 
	HELI_FORCE_INLINE static Mat4x4 project_x() noexcept {
		Mat4x4 r{};
		r.m22 = 0.0f; 
		r.m33 = 0.0f; 
		return r;
	}
	HELI_FORCE_INLINE static Mat4x4 project_y() noexcept {
		Mat4x4 r{};
		r.m11 = 0.0f;
		r.m33 = 0.0f;
		return r;
	}
	HELI_FORCE_INLINE static Mat4x4 project_z() noexcept {
		Mat4x4 r{};
		r.m11 = 0.0f;
		r.m22 = 0.0f;
		return r;
	}
	HELI_FORCE_INLINE static Mat4x4 project_xy() noexcept {
		Mat4x4 r{};
		r.m33 = 0.0f;
		return r;
	}



	HELI_FORCE_INLINE static Mat4x4 reflect_plane(const Vec3& n) noexcept {
		Mat4x4 r{};	

		r.m11 = 1.0f - 2.0f * n.x * n.x;
		r.m22 = 1.0f - 2.0f * n.y * n.y;
		r.m33 = 1.0f - 2.0f * n.z * n.z;

		r.m12 = -2.0f * n.x * n.y;
		r.m21 = -2.0f * n.y * n.x;

		r.m13 = -2.0f * n.x * n.z;
		r.m31 = -2.0f * n.z * n.x;

		r.m23 = -2.0f * n.y * n.z;
		r.m32 = -2.0f * n.z * n.y;

		return r;
	}

	// reflecting the x axis can be used for optimizing assets 
	// only left side of models can be loaded then we can reflect the right side 
	HELI_FORCE_INLINE static Mat4x4 reflect_x() noexcept {
		Mat4x4 r{};

		r.m11 = -1.0f;
		r.m22 = 1.0f;
		r.m33 = 1.0f;

		return r;
	}
	// reflecting the y axis can be used for water surface reflection but its limited in usage 
	// much more performant than plane reflection though 
	HELI_FORCE_INLINE static Mat4x4 reflect_y() noexcept {
		Mat4x4 r{};
		r.m11 = 1.0f;
		r.m22 = -1.0f;
		r.m33 = 1.0f;
		return r;
	}

	HELI_FORCE_INLINE static Mat4x4 reflect_z() noexcept {
		Mat4x4 r{};
		r.m11 = 1.0f;
		r.m22 = 1.0f;
		r.m33 = -1.0f;
		return r;
	}
};

HELI_FORCE_INLINE Mat4x4 operator*(float s, const Mat4x4& m) noexcept
{
	return m * s;
}

std::ostream& operator<<(std::ostream& out_stream, const Mat4x4& a);