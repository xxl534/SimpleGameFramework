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
#define MATH_ANGLE_BITS		14		// Number of valid bits in angles.
#define MATH_ANGLE_MASK		(((1<<MATH_ANGLE_BITS)-1)<<(16-MATH_ANGLE_BITS))
#define MATH_SMALL_NUMBER		(1.e-8)
#define MATH_KINDA_SMALL_NUMBER	(1.e-4)
namespace sgf
{
	extern const float	GSinTable[MATH_NUM_ANGLES];

	static const float	kPI = 3.1415926535897932f;
	static const float	kPIDivide180 = 0.0174532625199433f;
	static const float	kSmallNumber = 1.e-8f;
	static const float	kKindaSmallNumber = 1.e-4f;
	static const float	kBigNumber = 3.4e+38f;
	static const float	kEulersNumber = 2.71828182845904523536f;
	static const float	kInvPI = 0.31830988618f;
	static const float	kHalfPI = 1.57079632679f;
	static const float	kQuarterPI = 0.78539816340f;
	static const float	kDelta = 0.00001f;
	static const float	kCos30 = 0.86602540378443865f;
	static const float  kCos45 = 0.7071067811865475244f;
	static const float  kSqrt2 = 1.4142135623730950488f;
	static const float	kSqrt3 = 1.7320508075688772935f;
	static const int32	kMaxInt = 2147483647;

	//----------------------------------------
	template< class T > inline T MathAbs(const T a_value)
	{
		return (a_value >= (T)0) ? a_value : -a_value;
	}

	//----------------------------------------
	template< class T > inline T MathClamp(const T a_value, const T a_min, const T a_max)
	{
		return a_value < a_min ? a_min : a_value < a_min ? a_value : a_max;
	}

	//----------------------------------------
	template<class T> inline T Min(const T a, const T b)
	{
		return a <= b ? a : b;
	}

	//----------------------------------------
	template<class T> inline T Max(const T a, const T b)
	{
		return a >= b ? a : b;
	}

	//----------------------------------------
	template< class T > inline T Square(const T A)
	{
		return A*A;
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

	//------------------------------------------------------------------------
	inline int32 MathRound(float f)
	{
		return MathTrunc(roundf(f));
	}

	//------------------------------------------------------------------------
	inline float MathAtan2(float y, float x)
	{
		return atan2f(y, x);
	}

	//------------------------------------------------------------------------
	inline float MathSqrt(float f)
	{
		return sqrtf(f);
	}

	//------------------------------------------------------------------------
	inline bool MathNearlyZero(float f, float tolerance = MATH_KINDA_SMALL_NUMBER)
	{
		return	f > -tolerance&&f < tolerance;
	}
}