#include <cmath>
#include "Effekseer.Mat44f.h"
#include "../Effekseer.Matrix44.h"

namespace Effekseer
{
	
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
const Mat44f Mat44f::Identity = Mat44f(
	1, 0, 0, 0, 
	0, 1, 0, 0, 
	0, 0, 1, 0, 
	0, 0, 0, 1
);

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Mat44f::Mat44f(const Matrix44& mat)
	: X(mat.Values[0][0], mat.Values[1][0], mat.Values[2][0], mat.Values[3][0])
	, Y(mat.Values[0][1], mat.Values[1][1], mat.Values[2][1], mat.Values[3][1])
	, Z(mat.Values[0][2], mat.Values[1][2], mat.Values[2][2], mat.Values[3][2])
	, W(mat.Values[0][3], mat.Values[1][3], mat.Values[2][3], mat.Values[3][3])
{
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
bool Mat44f::IsValid() const
{
	const SIMD4f nan{NAN};
	const SIMD4f inf{INFINITY};
	SIMD4f res = 
		SIMD4f::Equal(X, nan) | 
		SIMD4f::Equal(Y, nan) | 
		SIMD4f::Equal(Z, nan) |
		SIMD4f::Equal(W, nan) |
		SIMD4f::Equal(X, inf) | 
		SIMD4f::Equal(Y, inf) | 
		SIMD4f::Equal(Z, inf) | 
		SIMD4f::Equal(W, inf);
	return SIMD4f::ToComparedMask(res) == 0;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
bool Mat44f::Equal(const Mat44f& lhs, const Mat44f& rhs, float epsilon)
{
	SIMD4f ret =
		SIMD4f::NearEqual(lhs.X, rhs.X, epsilon) &
		SIMD4f::NearEqual(lhs.Y, rhs.Y, epsilon) &
		SIMD4f::NearEqual(lhs.Z, rhs.Z, epsilon) &
		SIMD4f::NearEqual(lhs.W, rhs.W, epsilon);
	return (SIMD4f::ToComparedMask(ret) & 0xf) == 0xf;

}

}
