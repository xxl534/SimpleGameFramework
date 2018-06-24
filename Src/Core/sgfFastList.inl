//-------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////
//TFastList
//////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
namespace sgf
{

	template<typename T>
	INLINE 
		TFastList<T>::TFastList()
		:m_nSize(0)
	{
		_init(0);
	}

	//-------------------------------------------------------------------------
	template<typename T> 
	INLINE
		TFastList<T>::TFastList(const TFastList<T>& a_rhs)
		:m_nSize(0)
	{
		_init(a_rhs.size());
		_assign(a_rhs.begin(), a_rhs.end());
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE
	TFastList<T>::~TFastList()
	{
		clear();
		m_pHead->~Node();
		for (int i = 0; i < m_arrMemoryBlock.size(); ++i)
		{
			free(m_arrMemoryBlock[i].m_pMemoryBlock);
		}
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE void 
		TFastList<T>::operator=(const TFastList<T> a_rhs)
	{
		clear();
		_assign(a_rhs.begin(), a_rhs.end());
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE bool 
		TFastList<T>::operator==(const TFastList<T> a_rhs) const
	{
		if (size() != a_rhs.size())
		{
			return false;
		}
		const_iterator itLeft = begin();
		const_iterator itRight = a_rhs.begin();
		const_iterator itLeftEnd = end();
		const_iterator itRightEnd = a_rhs.end();
		while (itLeft != itLeftEnd && itRight != itRightEnd)
		{
			if( (*itLeft) != (*itRight))
			{
				return false;
			}
			++itLeft;
			++itRight;
		}
		return true;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE bool 
		TFastList<T>::operator!=(const TFastList<T> a_rhs) const
	{
		return !(this->operator ==(a_rhs));
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE T& 
		TFastList<T>::front()
	{
		assert(m_pHead != m_pHead->m_pNext);
		return m_pHead->m_pNext->m_Data;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE const T& 
		TFastList<T>::front() const
	{
		assert(m_pHead != m_pHead->m_pNext);
		return m_pHead->m_pNext->m_Data;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE T& 
		TFastList<T>::back()
	{
		assert(m_pHead != m_pHead->m_pPrev);
		return m_pHead->m_pPrev->m_Data;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE const T& 
		TFastList<T>::back() const
	{
		assert(m_pHead != m_pHead->m_pPrev);
		return m_pHead->m_pPrev->m_Data;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE void
		TFastList<T>::push_back(const T& a_val)
	{
		insert(end(), a_val);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE void 
		TFastList<T>::pop_back()
	{
		assert(m_size > 0);
		iterator it(end());
		--it;
		remove(it);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE void 
		TFastList<T>::push_front(const T& a_val)
	{
		insert(begin(), a_val);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	void TFastList<T>::pop_front()
	{
		assert(m_size > 0);
		remove(begin());
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::iterator
		TFastList<T>::begin()
	{
		return iterator(m_pHead->m_pNext);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::const_iterator
		TFastList<T>::begin() const
	{
		return const_iterator(m_pHead->m_pNext);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::iterator
		TFastList<T>::end()
	{
		return iterator(m_pHead);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::const_iterator
		TFastList<T>::end() const
	{
		return const_iterator(m_pHead);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::reverse_iterator 
		TFastList<T>::rbegin()
	{
		return reverse_iterator(m_pHead->m_pPrev);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::const_reverse_iterator 
		TFastList<T>::rbegin() const
	{
		return const_reverse_iterator(m_pHead->m_pPrev);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::reverse_iterator
		TFastList<T>::rend()
	{
		return reverse_iterator(m_pHead);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::const_reverse_iterator 
		TFastList<T>::rend() const
	{
		return const_reverse_iterator(m_pHead);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::iterator 
		TFastList<T>::insert(iterator a_itWhere, const T& a_val)
	{
		Node* pNode = _alloc_node(a_val);
		pNode->m_pNext = a_itWhere.m_pNode;
		pNode->m_pPrev = a_itWhere.m_pNode->m_pPrev;
		pNode->m_pNext->m_pPrev = pNode;
		pNode->m_pPrev->m_pNext = pNode;
		++m_nSize;
		return iterator(pNode);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::reverse_iterator 
		TFastList<T>::insert(reverse_iterator a_itWhere, const T& a_val)
	{
		Node* pNode = _alloc_node(a_val);
		pNode->m_pNext = a_itWhere.m_pNode->m_pNext;
		pNode->m_pPrev = a_itWhere.m_pNode;
		pNode->m_pNext->m_pPrev = pNode;
		pNode->m_pPrev->m_pNext = pNode;
		++m_nSize;
		return reverse_iterator(pNode);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE void 
		TFastList<T>::remove(iterator a_itWhere)
	{
		assert(a_itWhere.m_pNode && a_itWhere != end());
		Node* pNode = a_itWhere.m_pNode;
		pNode->m_pPrev->m_pNext = pNode->m_pNext;
		pNode->m_pNext->m_pPrev = pNode->m_pPrev;
		_free_node(pNode);
		--m_nSize;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE void 
		TFastList<T>::remove(reverse_iterator a_itWhere)
	{
		assert(a_itWhere.m_pNode && a_itWhere != rend());
		Node* pNode = a_itWhere.m_pNode;
		pNode->m_pPrev->m_pNext = pNode->m_pNext;
		pNode->m_pNext->m_pPrev = pNode->m_pPrev;
		_free_node(pNode);
		--m_nSize;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE void 
		TFastList<T>::remove(const T& a_val)
	{
		iterator it(find(a_val));
		while (it != end())
		{
			iterator itRemove = it;
			it = find(a_val, it);
			remove(itRemove);
		}
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::iterator 
		TFastList<T>::remove_return_next(iterator a_itWhere)
	{
		assert(a_itWhere.m_pNode&& a_itWhere != end());
		iterator itNext(a_itWhere.m_pNode->m_pNext);
		remove(a_itWhere);
		return itNext;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::reverse_iterator 
		TFastList<T>::remove_return_next(reverse_iterator a_itWhere)
	{
		assert(a_itWhere.m_pNode&& a_itWhere != rend());
		reverse_iterator itPrev(a_itWhere.m_pNode->m_pPrev);
		remove(a_itWhere);
		return itPrev;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::iterator 
		TFastList<T>::find(const T& a_val)
	{
		return find(a_val, end());
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::const_iterator 
		TFastList<T>::find(const T& a_val) const
	{
		return find(a_val, end());
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::iterator 
		TFastList<T>::find(const T& a_val, iterator a_it)
	{
		++a_it;
		iterator itEnd = end();
		while (a_it != itEnd)
		{
			if (a_it.m_pNode->m_Data == a_val)
			{
				return a_it;
			}
			++a_it;
		}
		return end();
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::const_iterator 
		TFastList<T>::find(const T& a_val, const_iterator a_it) const
	{
		++a_it;
		const_iterator itEnd = end();
		while (a_it != itEnd)
		{
			if (a_it.m_pNode->m_Data == a_val)
			{
				return a_it;
			}
			++a_it;
		}
		return end();
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::reverse_iterator 
		TFastList<T>::rfind(const T& a_val)
	{
		return rfind(a_val, rend());
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::const_reverse_iterator 
		TFastList<T>::rfind(const T& a_val) const
	{
		return rfind(a_val, rend());
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::reverse_iterator 
		TFastList<T>::rfind(const T& a_val, reverse_iterator a_it)
	{
		++a_it;
		reverse_iterator itEnd = rend();
		while (a_it != itEnd)
		{
			if (a_it.m_pNode->m_Data == a_val)
			{
				return a_it;
			}
			++a_it;
		}
		return rend();
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::const_reverse_iterator 
		TFastList<T>::rfind(const T& a_val, const_reverse_iterator a_it) const
	{
		++a_it;
		const_reverse_iterator itEnd = rend();
		while (a_it != itEnd)
		{
			if (a_it.m_pNode->m_Data == a_val)
			{
				return a_it;
			}
			++a_it;
		}
		return rend();
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE bool 
		TFastList<T>::empty() const
	{
		return m_nSize == 0;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE int 
		TFastList<T>::size() const
	{
		return m_nSize;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE void
		TFastList<T>::clear()
	{
		iterator it = begin();
		iterator itEnd = end();
		while (it != itEnd)
		{
			it = remove_return_next(it);
		}
		m_nSize = 0;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE void 
		TFastList<T>::swap(TFastList<T>& a_rhs)
	{
		sgfSwap(m_nSize, a_rhs.m_nSize);
		sgfSwap(m_pHead, a_rhs.m_pHead);
		m_arrFreeNode.swap(a_rhs.m_arrFreeNode);
		m_arrMemoryBlock.swap(a_rhs.m_arrMemoryBlock);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE void 
		TFastList<T>::to_array(T** a_outArray) const
	{
		assert(a_outArray != NULL);
		const_iterator it = begin();
		const_iterator itEnd = end();
		int idx = 0;
		while (it != itEnd)
		{
			(*a_outArray)[idx] = *it;
			++it;
			++idx;
		}
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE void 
		TFastList<T>::_init(int a_nCapacity)
	{
		if (a_nCapacity < 1)
		{
			a_nCapacity = FASTLIST_INCREASE_STEP;
		}
		Node* pBase = static_cast<Node*>(malloc(a_nCapacity * sizeof(Node)));
		MemoryBlock block(pBase, a_nCapacity);
		m_arrMemoryBlock.push_back(block);
		for (int i = 0; i < a_nCapacity - 1; ++i)
		{
			m_arrFreeNode.push_back(pBase + i);
		}
		m_pHead = new(pBase + a_nCapacity - 1) Node();
		m_pHead->m_pNext = m_pHead;
		m_pHead->m_pPrev = m_pHead;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE void 
		TFastList<T>::_assign(typename TFastList<T>::const_iterator a_beginNode, typename TFastList<T>::const_iterator a_endNode)
	{
		clear();
		for (const_iterator it = a_beginNode; it != a_endNode; ++it)
		{
			push_back(it.m_pNode->m_Data);
		}
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE typename TFastList<T>::Node* 
		TFastList<T>::_alloc_node(const T& a_val)
	{
		if (m_arrFreeNode.empty())
		{
			int nCapacity = FASTLIST_INCREASE_STEP;
			Node* pBase = static_cast<Node*>(malloc(nCapacity * sizeof(Node)));
			MemoryBlock block(pBase, nCapacity);
			m_arrMemoryBlock.push_back(block);
			for (int i = 0; i < nCapacity; ++i)
			{
				m_arrFreeNode.push_back(pBase + i);
			}
		}
		Node* pNode = m_arrFreeNode.back();
		m_arrFreeNode.pop_back();
		return new(pNode) Node(a_val);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE void 
		TFastList<T>::_free_node(Node* a_pNode)
	{
		a_pNode->~Node();
		m_arrFreeNode.push_back(a_pNode);
	}
	
}