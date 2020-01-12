
#ifndef __EFFEKSEER_SIMD4F_SSE_H__
#define __EFFEKSEER_SIMD4F_SSE_H__

#include <stdint.h>
#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#endif
#include "../Effekseer.Math.h"

namespace Effekseer
{

inline float Sqrt(float x)
{
	_mm_store_ss(&x, _mm_sqrt_ss(_mm_load_ss(&x)));
	return x;
}
inline float Rsqrt(float x)
{
	_mm_store_ss(&x, _mm_rsqrt_ss(_mm_load_ss(&x)));
	return x;
}

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
	SIMD4f(__m128i rhs) { si = rhs; }
	SIMD4f(float x, float y, float z, float w) { sf = _mm_setr_ps(x, y, z, w); }
	SIMD4f(float i) { sf = _mm_set_ps1(i); }

	float GetX() const { return f[0]; }
	float GetY() const { return f[1]; }
	float GetZ() const { return f[2]; }
	float GetW() const { return f[3]; }

	void SetX(float i) { f[0] = i; }
	void SetY(float i) { f[1] = i; }
	void SetZ(float i) { f[2] = i; }
	void SetW(float i) { f[3] = i; }

	SIMD4f& operator+=(const SIMD4f& rhs) { sf = _mm_add_ps(sf, rhs.sf); return *this; }
	SIMD4f& operator-=(const SIMD4f& rhs) { sf = _mm_sub_ps(sf, rhs.sf); return *this; }
	SIMD4f& operator*=(const SIMD4f& rhs) { sf = _mm_mul_ps(sf, rhs.sf); return *this; }
	SIMD4f& operator*=(float rhs) { sf = _mm_mul_ps(sf, _mm_set1_ps(rhs)); return *this; }
	SIMD4f& operator/=(const SIMD4f& rhs) { sf = _mm_div_ps(sf, rhs.sf); return *this; }
	SIMD4f& operator/=(float rhs) { sf = _mm_div_ps(sf, _mm_set1_ps(rhs)); return *this; }

	static SIMD4f SetInt(int32_t x, int32_t y, int32_t z, int32_t w);
	static SIMD4f SetUInt(uint32_t x, uint32_t y, uint32_t z, uint32_t w);
	static SIMD4f Sqrt(const SIMD4f& in);
	static SIMD4f Rsqrt(const SIMD4f& in);
	static SIMD4f Abs(const SIMD4f& in);
	static SIMD4f Min(const SIMD4f& lhs, const SIMD4f& rhs);
	static SIMD4f Max(const SIMD4f& lhs, const SIMD4f& rhs);
	static SIMD4f MulAdd(const SIMD4f& a, const SIMD4f& b, const SIMD4f& c);
	static SIMD4f MulSub(const SIMD4f& a, const SIMD4f& b, const SIMD4f& c);

	template<size_t LANE>
	static SIMD4f MulLane(const SIMD4f& lhs, const SIMD4f& rhs)
	{
		static_assert(LANE < 4, "LANE is must be less than 4.");
		return SIMD4f{_mm_mul_ps(lhs.sf, _mm_shuffle_ps(rhs.sf, rhs.sf, _MM_SHUFFLE(LANE, LANE, LANE, LANE)))};
	}

	template<size_t LANE>
	static SIMD4f MulAddLane(const SIMD4f& a, const SIMD4f& b, const SIMD4f& c)
	{
		static_assert(LANE < 4, "LANE is must be less than 4.");
#ifdef __AVX2__
		return SIMD4f{_mm_fmadd_ps(b.sf, _mm_shuffle_ps(c.sf, c.sf, _MM_SHUFFLE(LANE, LANE, LANE, LANE)), a.sf)};
#else
		return SIMD4f{_mm_add_ps(a.sf, _mm_mul_ps(b.sf, _mm_shuffle_ps(c.sf, c.sf, _MM_SHUFFLE(LANE, LANE, LANE, LANE))))};
#endif
	}

