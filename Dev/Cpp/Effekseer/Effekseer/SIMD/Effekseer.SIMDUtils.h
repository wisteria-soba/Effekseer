
#ifndef __EFFEKSEER_SIMD_UTILS_H__
#define __EFFEKSEER_SIMD_UTILS_H__

#include "../Effekseer.Vector2D.h"
#include "../Effekseer.Vector3D.h"
#include "../Effekseer.Matrix43.h"
#include "../Effekseer.Matrix44.h"
#include "Effekseer.Vec2f.h"
#include "Effekseer.Vec3f.h"
#include "Effekseer.Mat43f.h"
#include "Effekseer.Mat44f.h"

namespace Effekseer
{
	
template <size_t align>
class AlignedAllocationPolicy {
public:
	static void* operator new(size_t size) {
#ifdef _MSC_VER
		return _mm_malloc(size, align);
#else
		return memalign(align, size);
#endif
	}
	static void operator delete(void* ptr) {
#ifdef _MSC_VER
		_mm_free(ptr);
#else
		return free(ptr);
#endif
	}
};

inline Vector2D ToStruct(const Vec2f& o)
{
	Vector2D ret;
	Vec2f::Store(&ret, o);
	return ret;
}

inline Vector3D ToStruct(const Vec3f& o)
{
	Vector3D ret;
	Vec3f::Store(&ret, o);
	return ret;
}

inline Matrix43 ToStruct(const Mat43f& o)
{
	Matrix43 ret;

	ret.Value[0][0] = o.X.GetX();
	ret.Value[0][1] = o.Y.GetX();
	ret.Value[0][2] = o.Z.GetX();

	ret.Value[1][0] = o.X.GetY();
	ret.Value[1][1] = o.Y.GetY();
	ret.Value[1][2] = o.Z.GetY();

	ret.Value[2][0] = o.X.GetZ();
	ret.Value[2][1] = o.Y.GetZ();
	ret.Value[2][2] = o.Z.GetZ();

	ret.Value[3][0] = o.X.GetW();
	ret.Value[3][1] = o.Y.GetW();
	ret.Value[3][2] = o.Z.GetW();

	return ret;
}

inline Matrix44 ToStruct(const Mat44f& o)
{
	Matrix44 ret;

	ret.Values[0][0] = o.X.GetX();
	ret.Values[0][1] = o.Y.GetX();
	ret.Values[0][2] = o.Z.GetX();
	ret.Values[0][3] = o.W.GetX();

	ret.Values[1][0] = o.X.GetY();
	ret.Values[1][1] = o.Y.GetY();
	ret.Values[1][2] = o.Z.GetY();
	ret.Values[1][3] = o.W.GetY();

	ret.Values[2][0] = o.X.GetZ();
	ret.Values[2][1] = o.Y.GetZ();
	ret.Values[2][2] = o.Z.GetZ();
	ret.Values[2][3] = o.W.GetZ();

	ret.Values[3][0] = o.X.GetW();
	ret.Values[3][1] = o.Y.GetW();
	ret.Values[3][2] = o.Z.GetW();
	ret.Values[3][3] = o.W.GetW();

	return ret;
}

} // namespace Effekseer

#endif
