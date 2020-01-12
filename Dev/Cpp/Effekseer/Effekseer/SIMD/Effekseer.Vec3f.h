
#ifndef __EFFEKSEER_VEC3F_H__
#define __EFFEKSEER_VEC3F_H__

#include "Effekseer.SIMD4f.h"
#include "../Effekseer.Math.h"

namespace Effekseer
{

struct Vector3D;
struct vector3d;

struct Vec3f
{
	SIMD4f s;

	explicit Vec3f() = default;
	Vec3f(const Vec3f& vec) = default;
	Vec3f(float x, float y, float z): s(x, y, z, 1.0f) {}
	Vec3f(const SIMD4f& vec): s(vec) {}
	Vec3f(const Vector3D& vec);
	Vec3f(const vector3d& vec);

	float GetX() const { return s.GetX(); }
	float GetY() const { return s.GetY(); }
	float GetZ() const { return s.GetZ(); }

	void SetX(float o) { s.SetX(o); }
	void SetY(float o) { s.SetY(o); }
	void SetZ(float o) { s.SetZ(o); }

	Vec3f& operator+=(const Vec3f& o) { s += o.s; return *this; }
	Vec3f& operator-=(const Vec3f& o) { s -= o.s; return *this; }
	Vec3f& operator*=(const Vec3f& o) { s *= o.s; return *this; }
	Vec3f& operator*=(float o) { s *= o; return *this; }
	Vec3f& operator/=(const Vec3f& o) { s /= o.s; return *this; }
	Vec3f& operator/=(float o) { s /= o; return *this; }

	float GetSquaredLength() const;
	float GetLength() const;
	bool IsZero(float epsiron = DefaultEpsilon) const;
	Vec3f Normalize() const;

	static Vec3f Sqrt(const Vec3f& i);
	static Vec3f Rsqrt(const Vec3f& i);
	static Vec3f Abs(const Vec3f& i);
	static Vec3f Min(const Vec3f& lhs, const Vec3f& rhs);
	static Vec3f Max(const Vec3f& lhs, const Vec3f& rhs);
	static float Dot(const Vec3f& lhs, const Vec3f& rhs);
	static Vec3f Cross(const Vec3f& lhs, const Vec3f& rhs);
	static bool Equal(const Vec3f& lhs, const Vec3f& rhs, float epsilon = DefaultEpsilon);
};

inline Vec3f operator+(const Vec3f& lhs, const Vec3f& rhs)
{
	return Vec3f{lhs.s + rhs.s};
}

inline Vec3f operator-(const Vec3f& lhs, const Vec3f& rhs)
{
	return Vec3f{lhs.s - rhs.s};
}

inline Vec3f operator*(const Vec3f& lhs, const Vec3f& rhs)
{
	return Vec3f{lhs.s * rhs.s};
}

inline Vec3f operator*(const Vec3f& lhs, float rhs)
{
	return Vec3f{lhs.s * rhs};
}

inline Vec3f operator/(const Vec3f& lhs, const Vec3f& rhs)
{
	return Vec3f{lhs.s / rhs.s};
}

inline Vec3f operator/(const Vec3f& lhs, float rhs)
{
	return Vec3f{lhs.s / rhs};
}

inline bool operator==(const Vec3f& lhs, const Vec3f& rhs)
{
	return (SIMD4f::ToComparedMask(SIMD4f::Equal(lhs.s, rhs.s)) & 0x07) == 0x7;
}

inline bool operator!=(const Vec3f& lhs, const Vec3f& rhs)
{
	return (SIMD4f::ToComparedMask(SIMD4f::Equal(lhs.s, rhs.s)) & 0x07) != 0x7;
}

inline Vec3f Vec3f::Sqrt(const Vec3f& i)
{
	return Vec3f{SIMD4f::Sqrt(i.s)};
}

inline Vec3f Vec3f::Rsqrt(const Vec3f& i)
{
	return Vec3f{SIMD4f::Rsqrt(i.s)};
}

inline Vec3f Vec3f::Abs(const Vec3f& i)
{
	return Vec3f{SIMD4f::Abs(i.s)};
}

inline Vec3f Vec3f::Min(const Vec3f& lhs, const Vec3f& rhs)
{
	return Vec3f{SIMD4f::Min(lhs.s, rhs.s)};
}

inline Vec3f Vec3f::Max(const Vec3f& lhs, const Vec3f& rhs)
{
	return Vec3f{SIMD4f::Max(lhs.s, rhs.s)};
}

inline float Vec3f::Dot(const Vec3f& lhs, const Vec3f& rhs)
{
	Vec3f muled = lhs * rhs;
	return muled.GetX() + muled.GetY() + muled.GetZ();
}

inline Vec3f Vec3f::Cross(const Vec3f& lhs, const Vec3f& rhs)
{
	return SIMD4f::Swizzle<1,2,0,3>(lhs.s) * SIMD4f::Swizzle<2,0,1,3>(rhs.s) -
		   SIMD4f::Swizzle<2,0,1,3>(lhs.s) * SIMD4f::Swizzle<1,2,0,3>(rhs.s);
}

inline bool Vec3f::Equal(const Vec3f& lhs, const Vec3f& rhs, float epsilon)
{
	return (SIMD4f::ToComparedMask(SIMD4f::NearEqual(lhs.s, rhs.s, epsilon)) & 0x7) == 0x7;
}

inline float Vec3f::GetSquaredLength() const
{
	auto o = s * s;
	return o.GetX() + o.GetY() + o.GetZ();
}

inline float Vec3f::GetLength() const
{
	return Effekseer::Sqrt(GetSquaredLength());
}

inline bool Vec3f::IsZero(float epsiron) const
{
	return (SIMD4f::ToComparedMask(SIMD4f::IsZero(epsiron)) & 0x7) != 0;
}

inline Vec3f Vec3f::Normalize() const
{
	return *this * Effekseer::Rsqrt(GetSquaredLength());
}

} // namespace Effekseer

#endif // __EFFEKSEER_VEC3F_H__