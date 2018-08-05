#pragma once
/********************************************************************
	created:	2018/06/17
	created:	17:6:2018   13:40
	filename: 	E:\SimpleGameFramework\Src\Core\sgfMatrix.h
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfMatrix
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

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

		Matrix4f(const float* mat)
		{
			for (int32 i = 0; i < 16; i++)
			{
				f[i] = mat[i];
			}
		}

		inline Matrix4f&	operator*=(const Matrix4f& mat);
		inline Matrix4f	operator*(const Matrix4f& mat) const;
		inline bool		Equals(const Matrix4f& mat, float fTolerance = kKindaSmallNumber) const;

		inline void		SetIdentity();
		inline Vector3f	TransformNormal(const Vector3f& vec) const;
		inline Vector3f	TransformVector(const Vector3f& vec) const;
		inline void		TransformVector(float x1, float y1, float z1, float& x2, float& y2, float& z2) const;
		inline Vector4	TransformVector4(const Vector4& vec) const;
		inline float	Determinant() const;
		inline Vector3f	GetAxis(int32 idx) const;

		inline Vector3f	GetTranslate() const;
		inline void		SetTranslate(const Vector3f& vec);
		inline Vector3f	GetScale() const;
		void			SetScale(const Vector3f& scale);

		inline bool		Decompose(Vector3f* outScale, Quaternion* outRotQuat, Vector3f* outTrans);

		inline Matrix4f	Transpose() const;
		inline Matrix4f&	TransposeSelf();
		inline Matrix4f	Inverse() const;
		inline Matrix4f&	InverseSelf();

		static inline const Matrix4f&	Identity();
		static inline void		Multiply(Matrix4f& mOut, const Matrix4f& mA, const Matrix4f& mB);
		static inline Matrix4f	LookAtLH(const Vector3f& vEye, const Vector3f& vAt, const Vector3f& vUp);
		static inline Matrix4f	LookAtRH(const Vector3f& vEye, const Vector3f& vAt, const Vector3f& vUp);
		static inline Matrix4f	PerspectiveFovLH(const float fFov, const float fAspect, const float zn, const float zf);
		static inline Matrix4f	PerspectiveFovRH(const float fFov, const float fAspect, const float zn, const float zf);
		static inline Matrix4f	PerspectiveLH(const float w, const float h, const float zn, const float zf);
		static inline Matrix4f	PerspectiveRH(const float w, const float h, const float zn, const float zf);
		static inline Matrix4f	OrthoLH(const float w, const float h, const float zn, const float zf);
		static inline Matrix4f	OrthoRH(const float w, const float h, const float zn, const float zf);
		static inline Matrix4f	OrthoOffCenterLH(const float l, const float r, const float b, const float t, const float zn, const float zf);
		static inline Matrix4f	OrthoOffCenterRH(const float l, const float r, const float b, const float t, const float zn, const float zf);

		static inline Matrix4f	RotationXMatrix(float roll);
		static inline Matrix4f	RotationYMatrix(float pitch);
		static inline Matrix4f	RotationZMatrix(float yaw);

		static inline Matrix4f	TranslationMatrix(const Vector3f& trans);
		static inline Matrix4f	ScaleMatrix(const Vector3f& scale);
		static inline Matrix4f	ScaleTranslationMatrix(const Vector3f& scale, const Vector3f& trans);
		static inline Matrix4f	QuaternionTranslationMatrix(const Quaternion& quat, const Vector3f& trans);

		static Matrix4f			RotationMatrix(const Vector3f& eular);
		static Matrix4f			RotationMatrix(const Rotator& rotator);
		static Matrix4f			ScaleRotationMatrix(const Vector3f& scale, const Rotator& rotator);
		static Matrix4f			ScaleRotationTranslationMatrix(const Vector3f& scale, const Rotator& rotator, const Vector3f& trans);
		static Matrix4f			RotationNormalMatrix(Vector3f normalAxis, float fAngle);
	};
}

#include "sgfMatrix.inl"