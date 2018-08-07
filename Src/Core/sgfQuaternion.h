#pragma once
/*************************************
	created: 2018/08/06 08:01 
	filename:	G:\Visual Studio 2015\SimpleGameFrame\Src\Core\sgfQuaternion.h
	file path:	G:\Visual Studio 2015\SimpleGameFrame\Src\Core
	file base:	sgfQuaternion
	file ext:	h	
	author: 	Xiexuelong
	
	purpose:
*************************************/

#include "sgfVector.h"

namespace sgf
{
	struct Matrix4f;
	struct Quaternion : public TVector4<float>
	{
		Quaternion() {}
		Quaternion(float a_fx, float a_fy, float a_fz, float a_fw)
		{
			x = a_fx;
			y = a_fy;
			z = a_fz;
			w = a_fw;
		}
		Quaternion(float* a_p)
		{
			x = a_p[0];
			y = a_p[1];
			z = a_p[2];
			w = a_p[3];
		}

		inline Quaternion&	operator*=(const Quaternion& a_rhs);
		inline Quaternion	operator* (const Quaternion& a_rhs) const;

		inline void			SetIdentity();
		inline void			Normalize();
		inline Quaternion	Slerp(const Quaternion& a_qTo, const float a_fWeight) const;
		inline void			Blend(const Quaternion& a_qTo, const float a_fWeight);
		inline Matrix4f		ToRotationMatrix() const;
		inline void			ToRotationAxis(Vector3f& out_vAxis, float& a_fAngle) const;

		static inline Quaternion	Identity();
		static inline Quaternion	RotationAxisX(const float a_fAngle);
		static inline Quaternion	RotationAxisY(const float a_fAngle);
		static inline Quaternion	RotationAxisZ(const float a_fAngle);
		static inline Quaternion	RotationAxis(const Vector3f& a_vAxis, const float a_fAngle);
		static inline Quaternion	RotationBetween(const Vector3f& a_v1, const Vector3f& a_v2);
		static inline Quaternion	Multiply(const Quaternion& a_qA, const Quaternion& a_qB);
		static inline Quaternion	FromMatrix(const Matrix4f& a_mat);
	};
}
#include "sgfQuaternion.inl"
