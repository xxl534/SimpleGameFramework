#pragma once
/********************************************************************
	created:	2018/06/17
	created:	17:6:2018   12:47
	filename: 	E:\SimpleGameFramework\Src\Core\sgfVector.h
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfVector
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	template<typename T>
	struct TVector2
	{
		union 
		{
			struct
			{
				T x, y;
			};
			T f[2];
		};

		TVector2() {}
		TVector2(T a_x, T a_y) :x(a_x), y(a_y) {}

		bool			operator==(const TVector2<T>& a_rhs) const;
		bool			operator!=(const TVector2<T>& a_rhs) const;
		TVector2<T>&	operator-=(const TVector2<T>& a_rhs);
		TVector2<T>		operator-(const TVector2<T>& a_rhs) const;
		TVector2<T>		operator-() const;
		TVector2<T>&	operator+=(const TVector2<T>& a_rhs);
		TVector2<T>		operator+(const TVector2<T>& a_rhs) const;
		TVector2<T>&	operator*=(float a_f);
		TVector2<T>		operator*(float a_f) const;
		TVector2<T>&	operator*=(const TVector2<T>& a_rhs);
		TVector2<T>		operator*(const TVector2<T>& a_rhs) const;
		TVector2<T>&	operator/=(float a_f);
		TVector2<T>		operator/(float a_f) const;
		float			dot(const TVector2<T>& a_rhs) const;
	};

	template<typename T>
	struct TVector3
	{
		union
		{
			struct
			{
				T x, y, z;
			};
			T f[3];
		};

		TVector3() {}
		TVector3(T a_x, T a_y, T a_z) :x(a_x), y(a_y), z(a_z) {}

		bool			operator==(const TVector3<T>& a_rhs) const;
		bool			operator!=(const TVector3<T>& a_rhs) const;
		TVector3<T>&	operator-=(const TVector3<T>& a_rhs);
		TVector3<T>		operator-(const TVector3<T>& a_rhs) const;
		TVector3<T>		operator-() const;
		TVector3<T>&	operator+=(const TVector3<T>& a_rhs);
		TVector3<T>		operator+(const TVector3<T>& a_rhs) const;
		TVector3<T>&	operator*=(float a_f);
		TVector3<T>		operator*(float a_f) const;
		TVector3<T>&	operator*=(const TVector3<T>& a_rhs);
		TVector3<T>		operator*(const TVector3<T>& a_rhs) const;
		TVector3<T>&	operator/=(float a_f);
		TVector3<T>		operator/(float a_f) const;
		float			dot(const TVector3<T>& a_rhs) const;
		TVector3<T>		cross(const TVector3<T>& a_rhs) const;
	};

	//-------------------------------------------------------------------------
	template<typename T>
	struct TVector4
	{
		union
		{
			struct
			{
				T x, y, z, w;
			};
			T f[4];
		};

		TVector4() {}
		TVector4(T a_x, T a_y, T a_z, T a_w) :x(a_x), y(a_y), z(a_z), w(a_w) {}

		bool			operator==(const TVector4<T>& a_rhs) const;
		bool			operator!=(const TVector4<T>& a_rhs) const;
		TVector4<T>&	operator-=(const TVector4<T>& a_rhs);
		TVector4<T>		operator-(const TVector4<T>& a_rhs) const;
		TVector4<T>		operator-() const;
		TVector4<T>&	operator+=(const TVector4<T>& a_rhs);
		TVector4<T>		operator+(const TVector4<T>& a_rhs) const;
		TVector4<T>&	operator*=(float a_f);
		TVector4<T>		operator*(float a_f) const;
		TVector4<T>&	operator*=(const TVector4<T>& a_rhs);
		TVector4<T>		operator*(const TVector4<T>& a_rhs) const;
		TVector4<T>&	operator/=(float a_f);
		TVector4<T>		operator/(float a_f) const;
		float			dot(const TVector4<T>& a_rhs) const;
	};
}

#include "sgfVector.inl"