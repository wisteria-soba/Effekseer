
#ifndef __EFFEKSEER_SIMD4F_GEN_H__
#define __EFFEKSEER_SIMD4F_GEN_H__


namespace Effekseer
{

/**
	@brief	simd class for generic
*/
struct alignas(16) SIMD4f
{
	union {
		float f[4];
	};

	SIMD4f() = default;
	SIMD4f(const SIMD4f& rhs) = default;
	SIMD4f(float x, float y, float z, float w) { f[0] = x; f[1] = y; f[2] = z; f[3] = w; }

	float GetX() const { return f[0]; }
	float GetY() const { return f[1]; }
	float GetZ() const { return f[2]; }
	float GetW() const { return f[3]; }

	void SetX(float o) { f[0] = o; }
	void SetY(float o) { f[1] = o; }
	void SetZ(float o) { f[2] = o; }
	void SetW(float o) { f[3] = o; }
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
		ret &= lhs.f[i] != rhs.f[i];
	}
	return ret;
}

inline bool operator<(const SIMD4f& lhs, const SIMD4f& rhs)
{
	bool ret = true;
	for (size_t i = 0; i < 4; i++)
	{
		ret &= lhs.f[i] < rhs.f[i];
	}
	return ret;
}

inline bool operator<=(const SIMD4f& lhs, const SIMD4f& rhs)
{
	bool ret = true;
	for (size_t i = 0; i < 4; i++)
	{
		ret &= lhs.f[i] <= rhs.f[i];
	}
	return ret;
}

inline bool operator>(const SIMD4f& lhs, const SIMD4f& rhs)
{
	bool ret = true;
	for (size_t i = 0; i < 4; i++)
	{
		ret &= lhs.f[i] > rhs.f[i];
	}
	return ret;
}

inline bool operator>=(const SIMD4f& lhs, const SIMD4f& rhs)
{
	bool ret = true;
	for (size_t i = 0; i < 4; i++)
	{
		ret &= lhs.f[i] >= rhs.f[i];
	}
	return ret;
}

template<size_t LANE>
inline SIMD4f mul(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.f[i] = lhs.f[i] * rhs.f[LANE];
	}
	return ret;
}

inline SIMD4f sqrt(const SIMD4f& o)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.f[i] = std::sqrt(o.f[i]);
	}
	return ret;
}

inline SIMD4f rsqrt(const SIMD4f& o)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.f[i] = 1.0f / std::sqrt(o.f[i]);
	}
	return ret;
}

inline SIMD4f abs(const SIMD4f& o)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.f[i] = std::abs(o.f[i]);
	}
	return ret;
}

inline SIMD4f min(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.f[i] = std::fmin(lhs.f[i], rhs.f[i]);
	}
	return ret;
}

inline SIMD4f max(const SIMD4f& lhs, const SIMD4f& rhs)
{
	SIMD4f ret;
	for (size_t i = 0; i < 4; i++)
	{
		ret.f[i] = std::fmax(lhs.f[i], rhs.f[i]);
	}
	return ret;
}

} // namespace Effekseer

#endif // __EFFEKSEER_SIMD4F_GEN_H__