#include "sgfRotator.h"
#include "sgfQuaternion.h"
namespace sgf
{ 
	template<typename T>
	INLINE T& TMatrix44<T>::operator()(const int32 a_row, const int32 a_col)
	{
		return f[4 * a_row + a_col];
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE const T& 
		TMatrix44<T>::operator()(const int32 a_row, const int32 a_col) const
	{
		return f[4 * a_row + a_col];
	}
	
	//-------------------------------------------------------------------------
	template<typename T>
	INLINE T* 
		TMatrix44<T>::operator[](const int32 a_row)
	{
		return m[a_row];
	}
	
	//-------------------------------------------------------------------------
	template<typename T>
	INLINE const T* 
		TMatrix44<T>::operator[](const int32 a_row) const
	{
		return m[a_row];
	}
	
	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TMatrix44<T>& 
		TMatrix44<T>::operator+=(const TMatrix44<T>& a_rhs)
	{
		for (int32 i = 0; i < 16; i++)
		{
			f[i] += a_rhs.f[i];
		}
		return *this;
	}
	
	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TMatrix44<T> 
		TMatrix44<T>::operator+(const TMatrix44<T>& a_rhs) const
	{
		TMatrix44<T> ret(*this);
		ret += a_rhs;
		return ret;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TMatrix44<T>& 
		TMatrix44<T>::operator-=(const TMatrix44<T>& a_rhs)
	{
		for (int i = 0; i < 16; i++)
		{
			f[i] -= a_rhs.f[i];
		}
		return *this;
	}
	
	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TMatrix44<T> 
		TMatrix44<T>::operator-(const TMatrix44<T>& a_rhs) const
	{
		TMatrix44<T> ret(*this);
		ret -= a_rhs;
		return ret;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TMatrix44<T>& 
		TMatrix44<T>::operator*=(const T a_val)
	{
		for (int i = 0; i < 16; i++)
		{
			f[i] *= a_val;
		}
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TMatrix44<T> 
		TMatrix44<T>::operator*(const T a_val) const
	{
		TMatrix44<T> ret(*this);
		ret *= a_val;
		return ret;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TMatrix44<T>& 
		TMatrix44<T>::operator/=(const T a_val)
	{
		for (int i = 0; i < 16; i++)
		{
			f[i] /= a_val;
		}
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TMatrix44<T> 
		TMatrix44<T>::operator/(const T a_val) const
	{
		TMatrix44<T> ret(*this);
		ret /= a_val;
		return ret;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE bool 
		TMatrix44<T>::operator==(const TMatrix44<T>& a_rhs) const
	{
		return MemCmp(this, &a_rhs, sizeof(a_rhs)) == 0;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE bool 
		TMatrix44<T>::operator!=(const TMatrix44<T>& a_rhs) const
	{
		return !((*this)==a_rhs );
	}

	//----------------------------------------
	//////////////////////////////////////////
	//Matrix4f
	//////////////////////////////////////////
	//----------------------------------------
	Matrix4f& 
		Matrix4f::operator*=(const Matrix4f& a_mat)
	{
		Multiply(*this, *this, a_mat);
		return *this;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::operator*(const Matrix4f& a_mat) const
	{
		Matrix4f ret;
		ret *= a_mat;
		return ret;
	}

	//----------------------------------------
	bool 
		Matrix4f::Equals(const Matrix4f& a_mat, float a_fTolerance /*= kKindaSmallNumber*/) const
	{
		for (int32 i = 0; i < 16; ++i)
		{
			if (MathAbs(f[i] - a_mat.f[i]) > a_fTolerance)
			{
				return false;
			}
		}
		return true;
	}

	//----------------------------------------
	void 
		Matrix4f::SetIdentity()
	{
		*this = Matrix4f::Identity();
	}

	//----------------------------------------
	Vector3f 
		Matrix4f::TransformNormal(const Vector3f& a_v) const
	{
		Vector3f vOut;
		vOut.x = a_v.x * f[0] + a_v.y * f[4] + a_v.z * f[8];
		vOut.y = a_v.x * f[1] + a_v.y * f[5] + a_v.z * f[9];
		vOut.z = a_v.x * f[2] + a_v.y * f[6] + a_v.z * f[10];
		return vOut;
	}

	//----------------------------------------
	Vector3f 
		Matrix4f::TransformVector(const Vector3f& a_v) const
	{
		Vector3f vOut;
		vOut.x = a_v.x * f[0] + a_v.y * f[4] + a_v.z * f[8] + f[12];
		vOut.y = a_v.x * f[1] + a_v.y * f[5] + a_v.z * f[9] + f[13];
		vOut.z = a_v.x * f[2] + a_v.y * f[6] + a_v.z * f[10] + f[14];
		return vOut;
	}

	//----------------------------------------
	void 
		Matrix4f::TransformVector(float a_fx, float a_fy, float a_fz, float& out_fx, float& out_fy, float& out_fz) const
	{
		out_fx = a_fx * f[0] + a_fy * f[4] + a_fz * f[8] + f[12];
		out_fy = a_fx * f[1] + a_fy * f[5] + a_fz * f[9] + f[13];
		out_fz = a_fx * f[2] + a_fy * f[6] + a_fz * f[10] + f[14];
	}

	//----------------------------------------
	float 
		Matrix4f::Determinant() const
	{
		return	m[0][0] * (
			m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
			m[2][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) +
			m[3][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2])
			) -
			m[1][0] * (
				m[0][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
				m[2][1] * (m[0][2] * m[3][3] - m[0][3] * m[3][2]) +
				m[3][1] * (m[0][2] * m[2][3] - m[0][3] * m[2][2])
				) +
			m[2][0] * (
				m[0][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) -
				m[1][1] * (m[0][2] * m[3][3] - m[0][3] * m[3][2]) +
				m[3][1] * (m[0][2] * m[1][3] - m[0][3] * m[1][2])
				) -
			m[3][0] * (
				m[0][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) -
				m[1][1] * (m[0][2] * m[2][3] - m[0][3] * m[2][2]) +
				m[2][1] * (m[0][2] * m[1][3] - m[0][3] * m[1][2])
				);
	}

	//----------------------------------------
	Vector3f 
		Matrix4f::GetAxis(int32 a_nIdx) const
	{
		return Vector3f(m[a_nIdx][0], m[a_nIdx][1], m[a_nIdx][2]);
	}

	//----------------------------------------
	Vector3f
		Matrix4f::GetTranslate() const
	{
		return Vector3f(m[3][0], m[3][1], m[3][2]);
	}

	//----------------------------------------
	void 
		Matrix4f::SetTranslate(const Vector3f& a_v)
	{
		m[3][0] = a_v.x;
		m[3][1] = a_v.y;
		m[3][2] = a_v.z;
	}

	//----------------------------------------
	Vector3f 
		Matrix4f::GetScale() const
	{
		if (
			MathNearlyZero(f[1]) && MathNearlyZero(f[2]) &&
			MathNearlyZero(f[4]) && MathNearlyZero(f[6]) &&
			MathNearlyZero(f[8]) && MathNearlyZero(f[9])
			)
		{
			return Vector3f(MathAbs(f[0]), MathAbs(f[5]), MathAbs(f[10]));
		}

		// We have to do the full calculation.
		return Vector3f(
			MathSqrt(f[0] * f[0] + f[1] * f[1] + f[2] * f[2]),
			MathSqrt(f[4] * f[4] + f[5] * f[5] + f[6] * f[6]),
			MathSqrt(f[8] * f[8] + f[9] * f[9] + f[10] * f[10])
		);
	}

	//----------------------------------------
	void 
		Matrix4f::SetScale(const Vector3f& a_vScale)
	{
		*this = ScaleRotationTranslationMatrix(a_vScale, Rotator::FromMatrix(*this), GetTranslate());
	}

	//----------------------------------------
	bool 
		Matrix4f::Decompose(Vector3f* out_vScale, Quaternion* out_quat, Vector3f* out_vTrans)
	{
		Matrix4f kQ = Matrix4f::Identity();

		float fInvLength = m[0][0] * m[0][0] + m[0][1] * m[0][1] + m[0][2] * m[0][2];
		if (fInvLength != 0) fInvLength = 1 / (float)sqrt(fInvLength);

		kQ.m[0][0] = m[0][0] * fInvLength;
		kQ.m[0][1] = m[0][1] * fInvLength;
		kQ.m[0][2] = m[0][2] * fInvLength;

		float fDot = kQ[0][0] * m[1][0] + kQ[0][1] * m[1][1] + kQ[0][2] * m[1][2];

		kQ.m[1][0] = m[1][0] - fDot*kQ.m[0][0];
		kQ.m[1][1] = m[1][1] - fDot*kQ.m[0][1];
		kQ.m[1][2] = m[1][2] - fDot*kQ.m[0][2];

		fInvLength = kQ.m[1][0] * kQ.m[1][0] + kQ.m[1][1] * kQ.m[1][1] + kQ.m[1][2] * kQ.m[1][2];
		if (fInvLength != 0) fInvLength = 1 / (float)sqrt(fInvLength);

		kQ.m[1][0] *= fInvLength;
		kQ.m[1][1] *= fInvLength;
		kQ.m[1][2] *= fInvLength;

		fDot = kQ.m[0][0] * m[0][2] + kQ.m[1][0] * m[1][2] + kQ.m[2][0] * m[2][2];
		kQ.m[2][0] = m[2][0] - fDot*kQ.m[0][0];
		kQ.m[2][1] = m[2][1] - fDot*kQ.m[0][1];
		kQ.m[2][2] = m[2][2] - fDot*kQ.m[0][2];
		fDot = kQ.m[1][0] * m[2][0] + kQ.m[1][1] * m[2][1] + kQ.m[1][2] * m[2][2];

		kQ.m[2][0] -= fDot*kQ.m[1][0];
		kQ.m[2][1] -= fDot*kQ.m[1][1];
		kQ.m[2][2] -= fDot*kQ.m[1][2];
		fInvLength = kQ.m[2][0] * kQ.m[2][0] + kQ.m[2][1] * kQ.m[2][1] + kQ.m[2][2] * kQ.m[2][2];
		if (fInvLength != 0) fInvLength = 1 / (float)sqrt(fInvLength);

		kQ.m[2][0] *= fInvLength;
		kQ.m[2][1] *= fInvLength;
		kQ.m[2][2] *= fInvLength;

		// guarantee that orthogonal matrix has determinant 1 (no reflections)
		float fDet = kQ.m[0][0] * kQ.m[1][1] * kQ.m[2][2] + kQ.m[1][0] * kQ.m[2][1] * kQ.m[0][2] +
			kQ.m[2][0] * kQ.m[0][1] * kQ.m[1][2] - kQ.m[2][0] * kQ.m[1][1] * kQ.m[0][2] -
			kQ.m[1][0] * kQ.m[0][1] * kQ.m[2][2] - kQ.m[0][0] * kQ.m[2][1] * kQ.m[1][2];

		if (fDet < 0.0)
		{
			for (size_t iRow = 0; iRow < 3; iRow++)
				for (size_t iCol = 0; iCol < 3; iCol++)
					kQ.m[iCol][iRow] = -kQ.m[iCol][iRow];
		}

		// build "right" matrix R
		Matrix4f kR;
		kR.m[0][0] = kQ.m[0][0] * m[0][0] + kQ.m[0][1] * m[0][1] +
			kQ.m[0][2] * m[0][2];
		kR.m[1][0] = kQ.m[0][0] * m[1][0] + kQ.m[0][1] * m[1][1] +
			kQ.m[0][2] * m[1][2];
		kR.m[1][1] = kQ.m[1][0] * m[1][0] + kQ.m[1][1] * m[1][1] +
			kQ.m[1][2] * m[1][2];
		kR.m[2][0] = kQ.m[0][0] * m[2][0] + kQ.m[0][1] * m[2][1] +
			kQ.m[0][2] * m[2][2];
		kR.m[2][1] = kQ.m[1][0] * m[2][0] + kQ.m[1][1] * m[2][1] +
			kQ.m[1][2] * m[2][2];
		kR.m[2][2] = kQ.m[2][0] * m[2][0] + kQ.m[2][1] * m[2][1] +
			kQ.m[2][2] * m[2][2];

		// the scaling component
		out_vScale->f[0] = kR.m[0][0];
		out_vScale->f[1] = kR.m[1][1];
		out_vScale->f[2] = kR.m[2][2];

		out_vTrans->f[0] = m[3][0];
		out_vTrans->f[1] = m[3][1];
		out_vTrans->f[2] = m[3][2];
		// 	// the shear component
		// 	float fInvD0 = 1.0f/kD->f[0];
		// 	kU->f[0] = kR.m[1][0]*fInvD0;
		// 	kU->f[1] = kR.m[2][0]*fInvD0;
		// 	kU->f[2] = kR.m[2][1]/kD->f[1];

		*out_quat = Quaternion::FromMatrix(kQ);
		return true;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::Transpose() const
	{
		Matrix4f	mTmp;

		mTmp.f[0] = f[0];	mTmp.f[4] = f[1];	mTmp.f[8] = f[2];	mTmp.f[12] = f[3];
		mTmp.f[1] = f[4];	mTmp.f[5] = f[5];	mTmp.f[9] = f[6];	mTmp.f[13] = f[7];
		mTmp.f[2] = f[8];	mTmp.f[6] = f[9];	mTmp.f[10] = f[10];	mTmp.f[14] = f[11];
		mTmp.f[3] = f[12];	mTmp.f[7] = f[13];	mTmp.f[11] = f[14];	mTmp.f[15] = f[15];

		return mTmp;
	}

	//----------------------------------------
	Matrix4f& 
		Matrix4f::TransposeSelf()
	{
		*this = Transpose();
		return *this;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::Inverse() const
	{
		float det[4];
		Matrix4f matTmp;
		Matrix4f matResult;

		matTmp.m[0][0] = m[2][2] * m[3][3] - m[2][3] * m[3][2];
		matTmp.m[0][1] = m[1][2] * m[3][3] - m[1][3] * m[3][2];
		matTmp.m[0][2] = m[1][2] * m[2][3] - m[1][3] * m[2][2];

		matTmp.m[1][0] = m[2][2] * m[3][3] - m[2][3] * m[3][2];
		matTmp.m[1][1] = m[0][2] * m[3][3] - m[0][3] * m[3][2];
		matTmp.m[1][2] = m[0][2] * m[2][3] - m[0][3] * m[2][2];

		matTmp.m[2][0] = m[1][2] * m[3][3] - m[1][3] * m[3][2];
		matTmp.m[2][1] = m[0][2] * m[3][3] - m[0][3] * m[3][2];
		matTmp.m[2][2] = m[0][2] * m[1][3] - m[0][3] * m[1][2];

		matTmp.m[3][0] = m[1][2] * m[2][3] - m[1][3] * m[2][2];
		matTmp.m[3][1] = m[0][2] * m[2][3] - m[0][3] * m[2][2];
		matTmp.m[3][2] = m[0][2] * m[1][3] - m[0][3] * m[1][2];

		det[0] = m[1][1] * matTmp.m[0][0] - m[2][1] * matTmp.m[0][1] + m[3][1] * matTmp.m[0][2];
		det[1] = m[0][1] * matTmp.m[1][0] - m[2][1] * matTmp.m[1][1] + m[3][1] * matTmp.m[1][2];
		det[2] = m[0][1] * matTmp.m[2][0] - m[1][1] * matTmp.m[2][1] + m[3][1] * matTmp.m[2][2];
		det[3] = m[0][1] * matTmp.m[3][0] - m[1][1] * matTmp.m[3][1] + m[2][1] * matTmp.m[3][2];

		float fDeterminant = m[0][0] * det[0] - m[1][0] * det[1] + m[2][0] * det[2] - m[3][0] * det[3];
		const float	fDet = 1.0f / fDeterminant;

		matResult.m[0][0] = fDet * det[0];
		matResult.m[0][1] = -fDet * det[1];
		matResult.m[0][2] = fDet * det[2];
		matResult.m[0][3] = -fDet * det[3];
		matResult.m[1][0] = -fDet * (m[1][0] * matTmp.m[0][0] - m[2][0] * matTmp.m[0][1] + m[3][0] * matTmp.m[0][2]);
		matResult.m[1][1] = fDet * (m[0][0] * matTmp.m[1][0] - m[2][0] * matTmp.m[1][1] + m[3][0] * matTmp.m[1][2]);
		matResult.m[1][2] = -fDet * (m[0][0] * matTmp.m[2][0] - m[1][0] * matTmp.m[2][1] + m[3][0] * matTmp.m[2][2]);
		matResult.m[1][3] = fDet * (m[0][0] * matTmp.m[3][0] - m[1][0] * matTmp.m[3][1] + m[2][0] * matTmp.m[3][2]);
		matResult.m[2][0] = fDet * (
			m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) -
			m[2][0] * (m[1][1] * m[3][3] - m[1][3] * m[3][1]) +
			m[3][0] * (m[1][1] * m[2][3] - m[1][3] * m[2][1])
			);
		matResult.m[2][1] = -fDet * (
			m[0][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) -
			m[2][0] * (m[0][1] * m[3][3] - m[0][3] * m[3][1]) +
			m[3][0] * (m[0][1] * m[2][3] - m[0][3] * m[2][1])
			);
		matResult.m[2][2] = fDet * (
			m[0][0] * (m[1][1] * m[3][3] - m[1][3] * m[3][1]) -
			m[1][0] * (m[0][1] * m[3][3] - m[0][3] * m[3][1]) +
			m[3][0] * (m[0][1] * m[1][3] - m[0][3] * m[1][1])
			);
		matResult.m[2][3] = -fDet * (
			m[0][0] * (m[1][1] * m[2][3] - m[1][3] * m[2][1]) -
			m[1][0] * (m[0][1] * m[2][3] - m[0][3] * m[2][1]) +
			m[2][0] * (m[0][1] * m[1][3] - m[0][3] * m[1][1])
			);
		matResult.m[3][0] = -fDet * (
			m[1][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) -
			m[2][0] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]) +
			m[3][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
			);
		matResult.m[3][1] = fDet * (
			m[0][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) -
			m[2][0] * (m[0][1] * m[3][2] - m[0][2] * m[3][1]) +
			m[3][0] * (m[0][1] * m[2][2] - m[0][2] * m[2][1])
			);
		matResult.m[3][2] = -fDet * (
			m[0][0] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]) -
			m[1][0] * (m[0][1] * m[3][2] - m[0][2] * m[3][1]) +
			m[3][0] * (m[0][1] * m[1][2] - m[0][2] * m[1][1])
			);
		matResult.m[3][3] = fDet * (
			m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
			m[1][0] * (m[0][1] * m[2][2] - m[0][2] * m[2][1]) +
			m[2][0] * (m[0][1] * m[1][2] - m[0][2] * m[1][1])
			);

		return matResult;
	}

	//----------------------------------------
	Matrix4f& 
		Matrix4f::InverseSelf()
	{
		*this = Inverse();
		return *this;
	}

	//----------------------------------------
	const Matrix4f& 
		Matrix4f::Identity()
	{
		return Matrix4f::kIdentity;
	}

	//----------------------------------------
	void 
		Matrix4f::Multiply(Matrix4f& out_mat, const Matrix4f& a_matA, const Matrix4f& a_matB)
	{
		Matrix4f mRet;

		/* Perform calculation on a dummy matrix (mRet) */
		mRet.f[0] = a_matA.f[0] * a_matB.f[0] + a_matA.f[1] * a_matB.f[4] + a_matA.f[2] * a_matB.f[8] + a_matA.f[3] * a_matB.f[12];
		mRet.f[1] = a_matA.f[0] * a_matB.f[1] + a_matA.f[1] * a_matB.f[5] + a_matA.f[2] * a_matB.f[9] + a_matA.f[3] * a_matB.f[13];
		mRet.f[2] = a_matA.f[0] * a_matB.f[2] + a_matA.f[1] * a_matB.f[6] + a_matA.f[2] * a_matB.f[10] + a_matA.f[3] * a_matB.f[14];
		mRet.f[3] = a_matA.f[0] * a_matB.f[3] + a_matA.f[1] * a_matB.f[7] + a_matA.f[2] * a_matB.f[11] + a_matA.f[3] * a_matB.f[15];

		mRet.f[4] = a_matA.f[4] * a_matB.f[0] + a_matA.f[5] * a_matB.f[4] + a_matA.f[6] * a_matB.f[8] + a_matA.f[7] * a_matB.f[12];
		mRet.f[5] = a_matA.f[4] * a_matB.f[1] + a_matA.f[5] * a_matB.f[5] + a_matA.f[6] * a_matB.f[9] + a_matA.f[7] * a_matB.f[13];
		mRet.f[6] = a_matA.f[4] * a_matB.f[2] + a_matA.f[5] * a_matB.f[6] + a_matA.f[6] * a_matB.f[10] + a_matA.f[7] * a_matB.f[14];
		mRet.f[7] = a_matA.f[4] * a_matB.f[3] + a_matA.f[5] * a_matB.f[7] + a_matA.f[6] * a_matB.f[11] + a_matA.f[7] * a_matB.f[15];

		mRet.f[8] = a_matA.f[8] * a_matB.f[0] + a_matA.f[9] * a_matB.f[4] + a_matA.f[10] * a_matB.f[8] + a_matA.f[11] * a_matB.f[12];
		mRet.f[9] = a_matA.f[8] * a_matB.f[1] + a_matA.f[9] * a_matB.f[5] + a_matA.f[10] * a_matB.f[9] + a_matA.f[11] * a_matB.f[13];
		mRet.f[10] = a_matA.f[8] * a_matB.f[2] + a_matA.f[9] * a_matB.f[6] + a_matA.f[10] * a_matB.f[10] + a_matA.f[11] * a_matB.f[14];
		mRet.f[11] = a_matA.f[8] * a_matB.f[3] + a_matA.f[9] * a_matB.f[7] + a_matA.f[10] * a_matB.f[11] + a_matA.f[11] * a_matB.f[15];

		mRet.f[12] = a_matA.f[12] * a_matB.f[0] + a_matA.f[13] * a_matB.f[4] + a_matA.f[14] * a_matB.f[8] + a_matA.f[15] * a_matB.f[12];
		mRet.f[13] = a_matA.f[12] * a_matB.f[1] + a_matA.f[13] * a_matB.f[5] + a_matA.f[14] * a_matB.f[9] + a_matA.f[15] * a_matB.f[13];
		mRet.f[14] = a_matA.f[12] * a_matB.f[2] + a_matA.f[13] * a_matB.f[6] + a_matA.f[14] * a_matB.f[10] + a_matA.f[15] * a_matB.f[14];
		mRet.f[15] = a_matA.f[12] * a_matB.f[3] + a_matA.f[13] * a_matB.f[7] + a_matA.f[14] * a_matB.f[11] + a_matA.f[15] * a_matB.f[15];

		/* Copy result to mOut */
		out_mat = mRet;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::LookAtLH(const Vector3f& a_vEye, const Vector3f& a_vAt, const Vector3f& a_vUp)
	{
		Vector3f zaxis = a_vAt - a_vEye;
		zaxis.Normalize();

		Vector3f xaxis = a_vUp.cross(zaxis);
		xaxis.Normalize();

		Vector3f yaxis = zaxis.cross(xaxis);

		Matrix4f mOut;
		mOut.f[0] = xaxis.x;
		mOut.f[1] = yaxis.x;
		mOut.f[2] = zaxis.x;
		mOut.f[3] = 0;

		mOut.f[4] = xaxis.y;
		mOut.f[5] = yaxis.y;
		mOut.f[6] = zaxis.y;
		mOut.f[7] = 0;

		mOut.f[8] = xaxis.z;
		mOut.f[9] = yaxis.z;
		mOut.f[10] = zaxis.z;
		mOut.f[11] = 0;

		mOut.f[12] = -xaxis.dot(a_vEye);
		mOut.f[13] = -yaxis.dot(a_vEye);
		mOut.f[14] = -zaxis.dot(a_vEye);
		mOut.f[15] = 1;
		return mOut;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::LookAtRH(const Vector3f& a_vEye, const Vector3f& a_vAt, const Vector3f& a_vUp)
	{
		Vector3f zaxis = a_vEye - a_vAt;
		zaxis.Normalize();

		Vector3f xaxis = a_vUp.cross(zaxis);
		xaxis.Normalize();

		Vector3f yaxis = zaxis.cross(xaxis);

		Matrix4f mOut;
		mOut.f[0] = xaxis.x;
		mOut.f[1] = yaxis.x;
		mOut.f[2] = zaxis.x;
		mOut.f[3] = 0;

		mOut.f[4] = xaxis.y;
		mOut.f[5] = yaxis.y;
		mOut.f[6] = zaxis.y;
		mOut.f[7] = 0;

		mOut.f[8] = xaxis.z;
		mOut.f[9] = yaxis.z;
		mOut.f[10] = zaxis.z;
		mOut.f[11] = 0;

		mOut.f[12] = -xaxis.dot(a_vEye);
		mOut.f[13] = -yaxis.dot(a_vEye);
		mOut.f[14] = -zaxis.dot(a_vEye);
		mOut.f[15] = 1;
		return mOut;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::PerspectiveFovLH(const float a_fFov, const float a_fAspect, const float a_fZNear, const float a_fZFar)
	{
		Matrix4f mOut;
		float f, n, fRealAspect;

		fRealAspect = a_fAspect;

		// cotangent(a) == 1.0f / tan(a);
		f = 1.0f / (float)tanf(a_fFov * 0.5f);
		n = 1.0f / (a_fZFar - a_fZNear);

		mOut.f[0] = f / fRealAspect;
		mOut.f[1] = 0;
		mOut.f[2] = 0;
		mOut.f[3] = 0;

		mOut.f[4] = 0;
		mOut.f[5] = f;
		mOut.f[6] = 0;
		mOut.f[7] = 0;

		mOut.f[8] = 0;
		mOut.f[9] = 0;
		mOut.f[10] = a_fZFar * n;
		mOut.f[11] = 1;

		mOut.f[12] = 0;
		mOut.f[13] = 0;
		mOut.f[14] = -a_fZFar * a_fZNear * n;
		mOut.f[15] = 0;

		return mOut;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::PerspectiveFovRH(const float a_fFov, const float a_fAspect, const float a_fZNear, const float a_fZFar)
	{
		Matrix4f mOut;
		float f, n, fRealAspect;
		fRealAspect = a_fAspect;

		// cotangent(a) == 1.0f / tan(a);
		f = 1.0f / (float)tanf(a_fFov * 0.5f);
		n = 1.0f / (a_fZNear - a_fZFar);

		mOut.f[0] = f / fRealAspect;
		mOut.f[1] = 0;
		mOut.f[2] = 0;
		mOut.f[3] = 0;

		mOut.f[4] = 0;
		mOut.f[5] = f;
		mOut.f[6] = 0;
		mOut.f[7] = 0;

		mOut.f[8] = 0;
		mOut.f[9] = 0;
		mOut.f[10] = (a_fZFar + a_fZNear) * n;
		mOut.f[11] = -1;

		mOut.f[12] = 0;
		mOut.f[13] = 0;
		mOut.f[14] = (2 * a_fZFar * a_fZNear) * n;
		mOut.f[15] = 0;

		return mOut;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::PerspectiveLH(const float a_fWidth, const float a_fHeight, const float a_fZNear, const float a_fZFar)
	{
		Matrix4f mOut;
		return mOut;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::PerspectiveRH(const float a_fWidth, const float a_fHeight, const float a_fZNear, const float a_fZFar)
	{
		Matrix4f mOut;
		return mOut;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::OrthoLH(const float a_fWidth, const float a_fHeight, const float a_fZNear, const float a_fZFar)
	{
		Matrix4f mOut;
		mOut.f[0] = 2 / a_fWidth;
		mOut.f[1] = 0;
		mOut.f[2] = 0;
		mOut.f[3] = 0;

		mOut.f[4] = 0;
		mOut.f[5] = 2 / a_fHeight;
		mOut.f[6] = 0;
		mOut.f[7] = 0;

		mOut.f[8] = 0;
		mOut.f[9] = 0;
		mOut.f[10] = 1 / (a_fZFar - a_fZNear);
		mOut.f[11] = 0;

		mOut.f[12] = 0;
		mOut.f[13] = 0;
		mOut.f[14] = a_fZNear / (a_fZNear - a_fZFar);
		mOut.f[15] = 1;

		return mOut;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::OrthoRH(const float a_fWidth, const float a_fHeight, const float a_fZNear, const float a_fZFar)
	{
		Matrix4f mOut;
		mOut.f[0] = 2 / a_fWidth;
		mOut.f[1] = 0;
		mOut.f[2] = 0;
		mOut.f[3] = 0;

		mOut.f[4] = 0;
		mOut.f[5] = 2 / a_fHeight;
		mOut.f[6] = 0;
		mOut.f[7] = 0;

		mOut.f[8] = 0;
		mOut.f[9] = 0;
		mOut.f[10] = 1 / (a_fZNear - a_fZFar);
		mOut.f[11] = 0;

		mOut.f[12] = 0;
		mOut.f[13] = 0;
		mOut.f[14] = a_fZNear / (a_fZNear - a_fZFar);
		mOut.f[15] = 1;

		return mOut;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::OrthoOffCenterLH(const float a_fLeft, const float a_fRight, const float a_fBottom, const float a_fTop, const float a_fZNear, const float a_fZFar)
	{
		Matrix4f mOut;
		mOut.f[0] = 2 / (a_fRight - a_fLeft);
		mOut.f[1] = 0;
		mOut.f[2] = 0;
		mOut.f[3] = 0;

		mOut.f[4] = 0;
		mOut.f[5] = 2 / (a_fTop - a_fBottom);
		mOut.f[6] = 0;
		mOut.f[7] = 0;

		mOut.f[8] = 0;
		mOut.f[9] = 0;
		mOut.f[10] = 1 / (a_fZFar - a_fZNear);
		mOut.f[11] = 0;

		mOut.f[12] = (a_fLeft + a_fRight) / (a_fLeft - a_fRight);
		mOut.f[13] = (a_fTop + a_fBottom) / (a_fBottom - a_fTop);
		mOut.f[14] = a_fZNear / (a_fZNear - a_fZFar);
		mOut.f[15] = 1;

		return mOut;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::OrthoOffCenterRH(const float a_fLeft, const float a_fRight, const float a_fBottom, const float a_fTop, const float a_fZNear, const float a_fZFar)
	{
		Matrix4f mOut;
		mOut.f[0] = 2 / (a_fRight - a_fLeft);
		mOut.f[1] = 0;
		mOut.f[2] = 0;
		mOut.f[3] = 0;

		mOut.f[4] = 0;
		mOut.f[5] = 2 / (a_fTop - a_fBottom);
		mOut.f[6] = 0;
		mOut.f[7] = 0;

		mOut.f[8] = 0;
		mOut.f[9] = 0;
		mOut.f[10] = 1 / (a_fZNear - a_fZFar);
		mOut.f[11] = 0;

		mOut.f[12] = (a_fLeft + a_fRight) / (a_fLeft - a_fRight);
		mOut.f[13] = (a_fTop + a_fBottom) / (a_fBottom - a_fTop);
		mOut.f[14] = a_fZNear / (a_fZNear - a_fZFar);
		mOut.f[15] = 1;

		return mOut;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::RotationXMatrix(float a_fRoll)
	{
		Matrix4f		mOut;
		float		fCosine, fSine;

		fCosine = (float)MathCosFloat(a_fRoll);
		fSine = (float)MathSinFloat(a_fRoll);

		/* Create the trigonometric matrix corresponding to X Rotation */
		mOut.f[0] = 1.0f;	mOut.f[4] = 0.0f;	mOut.f[8] = 0.0f;	mOut.f[12] = 0.0f;
		mOut.f[1] = 0.0f;	mOut.f[5] = fCosine;	mOut.f[9] = fSine;	mOut.f[13] = 0.0f;
		mOut.f[2] = 0.0f;	mOut.f[6] = -fSine;	mOut.f[10] = fCosine;	mOut.f[14] = 0.0f;
		mOut.f[3] = 0.0f;	mOut.f[7] = 0.0f;	mOut.f[11] = 0.0f;	mOut.f[15] = 1.0f;
		return mOut;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::RotationYMatrix(float a_fPitch)
	{
		Matrix4f		mOut;
		float		fCosine, fSine;

		/* Precompute cos and sin */
		fCosine = (float)cosf(a_fPitch);
		fSine = (float)sinf(a_fPitch);

		/* Create the trigonometric matrix corresponding to Y Rotation */
		mOut.f[0] = fCosine;		mOut.f[4] = 0.0f;	mOut.f[8] = -fSine;		mOut.f[12] = 0.0f;
		mOut.f[1] = 0.0f;		mOut.f[5] = 1.0f;	mOut.f[9] = 0.0f;		mOut.f[13] = 0.0f;
		mOut.f[2] = fSine;		mOut.f[6] = 0.0f;	mOut.f[10] = fCosine;		mOut.f[14] = 0.0f;
		mOut.f[3] = 0.0f;		mOut.f[7] = 0.0f;	mOut.f[11] = 0.0f;		mOut.f[15] = 1.0f;

		return mOut;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::RotationZMatrix(float a_fYaw)
	{
		Matrix4f		mOut;
		float		fCosine, fSine;

		/* Precompute cos and sin */
		fCosine = (float)cosf(a_fYaw);
		fSine = (float)sinf(a_fYaw);

		/* Create the trigonometric matrix corresponding to Z Rotation */
		mOut.f[0] = fCosine;		mOut.f[4] = -fSine;	mOut.f[8] = 0.0f;	mOut.f[12] = 0.0f;
		mOut.f[1] = fSine;		mOut.f[5] = fCosine;	mOut.f[9] = 0.0f;	mOut.f[13] = 0.0f;
		mOut.f[2] = 0.0f;		mOut.f[6] = 0.0f;	mOut.f[10] = 1.0f;	mOut.f[14] = 0.0f;
		mOut.f[3] = 0.0f;		mOut.f[7] = 0.0f;	mOut.f[11] = 0.0f;	mOut.f[15] = 1.0f;

		return mOut;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::TranslationMatrix(const Vector3f& a_vTrans)
	{
		Matrix4f mOut;

		mOut.f[0] = 1.0f;	mOut.f[4] = 0.0f;	mOut.f[8] = 0.0f;	mOut.f[12] = a_vTrans.x;
		mOut.f[1] = 0.0f;	mOut.f[5] = 1.0f;	mOut.f[9] = 0.0f;	mOut.f[13] = a_vTrans.y;
		mOut.f[2] = 0.0f;	mOut.f[6] = 0.0f;	mOut.f[10] = 1.0f;	mOut.f[14] = a_vTrans.z;
		mOut.f[3] = 0.0f;	mOut.f[7] = 0.0f;	mOut.f[11] = 0.0f;	mOut.f[15] = 1.0f;

		return mOut;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::ScaleMatrix(const Vector3f& a_vScale)
	{
		Matrix4f mOut;

		mOut.f[0] = a_vScale.x;	mOut.f[4] = 0.0f;	mOut.f[8] = 0.0f;	mOut.f[12] = 0.0f;
		mOut.f[1] = 0.0f;	mOut.f[5] = a_vScale.y;	mOut.f[9] = 0.0f;	mOut.f[13] = 0.0f;
		mOut.f[2] = 0.0f;	mOut.f[6] = 0.0f;	mOut.f[10] = a_vScale.z;	mOut.f[14] = 0.0f;
		mOut.f[3] = 0.0f;	mOut.f[7] = 0.0f;	mOut.f[11] = 0.0f;	mOut.f[15] = 1.0f;

		return mOut;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::ScaleTranslationMatrix(const Vector3f& a_vScale, const Vector3f& a_vTrans)
	{
		Matrix4f mOut;

		mOut.f[0] = a_vScale.x;	mOut.f[4] = 0.0f;	mOut.f[8] = 0.0f;	mOut.f[12] = a_vTrans.x;
		mOut.f[1] = 0.0f;	mOut.f[5] = a_vScale.y;	mOut.f[9] = 0.0f;	mOut.f[13] = a_vTrans.y;
		mOut.f[2] = 0.0f;	mOut.f[6] = 0.0f;	mOut.f[10] = a_vScale.z;	mOut.f[14] = a_vTrans.z;
		mOut.f[3] = 0.0f;	mOut.f[7] = 0.0f;	mOut.f[11] = 0.0f;	mOut.f[15] = 1.0f;

		return mOut;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::QuaternionTranslationMatrix(const Quaternion& a_quat, const Vector3f& a_vTrans)
	{
		Matrix4f mOut = a_quat.ToRotationMatrix();
		mOut._41 = a_vTrans.x;
		mOut._42 = a_vTrans.y;
		mOut._43 = a_vTrans.z;
		return mOut;
	}

	
}