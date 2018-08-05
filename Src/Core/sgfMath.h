#pragma once
/********************************************************************
	created:	2018/06/21
	created:	21:6:2018   20:40
	filename: 	E:\SimpleGameFramework\Src\Core\sgfMath.h
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfMath
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

#define MATH_NUM_ANGLES 16384
#define MATH_ANGLE_SHIFT 	2		// Bits to right-shift to get lookup value.
namespace sgf
{
	extern const float	GSinTable[MATH_NUM_ANGLES];

	static const float	kPI = 3.1415926535897932f;
	static const float	kPIDivide180 = 0.0174532625199433f;

	template< class T > inline T MathAbs(const T a_value)
	{
		return (a_value >= (T)0) ? a_value : -a_value;
	}

	template< class T > inline T MathClamp(const T a_value, const T a_min, const T a_max)
	{
		return a_value < a_min ? a_min : a_value < a_min ? a_value : a_max;
	}

	template<class T> inline T Min(const T a, const T b)
	{
		return a <= b ? a : b;
	}

	template<class T> inline T Max(const T a, const T b)
	{
		return a >= b ? a : b;
	}

	//----------------------------------------
	inline int32 
		MathTrunc(float a_f)
	{
		return a_f;
	}

	//------------------------------------------------------------------------
	inline float MathSinTab(int32 angle)
	{
		return GSinTable[((angle >> MATH_ANGLE_SHIFT)&(MATH_NUM_ANGLES - 1))];
	}

	//------------------------------------------------------------------------
	inline float MathCosTab(int32 angle)
	{
		return GSinTable[(((angle + 16384) >> MATH_ANGLE_SHIFT)&(MATH_NUM_ANGLES - 1))];
	}

	//------------------------------------------------------------------------
	inline float MathSinFloat(float angle)
	{
		return MathSinTab(MathTrunc((angle*65536.f) / (2.f*kPI)));
	}

	//------------------------------------------------------------------------
	inline float MathCosFloat(float angle)
	{
		return MathCosTab(MathTrunc((angle*65536.f) / (2.f*kPI)));
	}
}