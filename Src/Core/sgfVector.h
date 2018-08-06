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

	struct Vector3f : public TVector3<float>
	{
		Vector3f()
		{

		}

		Vector3f(const TVector3<float>& a_v)
			:TVector3<float>(a_v)
		{

		}

		Vector3f(float a_f)
		{
			x = a_f;
			y = a_f;
			z = a_f;
		}
		Vector3f(float a_fx, float a_fy, float a_fz)
		{
			x = a_fx;
			y = a_fy;
			z = a_fz;
		}

		Vector3f(const float* a_p)
		{
			x = a_p[0];
			y = a_p[1];
			z = a_p[2];
		}

		inline Vector3f&		Lerp(const Vector3f& a_v, float a_fFactor);
		inline Vector3f			GetLerp(const Vector3f& a_v, float a_fFactor) const;
		inline Vector3f&		Abs();
		inline Vector3f			GetAbs() const;
		inline Vector3f&		Normalize();
		inline Vector3f			GetNormalize() const;
		inline float			Length() const; 
		inline float			LengthSqr() const;
		inline void				FindBestAxisVectors(Vector3f& a_vAxis1, Vector3f& a_vAxis2);
		inline Vector3f&		Set(float a_fx, float a_fy, float a_fz);

		// Rotates the vector by a specified number of a_fDegrees around the X axis and the specified a_vecCenter
		inline void			RotateYZBy(float a_fDegrees, const Vector3f& a_vecCenter = Vector3f(0.f, 0.f, 0.f));
		// Rotates the vector by a specified number of a_fDegrees around the Y axis and the specified a_vecCenter
		inline void			RotateXZBy(float a_fDegrees, const Vector3f& a_vecCenter = Vector3f(0.f, 0.f, 0.f));
		// Rotates the vector by a specified number of a_fDegrees around the Z axis and the specified a_vecCenter
		inline void			RotateXYBy(float a_fDegrees, const Vector3f& a_vecCenter = Vector3f(0.f, 0.f, 0.f));

		inline static const Vector3f&	Zero();
	private:
		static Vector3f			ms_vZero;
	};

}

#include "sgfVector.inl"