#include "sgfCorePCH.h"
#include "sgfVector.h"
#include "sgfMatrix.h"

namespace sgf
{
	Vector3f Vector3f::ms_vZero(0.f);


	//----------------------------------------
	//////////////////////////////////////////
	//Matrix4f
	//////////////////////////////////////////
	//----------------------------------------
	const Matrix4f Matrix4f::kZero(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	);

	const Matrix4f Matrix4f::kIdentity(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);

	//----------------------------------------
	Matrix4f 
		Matrix4f::RotationMatrix(const Vector3f& a_vEular)
	{
		return RotationMatrix(Rotator::FromEular(a_vEular));
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::RotationMatrix(const Rotator& a_rot)
	{
		Matrix4f mOut;

		const float	SR = MathSinTab(a_rot.roll);
		const float	SP = MathSinTab(a_rot.pitch);
		const float	SY = MathSinTab(a_rot.yaw);
		const float	CR = MathCosTab(a_rot.roll);
		const float	CP = MathCosTab(a_rot.pitch);
		const float	CY = MathCosTab(a_rot.yaw);

		mOut.m[0][0] = CP * CY;
		mOut.m[0][1] = CP * SY;
		mOut.m[0][2] = SP;
		mOut.m[0][3] = 0.f;

		mOut.m[1][0] = SR * SP * CY - CR * SY;
		mOut.m[1][1] = SR * SP * SY + CR * CY;
		mOut.m[1][2] = -SR * CP;
		mOut.m[1][3] = 0.f;

		mOut.m[2][0] = -(CR * SP * CY + SR * SY);
		mOut.m[2][1] = CY * SR - CR * SP * SY;
		mOut.m[2][2] = CR * CP;
		mOut.m[2][3] = 0.f;

		mOut.m[3][0] = 0.f;
		mOut.m[3][1] = 0.f;
		mOut.m[3][2] = 0.f;
		mOut.m[3][3] = 1.f;

		return mOut;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::ScaleRotationMatrix(const Vector3f& a_vScale, const Rotator& a_rot)
	{
		Matrix4f mOut;

		const float	SR = MathSinTab(a_rot.roll);
		const float	SP = MathSinTab(a_rot.pitch);
		const float	SY = MathSinTab(a_rot.yaw);
		const float	CR = MathCosTab(a_rot.roll);
		const float	CP = MathCosTab(a_rot.pitch);
		const float	CY = MathCosTab(a_rot.yaw);

		mOut.m[0][0] = (CP * CY) * a_vScale.x;
		mOut.m[0][1] = (CP * SY) * a_vScale.x;
		mOut.m[0][2] = (SP)* a_vScale.x;
		mOut.m[0][3] = 0.f;

		mOut.m[1][0] = (SR * SP * CY - CR * SY) * a_vScale.y;
		mOut.m[1][1] = (SR * SP * SY + CR * CY) * a_vScale.y;
		mOut.m[1][2] = (-SR * CP) * a_vScale.y;
		mOut.m[1][3] = 0.f;

		mOut.m[2][0] = (-(CR * SP * CY + SR * SY)) * a_vScale.z;
		mOut.m[2][1] = (CY * SR - CR * SP * SY) * a_vScale.z;
		mOut.m[2][2] = (CR * CP) * a_vScale.z;
		mOut.m[2][3] = 0.f;

		mOut.m[3][0] = 0;
		mOut.m[3][1] = 0;
		mOut.m[3][2] = 0;
		mOut.m[3][3] = 1.f;

		return mOut;
	}

	//----------------------------------------
	Matrix4f 
		Matrix4f::ScaleRotationTranslationMatrix(const Vector3f& a_vScale, const Rotator& a_rot, const Vector3f& a_vTrans)
	{
		Matrix4f mOut;

		const float	SR = MathSinTab(a_rot.roll);
		const float	SP = MathSinTab(a_rot.pitch);
		const float	SY = MathSinTab(a_rot.yaw);
		const float	CR = MathCosTab(a_rot.roll);
		const float	CP = MathCosTab(a_rot.pitch);
		const float	CY = MathCosTab(a_rot.yaw);

		mOut.m[0][0] = (CP * CY) * a_vScale.x;
		mOut.m[0][1] = (CP * SY) * a_vScale.x;
		mOut.m[0][2] = (SP)* a_vScale.x;
		mOut.m[0][3] = 0.f;

		mOut.m[1][0] = (SR * SP * CY - CR * SY) * a_vScale.y;
		mOut.m[1][1] = (SR * SP * SY + CR * CY) * a_vScale.y;
		mOut.m[1][2] = (-SR * CP) * a_vScale.y;
		mOut.m[1][3] = 0.f;

		mOut.m[2][0] = (-(CR * SP * CY + SR * SY)) * a_vScale.z;
		mOut.m[2][1] = (CY * SR - CR * SP * SY) * a_vScale.z;
		mOut.m[2][2] = (CR * CP) * a_vScale.z;
		mOut.m[2][3] = 0.f;

		mOut.m[3][0] = a_vTrans.x;
		mOut.m[3][1] = a_vTrans.y;
		mOut.m[3][2] = a_vTrans.z;
		mOut.m[3][3] = 1.f;

		return mOut;
	}
}