	template<size_t LANE>
	static SIMD4f MulSubLane(const SIMD4f& a, const SIMD4f& b, const SIMD4f& c)
	{
		static_assert(LANE < 4, "LANE is must be less than 4.");
#ifdef __AVX2__
		return SIMD4f{_mm_fnmadd_ps(b.sf, _mm_shuffle_ps(c.sf, c.sf, _MM_SHUFFLE(LANE, LANE, LANE, LANE)), a.sf)};
#else
		return SIMD4f{_mm_sub_ps(a.sf, _mm_mul_ps(b.sf, _mm_shuffle_ps(c.sf, c.sf, _MM_SHUFFLE(LANE, LANE, LANE, LANE))))};
#endif
	}

	template <uint32_t indexX, uint32_t indexY, uint32_t indexZ, uint32_t indexW>
	static SIMD4f Swizzle(const SIMD4f& v)
	{
		static_assert(indexX < 4, "indexX is must be less than 4.");
		static_assert(indexY < 4, "indexY is must be less than 4.");
		static_assert(indexZ < 4, "indexZ is must be less than 4.");
		static_assert(indexW < 4, "indexW is must be less than 4.");
		return SIMD4f{_mm_shuffle_ps(v.sf, v.sf, _MM_SHUFFLE(indexW, indexZ, indexY, indexX))};
	}

	static uint32_t ToComparedMask(const SIMD4f& in);
	static SIMD4f Equal(const SIMD4f& lhs, const SIMD4f& rhs);
	static SIMD4f NotEqual(const SIMD4f& lhs, const SIMD4f& rhs);
	static SIMD4f LessThan(const SIMD4f& lhs, const SIMD4f& rhs);
	static SIMD4f LessEqual(const SIMD4f& lhs, const SIMD4f& rhs);
	static SIMD4f GreaterThan(const SIMD4f& lhs, const SIMD4f& rhs);
	static SIMD4f GreaterEqual(const SIMD4f& lhs, const SIMD4f& rhs);
	static SIMD4f NearEqual(const SIMD4f& lhs, const SIMD4f& rhs, float epsilon = DefaultEpsilon);
	static SIMD4f IsZero(const SIMD4f& in, float epsilon = DefaultEpsilon);
};

inline SIMD4f operator+(const SIMD4f& lhs, const SIMD4f& rhs)
{
	return SIMD4f{_mm_add_ps(lhs.sf, rhs.sf)};
}

inline SIMD4f operator-(const SIMD4f& lhs, const SIMD4f& rhs)
{
	return SIMD4f{_mm_sub_ps(lhs.sf, rhs.sf)};
}

inline SIMD4f operator*(const SIMD4f& lhs, const SIMD4f& rhs)
{
	return SIMD4f{_mm_mul_ps(lhs.sf, rhs.sf)};
}

inline SIMD4f operator*(const SIMD4f& lhs, float rhs)
{
	return SIMD4f{_mm_mul_ps(lhs.sf, _mm_set1_ps(rhs))};
}

inline SIMD4f operator/(const SIMD4f& lhs, const SIMD4f& rhs)
{
	return SIMD4f{_mm_div_ps(lhs.sf, rhs.sf)};
}

inline SIMD4f operator/(const SIMD4f& lhs, float rhs)
{
	return SIMD4f{_mm_div_ps(lhs.sf, _mm_set1_ps(rhs))};
}

inline SIMD4f operator&(const SIMD4f& lhs, const SIMD4f& rhs)
{
	return SIMD4f{_mm_and_ps(lhs.sf, rhs.sf)};
}

inline SIMD4f operator|(const SIMD4f& lhs, const SIMD4f& rhs)
{
	return SIMD4f{_mm_or_ps(lhs.sf, rhs.sf)};
}

inline bool operator==(const SIMD4f& lhs, const SIMD4f& rhs)
{
	return SIMD4f::ToComparedMask(SIMD4f::Equal(lhs, rhs)) == 0xf;
}

inline bool operator!=(const SIMD4f& lhs, const SIMD4f& rhs)
{
	return SIMD4f::ToComparedMask(SIMD4f::Equal(lhs, rhs)) != 0xf;
}

