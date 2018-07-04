namespace sgf
{
	template<typename T> INLINE
	THashSet<T>::THashSet()
		:m_nHashCount(8)
		,m_arrHashIdx(NULL)
	{
		m_arrHashIdx = new int[m_nHashCount];
		for (int i = 0; i < m_nHashCount; ++i)
		{
			m_arrHashIdx[i] = HASH_INDEX_NONE;
		}
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE
	THashSet<T>::THashSet(int a_nCapacity)
		:m_nHashCount(8)
		,m_arrHashIdx(NULL)
		,m_arrData(a_nCapacity)
	{
		m_arrHashIdx = new int[m_nHashCount];
		for (int i = 0; i < m_nHashCount; ++i)
		{
			m_arrHashIdx[i] = HASH_INDEX_NONE;
		}
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE 
		THashSet<T>::THashSet(const THashSet<T>& a_rhs)
		:m_nHashCount(a_rhs.m_nHashCount)
		, m_arrHashIdx(NULL)
		, m_arrData(a_rhs.m_arrData)
	{
		_rehash();
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE
	THashSet<T>::~THashSet()
	{
		SAFE_DELETE_ARRAY(m_pHash);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE 
	typename THashSet<T>::iterator 
		THashSet<T>::begin()
	{
		return iterator(m_arrData, 0);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE 
	typename THashSet<T>::const_iterator 
		THashSet<T>::begin() const
	{
		return const_iterator(m_arrData, 0);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE 
	typename THashSet<T>::iterator 
		THashSet<T>::end()
	{
		return iterator(m_arrData, m_arrData.size());
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE 
	typename THashSet<T>::const_iterator
		THashSet<T>::end() const
	{
		return const_iterator(m_arrData, m_arrData.size());
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE 
	typename THashSet<T>::reverse_iterator 
		THashSet<T>::rbegin()
	{
		return reverse_iterator(m_arrData, m_arrData.size() - 1);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE 
	typename THashSet<T>::const_reverse_iterator 
		THashSet<T>::rbegin() const
	{
		return const_reverse_iterator(m_arrData, m_arrData.size() - 1);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE 
	typename THashSet<T>::reverse_iterator 
		THashSet<T>::rend()
	{
		return reverse_iterator(m_arrData, -1);
	}

	//-------------------------------------------------------------------------
	template<typename T>INLINE 
	typename THashSet<T>::const_reverse_iterator 
		THashSet<T>::rend() const
	{
		return const_reverse_iterator(m_arrData, -1);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE 
	void 
		THashSet<T>::clear()
	{
		m_arrData.clear();
		for (int i = 0; i < m_nHashCount; ++i)
		{
			m_arrHashIdx[i] = HASH_INDEX_NONE;
		}
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE
	bool 
		THashSet<T>::has(const T& a_value) const
	{
		return _findIndex(a_value) != HASH_INDEX_NONE;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE
	bool 
		THashSet<T>::empty() const
	{
		return m_arrData.empty();
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE
	void 
		THashSet<T>::insert(const T& a_value)
	{
		if (_findIndex(a_value) == HASH_INDEX_NONE)
		{
			_add(a_value);
		}
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE
	void 
		THashSet<T>::erase(const T& a_value)
	{
		int nIdx = _findIndex(a_value);
		if (nIdx != HASH_INDEX_NONE)
		{
			m_arrData.erase(nIdx);
			_relax();
		}
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE
	void 
		THashSet<T>::erase(typename THashSet<T>::iterator a_itWhere)
	{
		m_arrData.erase(a_itWhere.m_nIndex);
		_relax();
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE
	typename THashSet<T>::iterator 
		THashSet<T>::find(const T& a_value)
	{
		int nIdx = _findIndex(a_value);
		if (HASH_INDEX_NONE == nIdx)
		{
			return end();
		}
		return iterator(m_arrData, nIdx);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE
	typename THashSet<T>::const_iterator
		THashSet<T>::find(const T& a_value) const
	{
		int nIdx = _findIndex(a_value);
		if (HASH_INDEX_NONE == nIdx)
		{
			return end();
		}
		return const_iterator(m_arrData, nIdx);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE
	int 
		THashSet<T>::size() const
	{
		return m_arrData.size();
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE
	void 
		THashSet<T>::swap(THashSet<T>& a_rhs)
	{
		m_arrData.swap(a_rhs.m_arrData);
		sgfSwap(m_nHashCount, a_rhs.m_nHashCount);
		sgfSwap(m_arrHashIdx, a_rhs.m_arrHashIdx);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE
	void 
		THashSet<T>::operator=(const THashSet<T>& a_rhs)
	{
		SAFE_DELETE_ARRAY(m_arrHashIdx);
		m_nHashCount = a_rhs.m_nHashCount;
		m_arrData = a_rhs.m_arrData;
		_rehash();
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE
	void 
		THashSet<T>::_rehash()
	{

	}

	template<typename T> INLINE
	int 
		THashSet<T>::_findIndex(const T& a_value) const
	{

	}

	template<typename T> INLINE
	void 
		THashSet<T>::_add(const T& a_value)
	{

	}

	template<typename T> INLINE
	void 
		THashSet<T>::_relax()
	{

	}
}