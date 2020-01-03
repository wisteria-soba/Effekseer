
#ifndef __EFFEKSEER_SIMD44F_SSE_H__
#define __EFFEKSEER_SIMD44F_SSE_H__

#include "Effekseer.SIMD4f_SSE.h"

namespace Effekseer
{

inline void transpose(
	SIMD4f& outx, SIMD4f& outy, SIMD4f& outz, SIMD4f& outw, const SIMD4f& inx, const SIMD4f& iny, const SIMD4f& inz, const SIMD4f& inw)
{
	outx = inx;
	outy = iny;
	outz = inz;
	outw = inw;

	_MM_TRANSPOSE4_PS(outx.sf, outy.sf, outz.sf, outw.sf);
}

} // namespace Effekseer

#endif // __EFFEKSEER_SIMD4F_H__