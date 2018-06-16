namespace sgf
{
	template<typename K, typename V>
	INLINE THashMap<K, V>::THashMap()
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
	template<typename K, typename V>
	INLINE THashMap<K, V>::THashMap(int a_nCapacity)
		:m_nHashCount(8)
		,m_arrHashIdx(NULL)
		,m_arrPair(a_nCapacity)
	{
		m_arrHashIdx = new int[m_nHashCount];
		for (int i = 0; i < m_nHashCount; ++i)
		{
			m_arrHashIdx[i] = HASH_INDEX_NONE;
		}
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE THashMap<K, V>::THashMap(const THashMap<K, V>& a_rhs)
		:m_nHashCount( a_rhs.m_nHashCount )
		,m_arrHashIdx(NULL)
		,m_arrPair( a_rhs.m_arrPair )
	{
		_rehash();
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE THashMap<K, V>::~THashMap()
	{
		SAFE_DELETE_ARRAY(m_arrHashIdx);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K,V>::iterator 
		THashMap<K, V>::begin()
	{
		return iterator(m_arrPair, 0);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::const_iterator
		THashMap<K, V>::begin() const
	{
		return const_iterator(m_arrPair, 0);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::iterator
		THashMap<K, V>::end()
	{
		return iterator(m_arrPair, m_arrPair.size());
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::const_iterator
		THashMap<K, V>::end() const
	{
		return const_iterator(m_arrPair, m_arrPair.size());
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::reverse_iterator
		THashMap<K, V>::rbegin()
	{
		return reverse_iterator(m_arrPair, m_arrPair.size() - 1);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::const_reverse_iterator
		THashMap<K, V>::rbegin() const
	{
		return const_reverse_iterator(m_arrPair, m_arrPair.size() - 1);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::reverse_iterator
		THashMap<K, V>::rend()
	{
		return reverse_iterator(m_arrPair, -1);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::const_reverse_iterator
		THashMap<K, V>::rend() const
	{
		return const_reverse_iterator(m_arrPair, -1);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE void 
		THashMap<K, V>::clear()
	{
		m_arrPair.clear();
		for (int i = 0; i < m_nHashCount; ++i)
		{
			m_arrHashIdx[i] = HASH_INDEX_NONE;
		}
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE int 
		THashMap<K, V>::count(const K& k) const
	{
		return _findIndex(k) == HASH_INDEX_NONE ? 0 : 1;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE bool 
		THashMap<K, V>::hasKey(const K& k) const
	{
		return _findIndex(k) != HASH_INDEX_NONE;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE bool 
		THashMap<K, V>::empty() const
	{
		return m_arrPair.empty();
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE void 
		THashMap<K, V>::set(const K& a_k, const V& a_v)
	{
		int nIdx = _findIndex(a_k);
		if (nIdx == HASH_INDEX_NONE)
		{
			_add(a_k, a_v);
		}
		else
		{
			m_arrPair[nIdx].second = a_v;
		}
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE void 
		THashMap<K, V>::insert(const K& a_k, const V& a_v)
	{
		set(a_k, a_v);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE V& 
		THashMap<K, V>::operator[](const K& a_k)
	{
		int nIdx = _findIndex(a_k);
		if (nIdx == HASH_INDEX_NONE)
		{
			_add(a_k, V());
			return m_arrPair.back().second;
		}
		else
		{
			m_arrPair[nIdx].second;
		}
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE const V& 
		THashMap<K, V>::operator[](const K& a_k) const
	{
		return (*(const_cast<THashMap<K, V>*>(this)))[k];
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE void 
		THashMap<K, V>::operator=(const THashMap<K, V>& a_rhs)
	{
		SAFE_DELETE_ARRAY(m_arrHashIdx);
		m_nHashCount = a_rhs.m_nHashCount;
		m_arrPair = a_rhs.m_arrPair;
		_rehash();
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE V* 
		THashMap<K, V>::findValue(const K& a_k)
	{
		int nIdx = _findIndex(a_k);
		return nIdx != HASH_INDEX_NONE ? &(m_arrPair[nIdx].second) : NULL;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE const V* 
		THashMap<K, V>::findValue(const K& a_k) const
	{
		return (const_cast<THashMap<K, V>*>(this))->findValue(a_k);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE const K* 
		THashMap<K, V>::findKey(const V& a_v, const K* a_pStart /*= NULL*/) const
	{
		int nStartIdx = 0;
		if (a_pStart != NULL)
		{
			int nIdx = _findIndex(*a_pStart);
			if (nIdx != HASH_INDEX_NONE)
			{
				nStartIdx = nIdx;
			}
		}
		for (int i = nStartIdx; i < m_arrPair.size(); ++i)
		{
			if (m_arrPair[i].second == a_v)
			{
				return &m_arrPair[i].first;
			}
		}
		return NULL;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE void 
		THashMap<K, V>::remove(const K& a_k)
	{
		int nIdx = _findIndex(a_k);
		if (nIdx != HASH_INDEX_NONE)
		{
			m_arrPair.erase(nIdx);
			_relax();
		}
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE void 
		THashMap<K, V>::erase(iterator a_itor)
	{
		assert(&a_itor.m_arrPair == &m_arrPair);
		assert(a_itor);
		m_arrPair.erase(iterator.m_nIndex);
		_relax();
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE void 
		THashMap<K, V>::erase(iterator a_itorFrom, iterator a_itorTo)
	{
		assert(&a_itorFrom.m_arrPair == &m_arrPair && &a_itorTo.m_arrPair == &m_arrPair);
		assert(a_itorFrom && ( a_itorTo.m_nIndex >= 0 && a_itorTo.m_nIndex <= m_arrPair.size() ) );
		m_arrPair.erase(a_itorFrom.m_nIndex, a_itorTo.m_nIndex - a_itorFrom.m_nIndex);
		_relax();
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::iterator
		THashMap<K, V>::find(const K& a_k)
	{
		int nIdx = _findIndex(a_k);
		if (nIdx == HASH_INDEX_NONE)
		{
			return end();
		}
		else
		{
			return iterator(m_arrPair, nIdx);
		}
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::const_iterator
		THashMap<K, V>::find(const K& a_k) const
	{
		int nIdx = _findIndex(a_k);
		if (nIdx == HASH_INDEX_NONE)
		{
			return end();
		}
		else
		{
			return const_iterator(m_arrPair, nIdx);
		}
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE int 
		THashMap<K, V>::size() const
	{
		return m_arrPair.size();
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE void 
		THashMap<K, V>::swap(THashMap<K, V>& a_rhs)
	{
		m_arrPair.swap(a_rhs.m_arrPair);
		sgfSwap(m_nHashCount, a_rhs.m_nHashCount);
		sgfSwap(m_arrHashIdx, a_rhs.m_arrHashIdx);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE void 
		THashMap<K, V>::_rehash()
	{
		SAFE_DELETE_ARRAY(m_arrHashIdx);
		m_arrHashIdx = new int[m_nHashCount];
		for (int i = 0; i < m_nHashCount; ++i)
		{
			m_arrHashIdx[i] = HASH_INDEX_NONE;
		}
		for (int i = 0; i < m_arrPair.size(); ++i)
		{
			Pair& pair = m_arrPair[i];
			int nHash = (GetTypeHash(pair.first) & (m_nHashCount - 1));
			pair.m_nHashNext = m_arrHashIdx[nHash];
			m_arrHashIdx[nHash] = i;
		}
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE int 
		THashMap<K, V>::_findIndex(const K& a_k) const
	{
		if (m_arrHashIdx != NULL && m_arrPair.size() > 0)
		{
			for (int i = m_arrHashIdx[GetTypeHash(a_k)&(m_nHashCount - 1)]; i != HASH_INDEX_NONE; i = m_arrPair[i].m_nHashNext)
			{
				if (a_k == m_arrPair[i].first)
				{
					return i;
				}
			}
		}
		return HASH_INDEX_NONE;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE void 
		THashMap<K, V>::_relax()
	{
		while (m_nHashCount > m_arrPair.size() * HASH_REHASH_FACTOR + 8)
		{
			m_nHashCount /= 2;
		}
		_rehash();
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE void 
		THashMap<K, V>::_add(const K& a_k, const V& a_v)
	{
		Pair pair(a_k, a_v);
		m_arrPair.push_back(pair);
		if (m_nHashCount * HASH_REHASH_FACTOR + 8 < m_arrPair.size())
		{
			m_nHashCount *= 2;
			_rehash();
		}
		else
		{	
			int nHash = (GetTypeHash(a_k) & (m_nHashCount - 1));
			pair.m_nHashNext = m_arrHashIdx[nHash];
			m_arrHashIdx[nHash] = m_arrPair.size() - 1;
		}

	}

	//-------------------------------------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//THashMap::iterator
	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K,V>::Pair& 
		THashMap<K,V>::iterator::operator*()
	{
		assert(m_nIndex >= 0 && m_nIndex < m_arrPair.size());
		return m_arrPair[m_nIndex];
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::Pair* 
		THashMap<K, V>::iterator::operator->()
	{
		assert(m_nIndex >= 0 && m_nIndex < m_arrPair.size());
		return &m_arrPair[m_nIndex];
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::iterator& 
		THashMap<K, V>::iterator::operator++()
	{
		++m_nIndex;
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::iterator 
		THashMap<K, V>::iterator::operator++(int)
	{
		return iterator(m_arrPair, m_nIndex++);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::iterator& 
		THashMap<K, V>::iterator::operator--()
	{
		--m_nIndex;
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::iterator 
		THashMap<K, V>::iterator::operator--(int)
	{
		return iterator(m_arrPair, m_nIndex--);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE bool 
		THashMap<K, V>::iterator::operator==(const typename THashMap<K, V>::iterator& a_rhs) const
	{
		return &m_arrPair == &a_rhs.m_arrPair && m_nIndex == a_rhs.m_nIndex;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE bool 
		THashMap<K, V>::iterator::operator!=(const typename THashMap<K, V>::iterator& a_rhs) const
	{
		return !((*this) == a_rhs);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE 
		THashMap<K, V>::iterator::operator bool() const
	{
		return m_nIndex >= 0 && m_nIndex < m_arrPair.size();
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE const K& 
		THashMap<K, V>::iterator::key() const
	{
		assert(m_nIndex >= 0 && m_nIndex < m_arrPair.size());
		return m_arrPair[m_nIndex].first;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE V& 
		THashMap<K, V>::iterator::value()
	{
		assert(m_nIndex >= 0 && m_nIndex < m_arrPair.size());
		return m_arrPair[m_nIndex].second;
	}

	//-------------------------------------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//THashMap::const_iterator
	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE const typename THashMap<K, V>::Pair&
		THashMap<K, V>::const_iterator::operator*() const
	{
		assert(m_nIndex >= 0 && m_nIndex < m_arrPair.size());
		return m_arrPair[m_nIndex];
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE const typename THashMap<K, V>::Pair*
		THashMap<K, V>::const_iterator::operator->() const
	{
		assert(m_nIndex >= 0 && m_nIndex < m_arrPair.size());
		return &m_arrPair[m_nIndex];
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::const_iterator&
		THashMap<K, V>::const_iterator::operator++()
	{
		++m_nIndex;
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::const_iterator
		THashMap<K, V>::const_iterator::operator++(int)
	{
		return const_iterator(m_arrPair, m_nIndex++);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::const_iterator&
		THashMap<K, V>::const_iterator::operator--()
	{
		--m_nIndex;
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::const_iterator
		THashMap<K, V>::const_iterator::operator--(int)
	{
		return const_iterator(m_arrPair, m_nIndex--);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE bool
		THashMap<K, V>::const_iterator::operator==(const typename THashMap<K, V>::const_iterator& a_rhs) const
	{
		return &m_arrPair == &a_rhs.m_arrPair && m_nIndex == a_rhs.m_nIndex;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE bool
		THashMap<K, V>::const_iterator::operator!=(const typename THashMap<K, V>::const_iterator& a_rhs) const
	{
		return !((*this) == a_rhs);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE
		THashMap<K, V>::const_iterator::operator bool() const
	{
		return m_nIndex >= 0 && m_nIndex < m_arrPair.size();
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE const K&
		THashMap<K, V>::const_iterator::key() const
	{
		assert(m_nIndex >= 0 && m_nIndex < m_arrPair.size());
		return m_arrPair[m_nIndex].first;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE const V&
		THashMap<K, V>::const_iterator::value() const
	{
		assert(m_nIndex >= 0 && m_nIndex < m_arrPair.size());
		return m_arrPair[m_nIndex].second;
	}

	//-------------------------------------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//THashMap::reverse_iterator
	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::Pair&
		THashMap<K, V>::reverse_iterator::operator*()
	{
		assert(m_nIndex >= 0 && m_nIndex < m_arrPair.size());
		return m_arrPair[m_nIndex];
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::Pair*
		THashMap<K, V>::reverse_iterator::operator->()
	{
		assert(m_nIndex >= 0 && m_nIndex < m_arrPair.size());
		return &m_arrPair[m_nIndex];
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::reverse_iterator&
		THashMap<K, V>::reverse_iterator::operator++()
	{
		--m_nIndex;
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::reverse_iterator
		THashMap<K, V>::reverse_iterator::operator++(int)
	{
		return reverse_iterator(m_arrPair, m_nIndex--);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::reverse_iterator&
		THashMap<K, V>::reverse_iterator::operator--()
	{
		++m_nIndex;
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::reverse_iterator
		THashMap<K, V>::reverse_iterator::operator--(int)
	{
		return reverse_iterator(m_arrPair, m_nIndex++);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE bool
		THashMap<K, V>::reverse_iterator::operator==(const typename THashMap<K, V>::reverse_iterator& a_rhs) const
	{
		return &m_arrPair == &a_rhs.m_arrPair && m_nIndex == a_rhs.m_nIndex;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE bool
		THashMap<K, V>::reverse_iterator::operator!=(const typename THashMap<K, V>::reverse_iterator& a_rhs) const
	{
		return !((*this) == a_rhs);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE
		THashMap<K, V>::reverse_iterator::operator bool() const
	{
		return m_nIndex >= 0 && m_nIndex < m_arrPair.size();
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE const K&
		THashMap<K, V>::reverse_iterator::key() const
	{
		assert(m_nIndex >= 0 && m_nIndex < m_arrPair.size());
		return m_arrPair[m_nIndex].first;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE V&
		THashMap<K, V>::reverse_iterator::value()
	{
		assert(m_nIndex >= 0 && m_nIndex < m_arrPair.size());
		return m_arrPair[m_nIndex].second;
	}

	//-------------------------------------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//THashMap::const_reverse_iterator
	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE const typename THashMap<K, V>::Pair&
		THashMap<K, V>::const_reverse_iterator::operator*() const
	{
		assert(m_nIndex >= 0 && m_nIndex < m_arrPair.size());
		return m_arrPair[m_nIndex];
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE const typename THashMap<K, V>::Pair*
		THashMap<K, V>::const_reverse_iterator::operator->() const
	{
		assert(m_nIndex >= 0 && m_nIndex < m_arrPair.size());
		return &m_arrPair[m_nIndex];
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::const_reverse_iterator&
		THashMap<K, V>::const_reverse_iterator::operator++()
	{
		--m_nIndex;
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::const_reverse_iterator
		THashMap<K, V>::const_reverse_iterator::operator++(int)
	{
		return const_reverse_iterator(m_arrPair, m_nIndex--);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::const_reverse_iterator&
		THashMap<K, V>::const_reverse_iterator::operator--()
	{
		++m_nIndex;
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE typename THashMap<K, V>::const_reverse_iterator
		THashMap<K, V>::const_reverse_iterator::operator--(int)
	{
		return const_reverse_iterator(m_arrPair, m_nIndex++);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE bool
		THashMap<K, V>::const_reverse_iterator::operator==(const typename THashMap<K, V>::const_reverse_iterator& a_rhs) const
	{
		return &m_arrPair == &a_rhs.m_arrPair && m_nIndex == a_rhs.m_nIndex;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE bool
		THashMap<K, V>::const_reverse_iterator::operator!=(const typename THashMap<K, V>::const_reverse_iterator& a_rhs) const
	{
		return !((*this) == a_rhs);
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE
		THashMap<K, V>::const_reverse_iterator::operator bool() const
	{
		return m_nIndex >= 0 && m_nIndex < m_arrPair.size();
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE const K&
		THashMap<K, V>::const_reverse_iterator::key() const
	{
		assert(m_nIndex >= 0 && m_nIndex < m_arrPair.size());
		return m_arrPair[m_nIndex].first;
	}

	//-------------------------------------------------------------------------
	template<typename K, typename V>
	INLINE const V&
		THashMap<K, V>::const_reverse_iterator::value() const
	{
		assert(m_nIndex >= 0 && m_nIndex < m_arrPair.size());
		return m_arrPair[m_nIndex].second;
	}

}