inline SIMD4f SIMD4f::SetInt(int32_t x, int32_t y, int32_t z, int32_t w)
{
	return SIMD4f{_mm_setr_epi32((int)x, (int)y, (int)z, (int)w)};
}

inline SIMD4f SIMD4f::SetUInt(uint32_t x, uint32_t y, uint32_t z, uint32_t w)
{
	return SIMD4f{_mm_setr_epi32((int)x, (int)y, (int)z, (int)w)};
}

inline SIMD4f SIMD4f::Sqrt(const SIMD4f& in)
{
	return SIMD4f{_mm_sqrt_ps(in.sf)};
}

inline SIMD4f SIMD4f::Rsqrt(const SIMD4f& in)
{
	return SIMD4f{_mm_rsqrt_ps(in.sf)};
}

inline SIMD4f SIMD4f::Abs(const SIMD4f& in)
{
	return _mm_andnot_ps(_mm_set1_ps(-0.0f), in.sf);
}

inline SIMD4f SIMD4f::Min(const SIMD4f& lhs, const SIMD4f& rhs)
{
	return SIMD4f{_mm_min_ps(lhs.sf, rhs.sf)};
}

inline SIMD4f SIMD4f::Max(const SIMD4f& lhs, const SIMD4f& rhs)
{
	return SIMD4f{_mm_max_ps(lhs.sf, rhs.sf)};
}

inline SIMD4f SIMD4f::MulAdd(const SIMD4f& a, const SIMD4f& b, const SIMD4f& c)
{
#ifdef __AVX2__
	return SIMD4f{_mm_fmadd_ps(b.sf, c.sf, a.sf)};
#else
	return SIMD4f{_mm_add_ps(a.sf, _mm_mul_ps(b.sf, c.sf))};
#endif
}

inline SIMD4f SIMD4f::MulSub(const SIMD4f& a, const SIMD4f& b, const SIMD4f& c)
{
#ifdef __AVX2__
	return SIMD4f{_mm_fnmadd_ps(b.sf, c.sf, a.sf)};
#else
	return SIMD4f{_mm_sub_ps(a.sf, _mm_mul_ps(b.sf, c.sf))};
#endif
}

inline uint32_t SIMD4f::ToComparedMask(const SIMD4f& in)
{
	return (uint32_t)_mm_movemask_ps(in.sf);
}

inline SIMD4f SIMD4f::Equal(const SIMD4f& lhs, const SIMD4f& rhs)
{
	return SIMD4f{_mm_cmpeq_ps(lhs.sf, rhs.sf)};
}

inline SIMD4f SIMD4f::NotEqual(const SIMD4f& lhs, const SIMD4f& rhs)
{
	return SIMD4f{_mm_cmpneq_ps(lhs.sf, rhs.sf)};
}

inline SIMD4f SIMD4f::LessThan(const SIMD4f& lhs, const SIMD4f& rhs)
{
	return SIMD4f{_mm_cmplt_ps(lhs.sf, rhs.sf)};
}

inline SIMD4f SIMD4f::LessEqual(const SIMD4f& lhs, const SIMD4f& rhs)
{
	return SIMD4f{_mm_cmple_ps(lhs.sf, rhs.sf)};
}

inline SIMD4f SIMD4f::GreaterThan(const SIMD4f& lhs, const SIMD4f& rhs)
{
	return SIMD4f{_mm_cmpgt_ps(lhs.sf, rhs.sf)};
}

inline SIMD4f SIMD4f::GreaterEqual(const SIMD4f& lhs, const SIMD4f& rhs)
{
	return SIMD4f{_mm_cmpge_ps(lhs.sf, rhs.sf)};
}

inline SIMD4f SIMD4f::NearEqual(const SIMD4f& lhs, const SIMD4f& rhs, float epsilon)
{
	return LessEqual(Abs(lhs - rhs), SIMD4f(epsilon));
}

inline SIMD4f SIMD4f::IsZero(const SIMD4f& in, float epsilon)
{
	return LessEqual(Abs(in), SIMD4f(epsilon));
}

} // namespace Effekseer

#endif // __EFFEKSEER_SIMD4F_SSE_H__