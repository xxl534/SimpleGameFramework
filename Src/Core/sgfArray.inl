namespace sgf
{
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE
		TArray<T, NeedCtor, NeedDtor, alignment>::TArray()
		:m_nSize(0)
		,m_nCapacity(0)
		,m_pData(NULL)
	{

	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE
		TArray<T, NeedCtor, NeedDtor, alignment>::TArray(const TArray<T, NeedCtor, NeedDtor, alignment>& a_rhs)
		:m_nSize(0)
		,m_nCapacity(0)
		,m_pData(NULL)
	{
		_copy(a_rhs);
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE
	TArray<T, NeedCtor, NeedDtor, alignment>::TArray(int a_nCapacity)
		:m_nSize(0)
		,m_nCapacity(a_nCapacity)
		,m_pData(NULL)
	{
		assert(m_nCapacity >= 0);
		if (m_nCapacity > 0)
		{
			m_pData = static_cast<T*>(ALIGN_MALLOC(m_nCapacity * sizeof(T), alignment));
		}
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE
	TArray<T, NeedCtor, NeedDtor, alignment>::TArray(int a_nSize, const T& a_Default)
		:m_nSize(a_nSize)
		,m_nCapacity(a_nSize)
		,m_pData(NULL)
	{
		assert(m_nCapacity >= 0);
		if (m_nCapacity > 0)
		{
			m_pData = static_cast<T*>(ALIGN_MALLOC(m_nCapacity * sizeof(T), alignment));
			for (int i = 0; i < m_nSize; ++i)
			{
				new(m_pData + i) T(a_Default);
			}
		}
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE
	TArray<T, NeedCtor, NeedDtor, alignment>::TArray(int a_nSize, const T& a_Default, int a_nCapacity)
		:m_nSize(a_nSize)
		,m_nCapacity(a_nCapacity)
		,m_pData(NULL)
	{
		assert(m_nCapacity >= m_nSize);
		assert(m_nCapacity >= 0);
		if (m_nCapacity > 0)
		{
			m_pData = static_cast<T*>(ALIGN_MALLOC(m_nCapacity * sizeof(T), alignment));
			for (int i = 0; i < m_nSize; ++i)
			{
				new(m_pData + i) T(a_Default);
			}
		}
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE
	TArray<T, NeedCtor, NeedDtor, alignment>::~TArray()
	{
		_cleanup();
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE T&
		TArray<T, NeedCtor, NeedDtor, alignment>::operator[](int a_nIdx)
	{
		assert(a_nIdx >= 0 && a_nIdx < m_nSize);
		return m_pData[a_nIdx];
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE const T& 
		TArray<T, NeedCtor, NeedDtor, alignment>::operator[](int a_nIdx) const
	{
		assert(a_nIdx >= 0 && a_nIdx < m_nSize);
		return m_pData[a_nIdx];
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::operator=(const TArray<T, NeedCtor, NeedDtor, alignment>& a_rhs)
	{
		if (this != &a_rhs)
		{
			if (m_nCapacity >= a_rhs.m_nSize)
			{
				int i = 0;
				if (NeedCtor)
				{
					for (; i < a_rhs.m_nSize && i < m_nSize; ++i)
					{
						m_pData[i] = a_rhs.m_pData[i];
					}
					for (; i < a_rhs.m_nSize; ++i)
					{
						new(m_pData + i) T(a_rhs.m_pData[i]);
					}
				}
				else
				{
					memcpy(m_pData, a_rhs.m_pData, a_rhs.m_nSize * sizeof(T));
					i = a_rhs.m_nSize;
				}

				if (NeedDtor)
				{
					for(; i < m_nSize; ++i )
					{
						m_pData[i].~T();
					}
				}
				m_nSize = a_rhs.m_nSize;
			}
			else
			{
				_cleanup();
				_copy(a_rhs);
			}
		}
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE bool 
		TArray<T, NeedCtor, NeedDtor, alignment>::operator==(const TArray<T, NeedCtor, NeedDtor, alignment>& a_rhs) const
	{
		if( this == &a_rhs)
		{
			return true;
		}
		
		if( m_nSize == a_rhs.m_nSize )
		{
			for (int i = 0; i < m_nSize; ++i)
			{
				if( m_pData[i] != a_rhs.m_pData[i] )
				{
					return false;
				}
			}
		}
		return true;
	}
	
	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE bool 
		TArray<T, NeedCtor, NeedDtor, alignment>::operator!=(const TArray<T, NeedCtor, NeedDtor, alignment>& a_rhs) const
	{
		return !( (*this) == a_rhs );
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE int 
		TArray<T, NeedCtor, NeedDtor, alignment>::size() const
	{
		return m_nSize;
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::resize(int a_nSize)
	{
		assert(a_nSize >= 0);
		resize(a_nSize, T());
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::resize(int a_nSize, const T& a_Default)
	{
		assert(a_nSize >= 0);
		if (a_nSize > m_nCapacity)
		{
			_realloc(a_nSize);
		}
		if (NeedDtor)
		{
			for (int i = a_nSize; i < m_nSize; ++i)
			{
				m_pData[i].~T();
			}
		}
		if (NeedCtor)
		{
			for (int i = m_nSize; i < a_nSize; ++i)
			{
				new(m_pData + i) T(a_Default);
			}
		}
		else
		{
			for (int i = m_nSize; i < a_nSize; ++i)
			{
				memcpy(m_pData + i, &a_Default, sizeof(T));
			}
		}
		m_nSize = a_nSize;
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE int 
		TArray<T, NeedCtor, NeedDtor, alignment>::capacity() const
	{
		return m_nCapacity;
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE int 
		TArray<T, NeedCtor, NeedDtor, alignment>::get_reserve() const
	{
		return m_nCapacity - m_nSize;
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::reserve(int a_nReserveSize)
	{
		assert(a_nReserveSize >= 0);
		_set_capacity(a_nReserveSize + m_nSize);
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void TArray<T, NeedCtor, NeedDtor, alignment>::swap(TArray<T, NeedCtor, NeedDtor, alignment>& a_rhs)
	{
		sgfSwap(m_nSize, a_rhs.m_nSize);
		sgfSwap(m_nCapacity, a_rhs.m_nCapacity);
		sgfSwap(m_pData, a_rhs.m_pData);
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::push_back(const T& a_rhs)
	{
		if (!(m_nSize < m_nCapacity))
		{
			_grow();
		}
		new(m_pData + m_nSize) T(a_rhs);
		++m_nSize;
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::pop_back()
	{
		assert(m_nSize > 0);
		--m_nSize;
		if (NeedDtor)
		{
			m_pData[m_nSize].~T();
		}
	}
	
	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::swap_back(int a_nIdx)
	{
		assert(a_nIdx >= 0 && a_nIdx < m_nSize && m_nSize > 0 );
		--m_nSize;
		if (a_nIdx < m_nSize )
		{
			m_pData[a_nIdx] = m_pData[m_nSize];
		}
		if (NeedDtor)
		{
			m_pData[m_nSize].~T();
		}
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE bool 
		TArray<T, NeedCtor, NeedDtor, alignment>::empty() const
	{
		return m_nSize == 0;
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::clear()
	{
		if (m_nSize > 0)
		{
			if (NeedDtor)
			{
				for (int i = 0; i < m_nSize; ++i)
				{
					m_pData[i].~T();
				}
			}
			m_nSize = 0;
		}
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::trim()
	{
		_realloc(m_nSize);
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE typename TArray<T, NeedCtor, NeedDtor, alignment>::iterator 
		TArray<T, NeedCtor, NeedDtor, alignment>::find(const T& a_val)
	{
		for( int i = 0; i < m_nSize; ++i )
		{
			if (m_pData[i] == a_val) {
				return m_pData + i;
			} 
		}
		return m_pData + m_nSize;
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE typename TArray<T, NeedCtor, NeedDtor, alignment>::const_iterator 
		TArray<T, NeedCtor, NeedDtor, alignment>::find(const T& a_val) const
	{
		return const_cast<TArray<T, NeedCtor, NeedDtor, alignment>*>(this)->find(a_val);
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE int 
		TArray<T, NeedCtor, NeedDtor, alignment>::find_index(const T& a_val) const
	{
		for (int i = 0; i < m_nSize; ++i)
		{
			if (m_pData[i] == a_val) {
				return i;
			}
		}
		return -1;
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::insert(int a_nIdx, const T& a_val)
	{
		assert(a_nIdx >= 0 && a_nIdx <= m_nSize);
		if ( !(m_nSize < m_nCapacity))
		{
			_grow();
		}
		if (a_nIdx != m_nSize)
		{
			_move(a_nIdx, a_nIdx + 1);
		}
		if (NeedCtor)
		{
			new(m_pData + a_nIdx) T(a_val);
		}
		else
		{
			memcpy(m_pData + a_nIdx, &a_val, sizeof(T));
		}
		++m_nSize;
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::insert(iterator a_itor, const T& a_val)
	{
		int nIdx = a_itor - m_pData;
		insert(nIdx, a_val);
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::insert(int a_nIdx, const T& a_val, int a_nCount)
	{
		assert(a_nIdx >= 0 && a_nIdx <= m_nSize);
		if (a_nCount > 0)
		{
			if (!(m_nSize + a_nCount <= m_nCapacity))
			{
				_grow(m_nSize + a_nCount);
			}
			if (a_nIdx != m_nSize)
			{
				_move(a_nIdx, a_nIdx + a_nCount);
			}
			if (NeedCtor)
			{
				for (int i = a_nIdx; i < a_nIdx + a_nCount; ++i)
				{
					new(m_pData + i) T(a_val);
				}
			}
			else
			{
				for (int i = a_nIdx; i < a_nIdx + a_nCount; ++i)
				{
					memcpy(m_pData + i, &a_val, sizeof(T));
				}
			}
			m_nSize += a_nCount;
		}
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::insert(iterator a_itor, const T& a_val, int a_nCount)
	{
		int nIdx = a_itor - m_pData;
		insert(nIdx, a_val, a_nCount);
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::insert(int a_nIdx, const TArray<T, NeedCtor, NeedDtor, alignment>& a_arr)
	{
		insert(a_nIdx, a_arr.m_pData, a_arr.m_nSize);
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::insert(iterator a_itor, const TArray<T, NeedCtor, NeedDtor, alignment>& a_arr)
	{
		int nIdx = a_itor - m_pData;
		insert(nIdx, a_arr);
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::insert(int a_nIdx, const T* a_arr, int a_nLen)
	{
		assert(a_nIdx >= 0 && a_nIdx <= m_nSize);
		if (a_nLen > 0)
		{
			if (!(m_nSize + a_nLen < m_nCapacity))
			{
				_grow(m_nSize + a_nLen);
			}
			if (a_nIdx != m_nSize)
			{
				_move(a_nIdx, a_nIdx + a_nLen);
			}
			if (NeedCtor)
			{
				for (int i = 0; i < a_nLen; ++i)
				{
					new(m_pData + a_nIdx + i) T(a_arr[T]);
				}
			}
			else
			{
				memcpy(m_pData + a_nIdx, a_arr, a_nLen * sizeof(T));
			}
			m_nSize += a_nLen;
		}
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::insert(iterator a_itor, const T* a_arr, int a_nLen)
	{
		int nIdx = a_itor - m_pData;
		insert(nIdx, a_arr, a_nLen);
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::erase(int a_nIdx, int a_nCount /*= 1*/)
	{
		assert(a_nIdx >= 0 && a_nIdx <= m_nSize && a_nCount > 0);
		if (a_nIdx < m_nSize)
		{
			if (a_nIdx + a_nCount > m_nSize)
			{
				a_nCount = m_nSize - a_nIdx;
			}
			if (NeedDtor)
			{
				for (int i = 0; i < a_nCount; ++i)
				{
					m_pData[a_nIdx + i].~T();
				}
			}
			_move(a_nIdx + a_nCount, a_nIdx);
			m_nSize -= a_nCount;
		}
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::erase(iterator a_where)
	{
		int nIdx = a_where - m_pData;
		erase(nIdx);
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::erase(iterator a_itorStart, iterator a_itorEnd)
	{
		int nIdx = a_itorStart - m_pData;
		int nCount = a_itorEnd - a_itorStart;
		erase(nIdx, nCount);
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE typename TArray<T, NeedCtor, NeedDtor, alignment>::iterator 
		TArray<T, NeedCtor, NeedDtor, alignment>::begin()
	{
		return m_pData;
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE typename TArray<T, NeedCtor, NeedDtor, alignment>::const_iterator 
		TArray<T, NeedCtor, NeedDtor, alignment>::begin() const
	{
		return m_pData;
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE typename TArray<T, NeedCtor, NeedDtor, alignment>::iterator 
		TArray<T, NeedCtor, NeedDtor, alignment>::end()
	{
		return m_pData + m_nSize;
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE typename TArray<T, NeedCtor, NeedDtor, alignment>::const_iterator 
		TArray<T, NeedCtor, NeedDtor, alignment>::end() const
	{
		return m_pData + m_nSize;
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE T& 
		TArray<T, NeedCtor, NeedDtor, alignment>::front()
	{
		assert(m_nSize > 0 && m_pData != NULL );
		return *m_pData;
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE const T& 
		TArray<T, NeedCtor, NeedDtor, alignment>::front() const
	{
		assert(m_nSize > 0 && m_pData != NULL);
		return *m_pData;
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE T& 
		TArray<T, NeedCtor, NeedDtor, alignment>::back()
	{
		assert(m_nSize > 0 && m_pData != NULL);
		return m_pData[m_nSize-1];
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE const T& 
		TArray<T, NeedCtor, NeedDtor, alignment>::back() const
	{
		assert(m_nSize > 0 && m_pData != NULL);
		return m_pData[m_nSize - 1];
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::to_array(T** out_pArray) const
	{
		assert(out_pArray != NULL);
		for (int i = 0; i < m_nSize; ++i)
		{
			(*out_pArray)[i] = m_pData[i];
		}
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor, bool NeedDtor, int alignment>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::_cleanup()
	{
		if (NeedDtor)
		{
			for( int i = 0; i < m_nSize; ++i )
			{
				m_pData[i].~T();
			}
		}
		ALIGN_FREE(m_pData);
		m_pData = NULL;
		m_nSize = 0;
		m_nCapacity = 0;
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::_copy(const TArray<T, NeedCtor, NeedDtor, alignment>& a_rhs)
	{
		assert(m_nSize == 0 && m_nCapacity == 0 && m_pData == NULL);
		m_nSize = a_rhs.m_nSize;
		m_nCapacity = m_nSize;
		if (m_nCapacity > 0)
		{
			m_pData = static_cast<T*>(ALIGN_MALLOC(m_nCapacity * sizeof(T), alignment));
			if (NeedCtor)
			{
				for (int i = 0; i < m_nSize; ++i)
				{
					new(m_pData + i) T(a_rhs.m_pData[i]);
				}
			}
			else
			{
				memcpy(m_pData, a_rhs.m_pData, m_nSize * sizeof(T));
			}
		}
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::_realloc(int a_nCapacity)
	{
		assert(a_nCapacity >= m_nSize);
		if (a_nCapacity != m_nCapacity)
		{
			if (a_nCapacity > 0)
			{
				T* pData = static_cast<T*>(ALIGN_MALLOC(a_nCapacity * sizeof(T), alignment));
				if (NeedCtor)
				{
					for (int i = 0; i < m_nSize; ++i)
					{
						new(pData + i) T(m_pData[i]);
					}
				}
				else
				{
					memcpy(pData, m_pData, m_nSize * sizeof(T));
				}
				if (NeedDtor)
				{
					for (int i = 0; i < m_nSize; ++i)
					{
						m_pData[i].~T();
					}
				}
				ALIGN_FREE(m_pData);
				m_pData = pData;
				m_nCapacity = a_nCapacity;
			}
		}
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::_set_capacity(int a_nCapacity)
	{
		assert(a_nCapacity >= m_nSize);
		if (a_nCapacity > m_nCapacity)
		{
			_realloc(a_nCapacity);
		}
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor, bool NeedDtor, int alignment>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::_grow(int a_nMinSize)
	{
		int nCapacity = m_nCapacity;
		do {
			nCapacity = 2 * nCapacity + 3 * nCapacity / 8 + 32;
		} while (nCapacity < a_nMinSize);
		_realloc(nCapacity);
	}

	//-------------------------------------------------------------------------
	template<typename T, bool NeedCtor /*= true*/, bool NeedDtor /*= true*/, int alignment /*= ALIGNMENT_DEFAULT */>
	INLINE void 
		TArray<T, NeedCtor, NeedDtor, alignment>::_move(int a_nFrom, int a_nTo)
	{
		memmove(m_pData + a_nTo, m_pData + a_nFrom, (m_nSize - a_nFrom) * sizeof(T));
	}
}

