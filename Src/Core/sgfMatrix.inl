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
}