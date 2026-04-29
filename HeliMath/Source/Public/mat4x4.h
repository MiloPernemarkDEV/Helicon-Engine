#pragma once 

#include "math_defines.h"
#include "vec3.h"
#include <cmath>
#include <ostream>

// standard 4x4 Square matrix, will look at a simd optimized version later 
struct Mat4x4 {
	// OpenGl uses column major m[column][row] 
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
	HELI_FORCE_INLINE void transpose() {
		Mat4x4 r{};

		r.m11 = m11; r.m12 = m21; r.m13 = m31; r.m14 = m41;
		r.m21 = m12; r.m22 = m22; r.m23 = m32; r.m24 = m42;
		r.m31 = m13; r.m32 = m23; r.m33 = m33; r.m34 = m43;
		r.m41 = m14; r.m42 = m24; r.m43 = m34; r.m44 = m44;
			
		*this = r;
	}

	HELI_FORCE_INLINE Mat4x4 operator*(const Mat4x4& other) {

	}

	// Scalar multiplication 
	HELI_FORCE_INLINE Mat4x4 operator*(float s) const
	{
		Mat4x4 r = *this;
		r.m11 *= s; r.m12 *= s; r.m13 *= s; r.m14 *= s;
		r.m21 *= s; r.m22 *= s; r.m23 *= s; r.m24 *= s;
		r.m31 *= s; r.m32 *= s; r.m33 *= s; r.m34 *= s;
		r.m41 *= s; r.m42 *= s; r.m43 *= s; r.m44 *= s;
		return r;
	}

	HELI_FORCE_INLINE bool operator==(const Mat4x4& o) const
	{
		return
			fclose_enough(m11, o.m11) && fclose_enough(m12, o.m12) &&
			fclose_enough(m13, o.m13) && fclose_enough(m14, o.m14) &&

			fclose_enough(m21, o.m21) && fclose_enough(m22, o.m22) &&
			fclose_enough(m23, o.m23) && fclose_enough(m24, o.m24) &&

			fclose_enough(m31, o.m31) && fclose_enough(m32, o.m32) &&
			fclose_enough(m33, o.m33) && fclose_enough(m34, o.m34) &&

			fclose_enough(m41, o.m41) && fclose_enough(m42, o.m42) &&
			fclose_enough(m43, o.m43) && fclose_enough(m44, o.m44);
	}
};

HELI_FORCE_INLINE bool fclose_enough(float a, float b, float eps = 0.00001f)
{
	return std::fabs(a - b) < eps;
}

HELI_FORCE_INLINE Mat4x4 operator*(float s, const Mat4x4& m)
{
	return m * s;
}

std::ostream& operator<<(std::ostream& out_stream, const Mat4x4& a);
	