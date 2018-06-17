#include "sgfVector.h"
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
}