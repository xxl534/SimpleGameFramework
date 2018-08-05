namespace sgf
{
	//-------------------------------------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//TVector2
	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------
	template<typename T>
	INLINE bool 
		TVector2<T>::operator==(const TVector2<T>& a_rhs) const
	{
		return x == a_rhs.x && y == a_rhs.y;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE bool 
		TVector2<T>::operator!=(const TVector2<T>& a_rhs) const
	{
		return x != a_rhs.x || y != a_rhs.y;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector2<T>& 
		TVector2<T>::operator-=(const TVector2<T>& a_rhs)
	{
		x -= a_rhs.x;
		y -= a_rhs.y;
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector2<T> 
		TVector2<T>::operator-(const TVector2<T>& a_rhs) const
	{
		TVector2<T> v(*this);
		v -= a_rhs;
		return v;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector2<T> 
		TVector2<T>::operator-() const
	{
		return TVector2<T>(-x, -y);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector2<T>& 
		TVector2<T>::operator+=(const TVector2<T>& a_rhs)
	{
		x += a_rhs.x;
		y += a_rhs.y;
		return *this
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector2<T> 
		TVector2<T>::operator+(const TVector2<T>& a_rhs) const
	{
		TVector2<T> v(*this);
		v += a_rhs;
		return v;
	}
	
	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector2<T>& 
		TVector2<T>::operator*=(float a_f)
	{
		x *= a_f;
		y *= a_f;
		return *this
	}
	
	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector2<T> 
		TVector2<T>::operator*(float a_f) const
	{
		TVector2<T> v(*this);
		v *= a_rhs;
		return v;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector2<T>& 
		TVector2<T>::operator*=(const TVector2<T>& a_rhs)
	{
		x *= a_rhs.x;
		y *= a_rhs.y;
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector2<T> 
		TVector2<T>::operator*(const TVector2<T>& a_rhs) const
	{
		TVector2<T> v(*this);
		v *= a_rhs;
		return v;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector2<T>& 
		TVector2<T>::operator/=(float a_f)
	{
		return this->operator *=(1.f / a_f);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector2<T> 
		TVector2<T>::operator/(float a_f) const
	{
		TVector2<T> v(*this);
		v /= a_f;
		return v;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE float 
		TVector2<T>::dot(const TVector2<T>& a_rhs) const
	{
		return x * a_rhs.x + y * a_rhs.y;
	}

	//-------------------------------------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//TVector3
	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------
	template<typename T>
	INLINE bool
		TVector3<T>::operator==(const TVector3<T>& a_rhs) const
	{
		return x == a_rhs.x && y == a_rhs.y && z == a_rhs.z;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE bool
		TVector3<T>::operator!=(const TVector3<T>& a_rhs) const
	{
		return x != a_rhs.x || y != a_rhs.y || z != a_rhs.z;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector3<T>&
		TVector3<T>::operator-=(const TVector3<T>& a_rhs)
	{
		x -= a_rhs.x;
		y -= a_rhs.y;
		z -= a_rhs.z;
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector3<T>
		TVector3<T>::operator-(const TVector3<T>& a_rhs) const
	{
		TVector3<T> v(*this);
		v -= a_rhs;
		return v;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector3<T>
		TVector3<T>::operator-() const
	{
		return TVector3<T>(-x, -y, -z);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector3<T>&
		TVector3<T>::operator+=(const TVector3<T>& a_rhs)
	{
		x += a_rhs.x;
		y += a_rhs.y;
		z += a_rhs.z;
		return *this
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector3<T>
		TVector3<T>::operator+(const TVector3<T>& a_rhs) const
	{
		TVector3<T> v(*this);
		v += a_rhs;
		return v;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector3<T>&
		TVector3<T>::operator*=(float a_f)
	{
		x *= a_f;
		y *= a_f;
		z *= a_f;
		return *this
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector3<T>
		TVector3<T>::operator*(float a_f) const
	{
		TVector3<T> v(*this);
		v *= a_rhs;
		return v;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector3<T>& 
		TVector3<T>::operator*=(const TVector3<T>& a_rhs)
	{
		x *= a_rhs.x;
		y *= a_rhs.y;
		z *= a_rhs.z;
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector3<T> 
		TVector3<T>::operator*(const TVector3<T>& a_rhs) const
	{
		TVector3<T> v(*this);
		v *= a_rhs;
		return v;
	}
	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector3<T>&
		TVector3<T>::operator/=(float a_f)
	{
		return this->operator *=(1.f / a_f);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector3<T>
		TVector3<T>::operator/(float a_f) const
	{
		TVector3<T> v(*this);
		v /= a_f;
		return v;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE float
		TVector3<T>::dot(const TVector3<T>& a_rhs) const
	{
		return x * a_rhs.x + y * a_rhs.y + z * a_rhs.z;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector3<T> 
		TVector3<T>::cross(const TVector3<T>& a_rhs) const
	{
		T t_x = y * a_rhs.z - z * a_rhs.y;
		T t_y = z * a_rhs.x - x * a_rhs.z;
		T t_z = x * a_rhs.y - y * a_rhs.x;
		return TVector3<T>(t_x, t_y, t_z);
	}

	//-------------------------------------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//TVector4
	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------
	template<typename T>
	INLINE bool
		TVector4<T>::operator==(const TVector4<T>& a_rhs) const
	{
		return x == a_rhs.x && y == a_rhs.y && z == a_rhs.z && w == a_rhs.w;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE bool
		TVector4<T>::operator!=(const TVector4<T>& a_rhs) const
	{
		return !((*this) == a_rhs);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector4<T>&
		TVector4<T>::operator-=(const TVector4<T>& a_rhs)
	{
		x -= a_rhs.x;
		y -= a_rhs.y;
		z -= a_rhs.z;
		w -= a_rhs.w;
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector4<T>
		TVector4<T>::operator-(const TVector4<T>& a_rhs) const
	{
		TVector4<T> v(*this);
		v -= a_rhs;
		return v;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector4<T>
		TVector4<T>::operator-() const
	{
		return TVector4<T>(-x, -y, -z, -w);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector4<T>&
		TVector4<T>::operator+=(const TVector4<T>& a_rhs)
	{
		x += a_rhs.x;
		y += a_rhs.y;
		z += a_rhs.z;
		w += a_rhs.w;
		return *this
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector4<T>
		TVector4<T>::operator+(const TVector4<T>& a_rhs) const
	{
		TVector4<T> v(*this);
		v += a_rhs;
		return v;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector4<T>&
		TVector4<T>::operator*=(float a_f)
	{
		x *= a_f;
		y *= a_f;
		z *= a_f;
		w *= a_f;
		return *this
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector4<T>
		TVector4<T>::operator*(float a_f) const
	{
		TVector4<T> v(*this);
		v *= a_rhs;
		return v;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector4<T>&
		TVector4<T>::operator*=(const TVector4<T>& a_rhs)
	{
		x *= a_rhs.x;
		y *= a_rhs.y;
		z *= a_rhs.z;
		w *= a_rhs.w;
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector4<T>
		TVector4<T>::operator*(const TVector4<T>& a_rhs) const
	{
		TVector4<T> v(*this);
		v *= a_rhs;
		return v;
	}
	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector4<T>&
		TVector4<T>::operator/=(float a_f)
	{
		return this->operator *=(1.f / a_f);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TVector4<T>
		TVector4<T>::operator/(float a_f) const
	{
		TVector4<T> v(*this);
		v /= a_f;
		return v;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE float
		TVector4<T>::dot(const TVector4<T>& a_rhs) const
	{
		return x * a_rhs.x + y * a_rhs.y + z * a_rhs.z + w * a_rhs.w;
	}

	//----------------------------------------
	//////////////////////////////////////////
	//Vector3f
	//////////////////////////////////////////
	//----------------------------------------
	Vector3f& 
		Vector3f::Lerp(const Vector3f& a_v, float a_fFactor)
	{
		float fNegFactor = 1 - a_fFactor;
		x = fNegFactor * x + a_fFactor * a_v.x;
		y = fNegFactor * y + a_fFactor * a_v.y;
		z = fNegFactor * z + a_fFactor * a_v.z;
		return *this;
	}

	//----------------------------------------
	Vector3f 
		Vector3f::GetLerp(const Vector3f& a_v, float a_fFactor) const
	{
		Vector3f vTmp(*this);
		vTmp.Lerp(a_v, a_fFactor);
		return vTmp;
	}

	//----------------------------------------
	Vector3f& 
		Vector3f::Abs()
	{
		x = MathAbs(x);
		y = MathAbs(y);
		z = MathAbs(z);
	}

	//----------------------------------------
	Vector3f 
		Vector3f::GetAbs() const
	{
		Vector3f vTmp(*this);
		vTmp.Abs();
		return vTmp;
	}

	//----------------------------------------
	Vector3f& 
		Vector3f::Normalize()
	{
		double dLenSqr = (double)(x * x) + (y * y) + (z * z);
		if( dLenSqr > 0.0 )
		{
			float fLenRecp = 1.f / sqrt(dLenSqr);
			x *= fLenRecp;
			y *= fLenRecp;
			z *= fLenRecp;
		}
		return *this;
	}

	//----------------------------------------
	Vector3f 
		Vector3f::GetNormalize() const
	{
		Vector3f vTmp(*this);
		vTmp.Normalize();
		return vTmp;
	}

	//----------------------------------------
	float Vector3f::Length()
	{
		double dLenSqr = (double)(x * x) + (y * y) + (z * z);
		return sqrt(dLenSqr);
	}

	//----------------------------------------
	float 
		Vector3f::LengthSqr()
	{
		return x*x + y*y + z*z;;
	}

	//----------------------------------------
	void 
		Vector3f::FindBestAxisVectors(Vector3f& a_vAxis1, Vector3f& a_vAxis2)
	{
		Normalize();
		Vector3f vAbs = GetAbs();

		if (vAbs.z > vAbs.x && vAbs.z > vAbs.y)
		{
			a_vAxis1 = Vector3f(1.f, 0.f, 0.f);
		}
		else
		{
			a_vAxis1 = Vector3f(0.f, 0.f, 1.f);
		}

		a_vAxis1 = (a_vAxis1 - *this * (a_vAxis1.dot(*this)));
		a_vAxis1.Normalize();
		a_vAxis2 = a_vAxis1.cross(*this);
	}

	//----------------------------------------
	Vector3f& 
		Vector3f::Set(float a_fx, float a_fy, float a_fz)
	{
		x = a_fx;
		y = a_fy;
		z = a_fz;
	}

	//----------------------------------------
	void 
		Vector3f::RotateYZBy(float a_fDegrees, const Vector3f& a_vecCenter /*= Vector3f(0.f, 0.f, 0.f)*/)
	{
		a_fDegrees *= kPIDivide180;
		float cs = MathCosFloat(a_fDegrees);
		float sn = MathSinFloat(a_fDegrees);
		z -= a_vecCenter.z;
		y -= a_vecCenter.y;
		Set(x, y*cs - z*sn, y*sn + z*cs);
		z += a_vecCenter.z;
		y += a_vecCenter.y;
	}

	//----------------------------------------
	void 
		Vector3f::RotateXZBy(float a_fDegrees, const Vector3f& a_vecCenter /*= Vector3f(0.f, 0.f, 0.f)*/)
	{
		a_fDegrees *= kPIDivide180;
		float cs = MathCosFloat(a_fDegrees);
		float sn = MathSinFloat(a_fDegrees);
		x -= a_vecCenter.x;
		z -= a_vecCenter.z;
		Set(x*cs - z*sn, y, x*sn + z*cs);
		x += a_vecCenter.x;
		z += a_vecCenter.z;
	}

	//----------------------------------------
	void 
		Vector3f::RotateXYBy(float a_fDegrees, const Vector3f& a_vecCenter /*= Vector3f(0.f, 0.f, 0.f)*/)
	{
		a_fDegrees *= kPIDivide180;
		float cs = MathCosFloat(a_fDegrees);
		float sn = MathSinFloat(a_fDegrees);
		x -= a_vecCenter.x;
		y -= a_vecCenter.y;
		Set(x*cs - y*sn, x*sn + y*cs, z);
		x += a_vecCenter.x;
		y += a_vecCenter.y;
	}

	//----------------------------------------
	const Vector3f& 
		Vector3f::Zero()
	{
		return ms_vZero;
	}
}