namespace sgf
{


	Rotator Rotator::operator+(const Rotator& a_rhs) const
	{
		return Rotator(pitch + a_rhs.pitch, yaw + a_rhs.yaw, roll + a_rhs.roll);
	}

	Rotator Rotator::operator-(const Rotator& a_rhs) const
	{
		return Rotator(pitch - a_rhs.pitch, yaw - a_rhs.yaw, roll - a_rhs.roll);
	}

	Rotator Rotator::operator*(float a_fScale) const
	{
		return Rotator(MathTrunc(pitch*a_fScale), MathTrunc(yaw*a_fScale), MathTrunc(roll*a_fScale));
	}

	Rotator& Rotator::operator*=(float a_fScale)
	{
		pitch = MathTrunc(pitch*a_fScale);
		yaw = MathTrunc(pitch*a_fScale);
		roll = MathTrunc(pitch*a_fScale);
		return *this;
	}

	Quaternion Rotator::ToQuaternion() const
	{
		return Quaternion::FromMatrix(Matrix4f::RotationMatrix(*this));
	}

	Vector3f Rotator::ToEular() const
	{
		return Vector3f(
			roll * (180.f / 32768.f),
			pitch * (180.f / 32768.f),
			yaw * (180.f / 32768.f)
		);
	}

	Vector3f Rotator::ToEularArc() const
	{
		return Vector3f(
			roll * (kPI / 32768.f),
			pitch * (kPI / 32768.f),
			yaw * (kPI / 32768.f)
		);
	}

	Rotator Rotator::Clamp() const
	{
		return Rotator(pitch & 65535, yaw & 65535, roll & 65535);
	}

	Rotator Rotator::ClampPos() const
	{
		return Rotator(MathAbs(pitch & 65535), MathAbs(yaw & 65535), MathAbs(roll & 65535));
	}

	Rotator Rotator::Normalize() const
	{
		return Rotator(
			NormalizeAxis(pitch),
			NormalizeAxis(yaw),
			NormalizeAxis(roll)
		);
	}

	void Rotator::MakeShortestRoute()
	{
		// Clip rotation to +/- 65535 range
		yaw = yaw & 65535;

		// Then ensure it takes the 'shortest' route.
		if (yaw > 32768)
			yaw -= 65535;
		else if (yaw < -32768)
			yaw += 65535;


		//// PITCH

		pitch = pitch & 65535;

		if (pitch > 32768)
			pitch -= 65535;
		else if (pitch < -32768)
			pitch += 65535;


		//// ROLL

		roll = roll & 65535;

		if (roll > 32768)
			roll -= 65535;
		else if (roll < -32768)
			roll += 65535;
	}

	Rotator Rotator::FromEular(const Vector3f& a_vEular)
	{
		return Rotator(
			MathTrunc(a_vEular.y * (32768.f / 180.f)),
			MathTrunc(a_vEular.z * (32768.f / 180.f)),
			MathTrunc(a_vEular.x * (32768.f / 180.f))
		);
	}

	Rotator Rotator::FromEular(float a_fx, float a_fy, float a_fz)
	{
		return Rotator(
			MathTrunc(a_fy * (32768.f / 180.f)),
			MathTrunc(a_fz * (32768.f / 180.f)),
			MathTrunc(a_fx * (32768.f / 180.f))
		);
	}

	Rotator Rotator::FromEularArc(const Vector3f& a_vArc)
	{
		return Rotator(
			MathTrunc(a_vArc.y * (32768.f / kPI)),
			MathTrunc(a_vArc.z * (32768.f / kPI)),
			MathTrunc(a_vArc.x * (32768.f / kPI))
		);
	}

	Rotator Rotator::FromEularArc(float a_fx, float a_fy, float a_fz)
	{
		return Rotator(
			MathTrunc(a_fy * (32768.f / kPI)),
			MathTrunc(a_fz * (32768.f / kPI)),
			MathTrunc(a_fx * (32768.f / kPI))
		);
	}

	Rotator Rotator::FromQuaternion(const Quaternion& a_quat)
	{
		return Rotator::FromMatrix(a_quat.ToRotationMatrix());
	}

	Rotator Rotator::FromMatrix(const Matrix4f& a_mat)
	{
		const Vector3f XAxis = a_mat.GetAxis(0);
		const Vector3f YAxis = a_mat.GetAxis(1);
		const Vector3f ZAxis = a_mat.GetAxis(2);

		Rotator	a_rhs = Rotator(
			MathRound(MathAtan2(XAxis.z, MathSqrt(Square(XAxis.x) + Square(XAxis.y))) * 32768.f / kPI),
			MathRound(MathAtan2(XAxis.y, XAxis.x) * 32768.f / kPI),
			0
		);

		const Vector3f SYAxis = Matrix4f::RotationMatrix(a_rhs).GetAxis(1);
		a_rhs.roll = MathRound(MathAtan2(ZAxis | SYAxis, YAxis | SYAxis) * 32768.f / kPI);
		return a_rhs;
	}

	int32 Rotator::NormalizeAxis(int32 a_fAngle)
	{
		a_fAngle &= 0xFFFF;
		if (a_fAngle > 32767)
		{
			a_fAngle -= 0x10000;
		}
		return a_fAngle;
	}

	bool Rotator::operator!=(const Rotator& a_rhs) const
	{
		return pitch != a_rhs.pitch || yaw != a_rhs.yaw || roll != a_rhs.roll;
	}

	bool Rotator::operator==(const Rotator& a_rhs) const
	{
		return pitch == a_rhs.pitch&&yaw == a_rhs.yaw&&roll == a_rhs.roll;
	}

	Rotator& Rotator::operator-=(const Rotator& a_rhs)
	{
		pitch -= a_rhs.pitch;
		yaw -= a_rhs.yaw;
		roll -= a_rhs.roll;
		return *this;
	}

	Rotator& Rotator::operator+=(const Rotator& a_rhs)
	{
		pitch += a_rhs.pitch;
		yaw += a_rhs.yaw;
		roll += a_rhs.roll;
		return *this;
	}
}