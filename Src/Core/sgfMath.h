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

namespace sgf
{
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
}