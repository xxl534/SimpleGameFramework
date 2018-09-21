#pragma once
/********************************************************************
	created:	2018/06/17
	created:	17:6:2018   13:40
	filename: 	E:\SimpleGameFramework\Src\Core\sgfMatrix.a_fHeight
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfMatrix
	file ext:	a_fHeight
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/
#include"sgfMath.h"
namespace sgf
{
	template<typename T>
	struct TMatrix44
	{
		union
		{
			struct 
			{
				T _11, _12, _13, _14;
				T _21, _22, _23, _24;
				T _31, _32, _33, _34;
				T _41, _42, _43, _44;
			};
			T f[16];
			T m[4][4];
		};

		T&				operator()(const int32 a_row, const int32 a_col);
		const T&		operator()(const int32 a_row, const int32 a_col) const;
		T*				operator[](const int32 a_row);
		const T*		operator[](const int32 a_row) const;

		TMatrix44<T>&	operator+=(const TMatrix44<T>& a_rhs);
		TMatrix44<T>	operator+(const TMatrix44<T>& a_rhs) const;
		TMatrix44<T>&	operator-=(const TMatrix44<T>& a_rhs);
		TMatrix44<T>	operator-(const TMatrix44<T>& a_rhs) const;
		TMatrix44<T>&	operator*=(const T a_val);
		TMatrix44<T>	operator*(const T a_val) const;
		TMatrix44<T>&	operator/=(const T a_val);
		TMatrix44<T>	operator/(const T a_val) const;
		bool			operator==(const TMatrix44<T>& a_rhs) const;
		bool			operator!=(const TMatrix44<T>& a_rhs) const;
	};

	struct Quaternion;
	struct Rotator;
	struct Vector3f;
	struct Matrix4f : public TMatrix44<float>
	{
		static const Matrix4f	kIdentity;
		static const Matrix4f	kZero;


		Matrix4f() {}

		Matrix4f(float m0, float m1, float m2, float m3,
			float m4, float m5, float m6, float m7,
			float m8, float m9, float m10, float m11,
			float m12, float m13, float m14, float m15)
		{
			f[0] = m0;	f[1] = m1;	f[2] = m2;	f[3] = m3;
			f[4] = m4;	f[5] = m5;	f[6] = m6;	f[7] = m7;
			f[8] = m8;	f[9] = m9;	f[10] = m10;	f[11] = m11;
			f[12] = m12;	f[13] = m13;	f[14] = m14;	f[15] = m15;
		}

		Matrix4f(const float* a_mat)
		{
			for (int32 i = 0; i < 16; i++)
			{
				f[i] = a_mat[i];
			}
		}

		inline Matrix4f&	operator*=(const Matrix4f& a_mat);
		inline Matrix4f	operator*(const Matrix4f& a_mat) const;
		inline bool		Equals(const Matrix4f& a_mat, float a_fTolerance = kKindaSmallNumber) const;

		inline void		SetIdentity();
		inline Vector3f	TransformNormal(const Vector3f& a_v) const;
		inline Vector3f	TransformVector(const Vector3f& a_v) const;
		inline void		TransformVector(float x1, float y1, float z1, float& x2, float& y2, float& z2) const;
		inline float	Determinant() const;
		inline Vector3f	GetAxis(int32 a_nIdx) const;

		inline Vector3f	GetTranslate() const;
		inline void		SetTranslate(const Vector3f& a_v);
		inline Vector3f	GetScale() const;
		inline void		SetScale(const Vector3f& a_vScale);

		inline bool		Decompose(Vector3f* out_vScale, Quaternion* out_quat, Vector3f* out_vTrans);

		inline Matrix4f	Transpose() const;
		inline Matrix4f&	TransposeSelf();
		inline Matrix4f	Inverse() const;
		inline Matrix4f&	InverseSelf();

		static inline const Matrix4f&	Identity();
		static inline void		Multiply(Matrix4f& out_mat, const Matrix4f& a_matA, const Matrix4f& a_matB);
		static inline Matrix4f	LookAtLH(const Vector3f& a_vEye, const Vector3f& a_vAt, const Vector3f& a_vUp);
		static inline Matrix4f	LookAtRH(const Vector3f& a_vEye, const Vector3f& a_vAt, const Vector3f& a_vUp);
		static inline Matrix4f	PerspectiveFovLH(const float a_fFov, const float a_fAspect, const float a_fZNear, const float a_fZFar);
		static inline Matrix4f	PerspectiveFovRH(const float a_fFov, const float a_fAspect, const float a_fZNear, const float a_fZFar);
		static inline Matrix4f	PerspectiveLH(const float a_fWidth, const float a_fHeight, const float a_fZNear, const float a_fZFar);
		static inline Matrix4f	PerspectiveRH(const float a_fWidth, const float a_fHeight, const float a_fZNear, const float a_fZFar);
		static inline Matrix4f	OrthoLH(const float a_fWidth, const float a_fHeight, const float a_fZNear, const float a_fZFar);
		static inline Matrix4f	OrthoRH(const float a_fWidth, const float a_fHeight, const float a_fZNear, const float a_fZFar);
		static inline Matrix4f	OrthoOffCenterLH(const float a_fLeft, const float a_fRight, const float a_fBottom, const float a_fTop, const float a_fZNear, const float a_fZFar);
		static inline Matrix4f	OrthoOffCenterRH(const float a_fLeft, const float a_fRight, const float a_fBottom, const float a_fTop, const float a_fZNear, const float a_fZFar);

		static inline Matrix4f	RotationXMatrix(float a_fRoll);
		static inline Matrix4f	RotationYMatrix(float a_fPitch);
		static inline Matrix4f	RotationZMatrix(float a_fYaw);

		static inline Matrix4f	TranslationMatrix(const Vector3f& a_vTrans);
		static inline Matrix4f	ScaleMatrix(const Vector3f& a_vScale);
		static inline Matrix4f	ScaleTranslationMatrix(const Vector3f& a_vScale, const Vector3f& a_vTrans);
		static inline Matrix4f	QuaternionTranslationMatrix(const Quaternion& a_quat, const Vector3f& a_vTrans);

		static Matrix4f			RotationMatrix(const Vector3f& a_vEular);
		static Matrix4f			RotationMatrix(const Rotator& a_rot);
		static Matrix4f			ScaleRotationMatrix(const Vector3f& a_vScale, const Rotator& a_rot);
		static Matrix4f			ScaleRotationTranslationMatrix(const Vector3f& a_vScale, const Rotator& a_rot, const Vector3f& a_vTrans);
	};



}

#include "sgfMatrix.inl"