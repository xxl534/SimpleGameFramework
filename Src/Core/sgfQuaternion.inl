#include "sgfMatrix.h"
namespace sgf
{
	//----------------------------------------
	Quaternion& 
		Quaternion::operator*=(const Quaternion& a_rhs)
	{
		*this = Quaternion::Multiply(*this, a_rhs);
		return *this;
	}

	//----------------------------------------
	Quaternion 
		Quaternion::operator*(const Quaternion& a_rhs) const
	{
		Quaternion ret = Multiply(*this, a_rhs);
		return ret;
	}

	//----------------------------------------
	void 
		Quaternion::SetIdentity()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 1;
	}

	//----------------------------------------
	void 
		Quaternion::Normalize()
	{
		float	fMagnitude;
		double	temp;

		/* Compute quaternion magnitude */
		temp = w*w + x*x + y*y + z*z;
		fMagnitude = (float)sqrt(temp);

		/* Divide each quaternion component by this magnitude */
		if (fMagnitude != 0.0f)
		{
			fMagnitude = 1.0f / fMagnitude;
			x *= fMagnitude;
			y *= fMagnitude;
			z *= fMagnitude;
			w *= fMagnitude;
		}
	}

	//----------------------------------------
	Quaternion
		Quaternion::Slerp(const Quaternion& a_qTo, const float a_fWeight) const
	{
		Quaternion qOut;
		float		fCosine, fAngle, A, B;

		/* Parameter checking */
		if (a_fWeight<0.0f || a_fWeight>1.0f)
		{
			//_RPT0(_CRT_WARN, "PVRTMatrixQuaternionSlerp : Bad parameters\n");
			qOut.x = 0;
			qOut.y = 0;
			qOut.z = 0;
			qOut.w = 1;
			return qOut;
		}

		/* Find sine of Angle between Quaternion A and B (dot product between quaternion A and B) */
		fCosine = w*a_qTo.w + x*a_qTo.x + y*a_qTo.y + z*a_qTo.z;

		if (fCosine < 0)
		{
			Quaternion qi;

			/*
			<http://www.magic-software.com/Documentation/Quaternions.pdf>

			"It is important to note that the quaternions q and -q represent
			the same rotation... while either quaternion will do, the
			interpolation methods require choosing one over the other.

			"Although q1 and -q1 represent the same rotation, the values of
			Slerp(a_fWeight; q0, q1) and Slerp(a_fWeight; q0,-q1) are not the same. It is
			customary to choose the sign... on q1 so that... the angle
			between q0 and q1 is acute. This choice avoids extra
			spinning caused by the interpolated rotations."
			*/
			qi.x = -a_qTo.x;
			qi.y = -a_qTo.y;
			qi.z = -a_qTo.z;
			qi.w = -a_qTo.w;

			return Slerp(qi, a_fWeight);
		}

		fCosine = Min(fCosine, 1.0f);
		fAngle = (float)acosf(fCosine);

		/* Avoid a division by zero */
		if (fAngle == 0.0f)
		{
			return *this;
		}

		/* Precompute some values */
		float sangle = 1.0f / sinf(fAngle);
		A = (float)(sinf((1.0f - a_fWeight)*fAngle) * sangle);
		B = (float)(sinf(a_fWeight*fAngle) * sangle);

		/* Compute resulting quaternion */
		qOut.x = A * x + B * a_qTo.x;
		qOut.y = A * y + B * a_qTo.y;
		qOut.z = A * z + B * a_qTo.z;
		qOut.w = A * w + B * a_qTo.w;
		return  qOut;
	}

	//----------------------------------------
	void 
		Quaternion::Blend(const Quaternion& a_qTo, const float a_fWeight)
	{
		float		fCosine, fAngle, A, B;

		/* Parameter checking */
		if (a_fWeight<0.0f || a_fWeight>1.0f)
		{
			//_RPT0(_CRT_WARN, "PVRTMatrixQuaternionSlerp : Bad parameters\n");
			x = 0;
			y = 0;
			z = 0;
			w = 1;
			return;
		}

		/* Find sine of Angle between Quaternion A and B (dot product between quaternion A and B) */
		fCosine = w*a_qTo.w + x*a_qTo.x + y*a_qTo.y + z*a_qTo.z;

		if (fCosine < 0)
		{
			Quaternion qi;

			/*
			<http://www.magic-software.com/Documentation/Quaternions.pdf>

			"It is important to note that the quaternions q and -q represent
			the same rotation... while either quaternion will do, the
			interpolation methods require choosing one over the other.

			"Although q1 and -q1 represent the same rotation, the values of
			Slerp(a_fWeight; q0, q1) and Slerp(a_fWeight; q0,-q1) are not the same. It is
			customary to choose the sign... on q1 so that... the angle
			between q0 and q1 is acute. This choice avoids extra
			spinning caused by the interpolated rotations."
			*/
			qi.x = -a_qTo.x;
			qi.y = -a_qTo.y;
			qi.z = -a_qTo.z;
			qi.w = -a_qTo.w;

			Blend(qi, a_fWeight);
			return;
		}

		fCosine = Min(fCosine, 1.0f);
		fAngle = (float)acosf(fCosine);

		/* Avoid a division by zero */
		if (fAngle == 0.0f)
		{
			return;
		}

		/* Precompute some values */
		float sangle = 1.0f / sinf(fAngle);
		A = (float)(sinf((1.0f - a_fWeight)*fAngle) * sangle);
		B = (float)(sinf(a_fWeight*fAngle) * sangle);

		/* Compute resulting quaternion */
		x = A * x + B * a_qTo.x;
		y = A * y + B * a_qTo.y;
		z = A * z + B * a_qTo.z;
		w = A * w + B * a_qTo.w;
	}

	//----------------------------------------
	Matrix4f 
		Quaternion::ToRotationMatrix() const
	{
		Matrix4f mat;

		const float x2 = x + x;  const float y2 = y + y;  const float z2 = z + z;
		const float xx = x * x2;   const float xy = x * y2;   const float xz = x * z2;
		const float yy = y * y2;   const float yz = y * z2;   const float zz = z * z2;
		const float wx = w * x2;   const float wy = w * y2;   const float wz = w * z2;

		mat[0][0] = 1.0f - (yy + zz);	mat[1][0] = xy - wz;				mat[2][0] = xz + wy;			mat[3][0] = 0;
		mat[0][1] = xy + wz;			mat[1][1] = 1.0f - (xx + zz);		mat[2][1] = yz - wx;			mat[3][1] = 0;
		mat[0][2] = xz - wy;			mat[1][2] = yz + wx;				mat[2][2] = 1.0f - (xx + yy);	mat[3][2] = 0;
		mat[0][3] = 0.0f;				mat[1][3] = 0.0f;					mat[2][3] = 0.0f;				mat[3][3] = 1.0f;

		return mat;
	}

	//----------------------------------------
	void 
		Quaternion::ToRotationAxis(Vector3f& out_vAxis, float& a_fAngle) const
	{
		float	fCosAngle, fSinAngle;
		double	temp;

		/* Compute some values */
		fCosAngle = w;
		temp = 1.0f - fCosAngle*fCosAngle;
		a_fAngle = (float)acosf(fCosAngle)*2.0f;
		fSinAngle = (float)sqrt(temp);

		/* This is to avoid a division by zero */
		if ((float)fabs(fSinAngle) < 0.0005f)
			fSinAngle = 1.0f;

		/* Get axis vector */
		out_vAxis.x = x / fSinAngle;
		out_vAxis.y = y / fSinAngle;
		out_vAxis.z = z / fSinAngle;
	}

	//----------------------------------------
	Quaternion 
		Quaternion::Identity()
	{
		return Quaternion(0, 0, 0, 1);
	}

	//----------------------------------------
	Quaternion 
		Quaternion::RotationAxisX(const float a_fAngle)
	{
		return RotationAxis(Vector3f(1, 0, 0), a_fAngle);
	}

	//----------------------------------------
	Quaternion 
		Quaternion::RotationAxisY(const float a_fAngle)
	{
		return RotationAxis(Vector3f(0, 1, 0), a_fAngle);
	}

	//----------------------------------------
	Quaternion 
		Quaternion::RotationAxisZ(const float a_fAngle)
	{
		return RotationAxis(Vector3f(0, 0, 1), a_fAngle);
	}

	Quaternion Quaternion::RotationAxis(const Vector3f& a_vAxis, const float a_fAngle)
	{
		Quaternion qOut;
		float	fSin, fCos;

		fSin = (float)MathSinFloat(a_fAngle * 0.5f);
		fCos = (float)MathCosFloat(a_fAngle * 0.5f);

		/* Create quaternion */
		qOut.x = a_vAxis.x * fSin;
		qOut.y = a_vAxis.y * fSin;
		qOut.z = a_vAxis.z * fSin;
		qOut.w = fCos;

		/* Normalise it */
		qOut.Normalize();
		return qOut;
	}

	//----------------------------------------
	Quaternion 
		Quaternion::RotationBetween(const Vector3f& a_v1, const Vector3f& a_v2)
	{
		const Vector3f vCross = a_v1.cross(a_v2);
		const float fCrossMag = vCross.Length();

		// See if vectors are parallel or anti-parallel
		if (fCrossMag < MATH_KINDA_SMALL_NUMBER)
		{
			// If these vectors are parallel - just return identity quaternion (ie no rotation).
			const float dot = a_v1.dot(a_v2);
			if (dot > -MATH_KINDA_SMALL_NUMBER)
			{
				return Quaternion::Identity(); // no rotation
			}
			// Exactly opposite..
			else
			{
				// ..rotation by 180 degrees around a vector orthogonal to a_v1 & a_v2
				Vector3f Vec = a_v1.LengthSqr() > a_v2.LengthSqr() ? a_v1 : a_v2;
				Vec.Normalize();

				Vector3f AxisA, AxisB;
				Vec.FindBestAxisVectors(AxisA, AxisB);

				return Quaternion(AxisA.x, AxisA.y, AxisA.z, 0.f); // (axis*sin(pi/2), cos(pi/2)) = (axis, 0)
			}
		}

		// Not parallel, so use normal code
		float angle = asinf(fCrossMag);

		const float dot = a_v1.dot(a_v2);
		if (dot < 0.0f)
		{
			angle = kPI - angle;
		}

		const float sinHalfAng = sinf(0.5f * angle);
		const float cosHalfAng = cosf(0.5f * angle);
		const Vector3f axis = vCross / fCrossMag;

		return Quaternion(
			sinHalfAng * axis.x,
			sinHalfAng * axis.y,
			sinHalfAng * axis.z,
			cosHalfAng);
	}

	//----------------------------------------
	Quaternion
		Quaternion::Multiply(const Quaternion& a_qA, const Quaternion& a_qB)
	{
		Quaternion qOut;
		Vector3f vCrossProduct;

		/* Compute scalar component */
		qOut.w = (a_qB.w*a_qA.w) - (a_qB.x*a_qA.x + a_qB.y*a_qA.y + a_qB.z*a_qA.z);

		/* Compute cross product */
		vCrossProduct.x = a_qB.y*a_qA.z - a_qB.z*a_qA.y;
		vCrossProduct.y = a_qB.z*a_qA.x - a_qB.x*a_qA.z;
		vCrossProduct.z = a_qB.x*a_qA.y - a_qB.y*a_qA.x;

		/* Compute result vector */
		qOut.x = (a_qB.w * a_qA.x) + (a_qA.w * a_qB.x) + vCrossProduct.x;
		qOut.y = (a_qB.w * a_qA.y) + (a_qA.w * a_qB.y) + vCrossProduct.y;
		qOut.z = (a_qB.w * a_qA.z) + (a_qA.w * a_qB.z) + vCrossProduct.z;

		/* Normalize resulting quaternion */
		qOut.Normalize();
		return qOut;
	}

	//----------------------------------------
	Quaternion Quaternion::FromMatrix(const Matrix4f& a_mat)
	{
		Quaternion quat;
		//const MeReal *const t = (MeReal *) tm;
		float	s;

		float tq[4];
		int j = 0;

		// Use tq to store the largest trace
		tq[0] = 1 + a_mat.m[0][0] + a_mat.m[1][1] + a_mat.m[2][2];
		tq[1] = 1 + a_mat.m[0][0] - a_mat.m[1][1] - a_mat.m[2][2];
		tq[2] = 1 - a_mat.m[0][0] + a_mat.m[1][1] - a_mat.m[2][2];
		tq[3] = 1 - a_mat.m[0][0] - a_mat.m[1][1] + a_mat.m[2][2];

		// Find the maximum (could also use stacked if's later)
		j = 0;
		//for(i=1;i<4;i++) j = (tq[i]>tq[j])? i : j;
		j = (tq[0] > tq[j]) ? 0 : j;
		j = (tq[1] > tq[j]) ? 1 : j;
		j = (tq[2] > tq[j]) ? 2 : j;
		j = (tq[3] > tq[j]) ? 3 : j;

		// check the diagonal
		if (j == 0)
		{
			/* perform instant calculation */
			quat.w = tq[0];
			quat.x = a_mat.m[1][2] - a_mat.m[2][1];
			quat.y = a_mat.m[2][0] - a_mat.m[0][2];
			quat.z = a_mat.m[0][1] - a_mat.m[1][0];
		}
		else if (j == 1)
		{
			quat.w = a_mat.m[1][2] - a_mat.m[2][1];
			quat.x = tq[1];
			quat.y = a_mat.m[0][1] + a_mat.m[1][0];
			quat.z = a_mat.m[2][0] + a_mat.m[0][2];
		}
		else if (j == 2)
		{
			quat.w = a_mat.m[2][0] - a_mat.m[0][2];
			quat.x = a_mat.m[0][1] + a_mat.m[1][0];
			quat.y = tq[2];
			quat.z = a_mat.m[1][2] + a_mat.m[2][1];
		}
		else /* if (j==3) */
		{
			quat.w = a_mat.m[0][1] - a_mat.m[1][0];
			quat.x = a_mat.m[2][0] + a_mat.m[0][2];
			quat.y = a_mat.m[1][2] + a_mat.m[2][1];
			quat.z = tq[3];
		}

		s = 0.5f / sqrt(tq[j]);
		quat.w *= s;
		quat.x *= s;
		quat.y *= s;
		quat.z *= s;

		return quat;
	}
}