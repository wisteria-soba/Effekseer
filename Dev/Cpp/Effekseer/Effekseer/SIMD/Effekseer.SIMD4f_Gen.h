
#ifndef __EFFEKSEER_SIMD4F_GEN_H__
#define __EFFEKSEER_SIMD4F_GEN_H__

#include <stdint.h>
#include "../Effekseer.Math.h"

namespace Effekseer
{

inline float Sqrt(float x)
{
	return std::sqrt(x);
}
inline float Rsqrt(float x)
{
	return 1.0f / std::sqrt(x);
}

/**
	@brief	simd class for generic
*/
struct alignas(16) SIMD4f
{
	union {
		float f[4];
		uint32_t i[4];
	};

	SIMD4f() = default;
	SIMD4f(const SIMD4f& rhs) = default;
	SIMD4f(float x, float y, float z, float w) { f[0] = x; f[1] = y; f[2] = z; f[3] = w; }
	SIMD4f(float i) { f[0] = i; f[1] = i; f[2] = i; f[3] = i; }

	float GetX() const { return f[0]; }
	float GetY() const { return f[1]; }
	float GetZ() const { return f[2]; }
	float GetW() const { return f[3]; }

	void SetX(float o) { f[0] = o; }
	void SetY(float o) { f[1] = o; }
	void SetZ(float o) { f[2] = o; }
	void SetW(float o) { f[3] = o; }

	SIMD4f& operator+=(const SIMD4f& rhs)
	{
		for (size_t i = 0; i < 4; i++)
		{
			f[i] += rhs.f[i];
		}
		return *this;
	}

	SIMD4f& operator-=(const SIMD4f& rhs)
	{
		for (size_t i = 0; i < 4; i++)
		{
			f[i] -= rhs.f[i];
		}
		return *this;
	}

	SIMD4f& operator*=(const SIMD4f& rhs)
	{
		for (size_t i = 0; i < 4; i++)
		{
			f[i] *= rhs.f[i];
		}
		return *this;
	}

	SIMD4f& operator*=(float rhs)
	{
		for (size_t i = 0; i < 4; i++)
		{
			f[i] *= rhs;
		}
		return *this;
	}

	SIMD4f& operator/=(const SIMD4f& rhs)
	{
		for (size_t i = 0; i < 4; i++)
		{
			f[i] /= rhs.f[i];
		}
		return *this;
	}

	SIMD4f& operator/=(float rhs)
	{
		for (size_t i = 0; i < 4; i++)
		{
			f[i] /= rhs;
		}
		return *this;
	}

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
		return lhs * rhs.f[LANE];
	}

	template<size_t LANE>
	static SIMD4f MulAddLane(const SIMD4f& a, const SIMD4f& b, const SIMD4f& c)
	{
		static_assert(LANE < 4, "LANE is must be less than 4.");
		return a + b * c.f[LANE];
	}

	template<size_t LANE>
	static SIMD4f MulSubLane(const SIMD4f& a, const SIMD4f& b, const SIMD4f& c)
	{
		static_assert(LANE < 4, "LANE is must be less than 4.");
		return a - b * c.f[LANE];
	}

	template <uint32_t indexX, uint32_t indexY, uint32_t indexZ, uint32_t indexW>
	static SIMD4f Swizzle(const SIMD4f& in)
	{
		static_assert(indexX < 4, "indexX is must be less than 4.");
		static_assert(indexY < 4, "indexY is must be less than 4.");
		static_assert(indexZ < 4, "indexZ is must be less than 4.");
		static_assert(indexW < 4, "indexW is must be less than 4.");
		return SIMD4f{in.f[indexX], in.f[indexY], in.f[indexZ], in.f[indexW]};
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
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.f[i] = lhs.f[i] + rhs.f[i];
	}
	return ret;
}

inline SIMD4f operator-(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.f[i] = lhs.f[i] - rhs.f[i];
	}
	return ret;
}

inline SIMD4f operator*(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.f[i] = lhs.f[i] * rhs.f[i];
	}
	return ret;
}

inline SIMD4f operator*(const SIMD4f& lhs, float rhs)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.f[i] = lhs.f[i] * rhs;
	}
	return ret;
}

inline SIMD4f operator/(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.f[i] = lhs.f[i] / rhs.f[i];
	}
	return ret;
}

inline SIMD4f operator/(const SIMD4f& lhs, float rhs)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.f[i] = lhs.f[i] / rhs;
	}
	return ret;
}

inline SIMD4f operator&(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.i[i] = lhs.i[i] & rhs.i[i];
	}
	return ret;
}

