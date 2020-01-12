
#ifndef __EFFEKSEER_MAT43F_H__
#define __EFFEKSEER_MAT43F_H__

#include "Effekseer.SIMD4f.h"
#include "Effekseer.Vec3f.h"
#include "Effekseer.Vec4f.h"

namespace Effekseer
{

struct Matrix43;

struct Mat43f
{
	SIMD4f X;
	SIMD4f Y;
	SIMD4f Z;

	Mat43f() = default;
	Mat43f(const Mat43f& rhs) = default;
	Mat43f(float m11, float m12, float m13,
		   float m21, float m22, float m23,
		   float m31, float m32, float m33,
		   float m41, float m42, float m43);
	Mat43f(const Matrix43& mat);

	bool IsValid() const;

	Vec3f GetScale() const;

	Mat43f GetRotation() const;

	Vec3f GetTranslation() const;

	void GetSRT(Vec3f& s, Mat43f& r, Vec3f& t) const;

	void operator*=(const Mat43f& rhs);

	static const Mat43f Identity;

	static bool Equal(const Mat43f& lhs, const Mat43f& rhs, float epsilon = DefaultEpsilon);

	static Mat43f SRT(const Vec3f& s, const Mat43f& r, const Vec3f& t);

	static Mat43f Scaling(float x, float y, float z);

	static Mat43f Scaling(const Vec3f& scale);

	static Mat43f RotationX(float angle);

	static Mat43f RotationY(float angle);

	static Mat43f RotationZ(float angle);

	static Mat43f RotationXYZ(float rx, float ry, float rz);

	static Mat43f RotationZXY(float rz, float rx, float ry);

	static Mat43f RotationAxis(const Vec3f& axis, float angle);

	static Mat43f RotationAxis(const Vec3f& axis, float s, float c);

	static Mat43f Translation(float x, float y, float z);

	static Mat43f Translation(const Vec3f& pos);
};

inline Mat43f::Mat43f(
	float m11, float m12, float m13,
	float m21, float m22, float m23,
	float m31, float m32, float m33,
	float m41, float m42, float m43)
	: X(m11, m21, m31, m41)
	, Y(m12, m22, m32, m42)
	, Z(m13, m23, m33, m43)
{
}

inline bool operator==(const Mat43f& lhs, const Mat43f& rhs)
{
	return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z;
}

inline bool operator!=(const Mat43f& lhs, const Mat43f& rhs)
{
	return lhs.X != rhs.X && lhs.Y != rhs.Y && lhs.Z != rhs.Z;
}

inline Mat43f operator*(const Mat43f& lhs, const Mat43f& rhs)
{
	const SIMD4f mask = SIMD4f::SetUInt(0, 0, 0, 0xffffffff);

	Mat43f res;
	res.X = mask & rhs.X;
	res.X = SIMD4f::MulAddLane<0>(res.X, lhs.X, rhs.X);
	res.X = SIMD4f::MulAddLane<1>(res.X, lhs.Y, rhs.X);
	res.X = SIMD4f::MulAddLane<2>(res.X, lhs.Z, rhs.X);

	res.Y = mask & rhs.Y;
	res.Y = SIMD4f::MulAddLane<0>(res.Y, lhs.X, rhs.Y);
	res.Y = SIMD4f::MulAddLane<1>(res.Y, lhs.Y, rhs.Y);
	res.Y = SIMD4f::MulAddLane<2>(res.Y, lhs.Z, rhs.Y);

	res.Z = mask & rhs.Z;
	res.Z = SIMD4f::MulAddLane<0>(res.Z, lhs.X, rhs.Z);
	res.Z = SIMD4f::MulAddLane<1>(res.Z, lhs.Y, rhs.Z);
	res.Z = SIMD4f::MulAddLane<2>(res.Z, lhs.Z, rhs.Z);
	return res;
}

inline Vec3f operator*(const Mat43f& lhs, const Vec3f& rhs)
{
	SIMD4f rhs4 = rhs.s;
	rhs4.SetW(1.0f);

	SIMD4f res = SIMD4f::MulLane<0>(lhs.X, rhs4);
	res = SIMD4f::MulAddLane<1>(res, lhs.Y, rhs4);
	res = SIMD4f::MulAddLane<2>(res, lhs.Z, rhs4);
	return Vec3f{res};
}

inline Vec4f operator*(const Mat43f& lhs, const Vec4f& rhs)
{
	SIMD4f res = SIMD4f::MulLane<0>(lhs.X, rhs.s);
	res = SIMD4f::MulAddLane<1>(res, lhs.Y, rhs.s);
	res = SIMD4f::MulAddLane<2>(res, lhs.Z, rhs.s);
	return Vec4f{res};
}

inline void Mat43f::operator*=(const Mat43f& rhs)
{
	*this = *this * rhs;
}

} // namespace Effekseer

#endif // __EFFEKSEER_MAT43F_H__