
#ifndef __EFFEKSEER_MAT44F_H__
#define __EFFEKSEER_MAT44F_H__

#include "Effekseer.SIMD4f.h"
#include "Effekseer.Vec3f.h"
#include "Effekseer.Vec4f.h"

namespace Effekseer
{

struct Matrix44;

struct Mat44f
{
	SIMD4f X;
	SIMD4f Y;
	SIMD4f Z;
	SIMD4f W;
	
	Mat44f() = default;
	Mat44f(const Mat44f& rhs) = default;
	Mat44f(float m11, float m12, float m13, float m14,
		   float m21, float m22, float m23, float m24,
		   float m31, float m32, float m33, float m34,
		   float m41, float m42, float m43, float m44);
	Mat44f(const Matrix44& mat);

	bool IsValid() const;

	static const Mat44f Identity;

	static bool Equal(const Mat44f& lhs, const Mat44f& rhs, float epsilon = DefaultEpsilon);
};

inline Mat44f::Mat44f(
	float m11, float m12, float m13, float m14,
	float m21, float m22, float m23, float m24,
	float m31, float m32, float m33, float m34,
	float m41, float m42, float m43, float m44)
	: X(m11, m21, m31, m41)
	, Y(m12, m22, m32, m42)
	, Z(m13, m23, m33, m43)
	, W(m14, m24, m34, m44)
{
}

inline bool operator==(const Mat44f& lhs, const Mat44f& rhs)
{
	return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z && lhs.W == rhs.W;
}

inline bool operator!=(const Mat44f& lhs, const Mat44f& rhs)
{
	return lhs.X != rhs.X && lhs.Y != rhs.Y && lhs.Z != rhs.Z && lhs.W != rhs.W;
}

inline Mat44f operator*(const Mat44f& lhs, const Mat44f& rhs)
{
	Mat44f res;
	res.X = SIMD4f::MulLane<0>(lhs.X, rhs.X);
	res.X = SIMD4f::MulAddLane<1>(res.X, lhs.Y, rhs.X);
	res.X = SIMD4f::MulAddLane<2>(res.X, lhs.Z, rhs.X);
	res.X = SIMD4f::MulAddLane<3>(res.X, lhs.W, rhs.X);

	res.Y = SIMD4f::MulLane<0>(lhs.X, rhs.Y);
	res.Y = SIMD4f::MulAddLane<1>(res.Y, lhs.Y, rhs.Y);
	res.Y = SIMD4f::MulAddLane<2>(res.Y, lhs.Z, rhs.Y);
	res.Y = SIMD4f::MulAddLane<3>(res.Y, lhs.W, rhs.Y);

	res.Z = SIMD4f::MulLane<0>(lhs.X, rhs.Z);
	res.Z = SIMD4f::MulAddLane<1>(res.Z, lhs.Y, rhs.Z);
	res.Z = SIMD4f::MulAddLane<2>(res.Z, lhs.Z, rhs.Z);
	res.Z = SIMD4f::MulAddLane<3>(res.Z, lhs.W, rhs.Z);

	res.W = SIMD4f::MulLane<0>(lhs.X, rhs.W);
	res.W = SIMD4f::MulAddLane<1>(res.W, lhs.Y, rhs.W);
	res.W = SIMD4f::MulAddLane<2>(res.W, lhs.Z, rhs.W);
	res.W = SIMD4f::MulAddLane<3>(res.W, lhs.W, rhs.W);
	return res;
}

inline Vec3f operator*(const Mat44f& lhs, const Vec3f& rhs)
{
	SIMD4f rhs4 = rhs.s;
	rhs4.SetW(1.0f);

	SIMD4f res = SIMD4f::MulLane<0>(lhs.X, rhs4);
	res = SIMD4f::MulAddLane<1>(res, lhs.Y, rhs4);
	res = SIMD4f::MulAddLane<2>(res, lhs.Z, rhs4);
	res = SIMD4f::MulAddLane<3>(res, lhs.W, rhs4);
	return Vec3f{res};
}

inline Vec4f operator*(const Mat44f& lhs, const Vec4f& rhs)
{
	SIMD4f res = SIMD4f::MulLane<0>(lhs.X, rhs.s);
	res = SIMD4f::MulAddLane<1>(res, lhs.Y, rhs.s);
	res = SIMD4f::MulAddLane<2>(res, lhs.Z, rhs.s);
	res = SIMD4f::MulAddLane<3>(res, lhs.W, rhs.s);
	return Vec4f{res};
}

} // namespace Effekseer

#endif // __EFFEKSEER_VEC4F_H__