
#ifndef __EFFEKSEER_SIMD4F_SSE_H__
#define __EFFEKSEER_SIMD4F_SSE_H__

#include <emmintrin.h>

namespace Effekseer
{

/**
	@brief	simd class for sse
*/

struct alignas(16) SIMD4f
{
	union {
		__m128 sf;
		__m128i si;
		float f[4];
	};

	SIMD4f() = default;
	SIMD4f(const SIMD4f& rhs) = default;
	SIMD4f(__m128 rhs) { sf = rhs; }
	SIMD4f(float x, float y, float z, float w) { sf = _mm_setr_ps(x, y, z, w); }

	float GetX() const { return f[0]; }
	float GetY() const { return f[1]; }
	float GetZ() const { return f[2]; }
	float GetW() const { return f[3]; }

	void SetX(float o) { f[0] = o; }
	void SetY(float o) { f[1] = o; }
	void SetZ(float o) { f[2] = o; }
	void SetW(float o) { f[3] = o; }
};

inline SIMD4f operator+(const SIMD4f& lhs, const SIMD4f& rhs) { return SIMD4f{_mm_add_ps(lhs.sf, rhs.sf)}; }

inline SIMD4f operator-(const SIMD4f& lhs, const SIMD4f& rhs) { return SIMD4f{_mm_sub_ps(lhs.sf, rhs.sf)}; }

inline SIMD4f operator*(const SIMD4f& lhs, const SIMD4f& rhs) { return SIMD4f{_mm_mul_ps(lhs.sf, rhs.sf)}; }

inline SIMD4f operator*(const SIMD4f& lhs, float rhs) { return SIMD4f{_mm_mul_ps(lhs.sf, _mm_set1_ps(rhs))}; }

inline SIMD4f operator/(const SIMD4f& lhs, const SIMD4f& rhs) { return SIMD4f{_mm_div_ps(lhs.sf, rhs.sf)}; }

inline bool operator==(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret(_mm_cmpeq_ps(lhs.sf, rhs.sf));
	return ret.si.m128i_u64[0] && ret.si.m128i_u64[1];
}

inline bool operator!=(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret(_mm_cmpneq_ps(lhs.sf, rhs.sf));
	return ret.si.m128i_u64[0] && ret.si.m128i_u64[1];
}

inline bool operator<(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret(_mm_cmplt_ps(lhs.sf, rhs.sf));
	return ret.si.m128i_u64[0] && ret.si.m128i_u64[1];
}

inline bool operator<=(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret(_mm_cmple_ps(lhs.sf, rhs.sf));
	return ret.si.m128i_u64[0] && ret.si.m128i_u64[1];
}

inline bool operator>(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret(_mm_cmpgt_ps(lhs.sf, rhs.sf));
	return ret.si.m128i_u64[0] && ret.si.m128i_u64[1];
}

inline bool operator>=(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret(_mm_cmpge_ps(lhs.sf, rhs.sf));
	return ret.si.m128i_u64[0] && ret.si.m128i_u64[1];
}

template<size_t LANE>
inline SIMD4f mul(const SIMD4f& lhs, const SIMD4f& rhs)
{
	return SIMD4f{_mm_mul_ps(lhs.sf, _mm_shuffle_ps(rhs.sf, rhs.sf, 
		(LANE << 6) | (LANE << 4) | (LANE << 2) | LANE))};
}

inline SIMD4f sqrt(const SIMD4f& o) { return SIMD4f{_mm_sqrt_ps(o.sf)}; }

inline SIMD4f rsqrt(const SIMD4f& o) { return SIMD4f{_mm_rsqrt_ps(o.sf)}; }

inline SIMD4f abs(const SIMD4f& o) { return _mm_andnot_ps(_mm_set1_ps(-0.0f), o.sf); }

inline SIMD4f min(const SIMD4f& lhs, const SIMD4f& rhs) { return SIMD4f{_mm_min_ps(lhs.sf, rhs.sf)}; }

inline SIMD4f max(const SIMD4f& lhs, const SIMD4f& rhs) { return SIMD4f{_mm_max_ps(lhs.sf, rhs.sf)}; }

} // namespace Effekseer

#endif // __EFFEKSEER_SIMD4F_SSE_H__