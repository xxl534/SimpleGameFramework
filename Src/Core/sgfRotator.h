#pragma once
/*************************************
	created: 2018/08/05 20:28 
	filename:	G:\Visual Studio 2015\SimpleGameFrame\Src\Core\sgfRotator.h
	file path:	G:\Visual Studio 2015\SimpleGameFrame\Src\Core
	file base:	sgfRotator
	file ext:	h	
	author: 	Xiexuelong
	
	purpose:
*************************************/

namespace sgf
{
	struct Vector3f;
	struct Matrix4f;
	struct Quaternion;
	struct Rotator
	{
		int32 pitch, yaw, roll;

		inline Rotator() {};
		inline Rotator(int32 a_nPitch, int32 a_nYaw, int32 a_nRoll):pitch(a_nPitch),yaw(a_nYaw),roll(a_nRoll) {};

		inline Rotator		operator+ (const Rotator& a_rhs) const;
		inline Rotator		operator- (const Rotator& a_rhs) const;
		inline Rotator		operator* (float a_fScale) const;

		inline Rotator&	operator+=(const Rotator& a_rhs);
		inline Rotator&	operator-=(const Rotator& a_rhs);
		inline Rotator&	operator*=(float a_fScale);

		inline bool		operator==(const Rotator& a_rhs) const;
		inline bool		operator!=(const Rotator& a_rhs) const;

		inline Quaternion	ToQuaternion() const;
		inline Vector3f	ToEular() const;
		inline Vector3f	ToEularArc() const;

		inline Rotator		Clamp() const;
		inline Rotator		ClampPos() const;

		inline Rotator		Normalize() const;
		inline void		MakeShortestRoute();

		static inline Rotator	FromEular(const Vector3f& a_vEular);
		static inline Rotator	FromEular(float a_fx, float a_fy, float a_fz);
		static inline Rotator	FromEularArc(const Vector3f& a_vArc);
		static inline Rotator	FromEularArc(float a_fx, float a_fy, float a_fz);
		static inline Rotator	FromQuaternion(const Quaternion& a_quat);
		static inline Rotator	FromMatrix(const Matrix4f& a_mat);

		static inline int32	NormalizeAxis(int32 a_fAngle);

	};

}
#include "sgfRotator.inl"