inline SIMD4f operator|(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.i[i] = lhs.i[i] | rhs.i[i];
	}
	return ret;
}

inline bool operator==(const SIMD4f& lhs, const SIMD4f& rhs)
{
	bool ret = true;
	for (size_t i = 0; i < 4; i++)
	{
		ret &= lhs.f[i] == rhs.f[i];
	}
	return ret;
}

inline bool operator!=(const SIMD4f& lhs, const SIMD4f& rhs)
{
	bool ret = true;
	for (size_t i = 0; i < 4; i++)
	{
		ret &= lhs.f[i] == rhs.f[i];
	}
	return !ret;
}

inline SIMD4f SIMD4f::SetInt(int32_t x, int32_t y, int32_t z, int32_t w)
{
	SIMD4f ret;
	ret.i[0] = (uint32_t)x;
	ret.i[1] = (uint32_t)y;
	ret.i[2] = (uint32_t)z;
	ret.i[3] = (uint32_t)w;
	return ret;
}

inline SIMD4f SIMD4f::SetUInt(uint32_t x, uint32_t y, uint32_t z, uint32_t w)
{
	SIMD4f ret;
	ret.i[0] = (uint32_t)x;
	ret.i[1] = (uint32_t)y;
	ret.i[2] = (uint32_t)z;
	ret.i[3] = (uint32_t)w;
	return ret;
}

inline SIMD4f SIMD4f::Sqrt(const SIMD4f& in)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.f[i] = std::sqrt(in.f[i]);
	}
	return ret;
}

inline SIMD4f SIMD4f::Rsqrt(const SIMD4f& in)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.f[i] = 1.0f / std::sqrt(in.f[i]);
	}
	return ret;
}

inline SIMD4f SIMD4f::Abs(const SIMD4f& in)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.f[i] = std::abs(in.f[i]);
	}
	return ret;
}

inline SIMD4f SIMD4f::Min(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.f[i] = std::fmin(lhs.f[i], rhs.f[i]);
	}
	return ret;
}

inline SIMD4f SIMD4f::Max(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.f[i] = std::fmax(lhs.f[i], rhs.f[i]);
	}
	return ret;
}

inline SIMD4f SIMD4f::MulAdd(const SIMD4f& a, const SIMD4f& b, const SIMD4f& c)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.f[i] = a.f[i] + b.f[i] * c.f[i];
}
	return ret;
}

inline SIMD4f SIMD4f::MulSub(const SIMD4f& a, const SIMD4f& b, const SIMD4f& c)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.f[i] = a.f[i] - b.f[i] * c.f[i];
}
	return ret;
}

inline uint32_t SIMD4f::ToComparedMask(const SIMD4f& in)
{
	return (in.i[0] & 0x1) | (in.i[1] & 0x2) | (in.i[2] & 0x4) | (in.i[3] & 0x8);
}

inline SIMD4f SIMD4f::Equal(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.i[i] = (lhs.f[i] == rhs.f[i]) ? 0xffffffff : 0;
	}
	return ret;
}

inline SIMD4f SIMD4f::NotEqual(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.i[i] = (lhs.f[i] != rhs.f[i]) ? 0xffffffff : 0;
	}
	return ret;
}

inline SIMD4f SIMD4f::LessThan(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.i[i] = (lhs.f[i] < rhs.f[i]) ? 0xffffffff : 0;
	}
	return ret;
}

inline SIMD4f SIMD4f::LessEqual(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.i[i] = (lhs.f[i] <= rhs.f[i]) ? 0xffffffff : 0;
	}
	return ret;
}

inline SIMD4f SIMD4f::GreaterThan(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.i[i] = (lhs.f[i] > rhs.f[i]) ? 0xffffffff : 0;
	}
	return ret;
}

inline SIMD4f SIMD4f::GreaterEqual(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.i[i] = (lhs.f[i] >= rhs.f[i]) ? 0xffffffff : 0;
	}
	return ret;
}

inline SIMD4f SIMD4f::NearEqual(const SIMD4f& lhs, const SIMD4f& rhs, float epsilon)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.i[i] = (std::abs(lhs.f[i] - rhs.f[i]) <= epsilon) ? 0xffffffff : 0;
	}
	return ret;
}

inline SIMD4f SIMD4f::IsZero(const SIMD4f& in, float epsilon)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.i[i] = (std::abs(in.f[i]) <= epsilon) ? 0xffffffff : 0;
	}
	return ret;
}

} // namespace Effekseer

#endif // __EFFEKSEER_SIMD4F_GEN_H__