#include "sgfString.h"
namespace sgf
{
	
	//----------------------------------------
	//////////////////////////////////////////
	//TStringBase::Rep
	//////////////////////////////////////////
	//----------------------------------------
	template<typename T> INLINE T * 
		TStringBase<T>::Rep::getData()
	{
		return reinterpret_cast<T*>(this + 1);
	}

	//----------------------------------------
	template<typename T> INLINE const T * 
		TStringBase<T>::Rep::getData() const
	{
		return reinterpret_cast<const T*>(this + 1);
	}

	//----------------------------------------
	template<typename T> INLINE T* 
		TStringBase<T>::Rep::refCopy()
	{
		++m_nReference;
		return getData();
	}

	//----------------------------------------
	template<typename T> INLINE int 
		TStringBase<T>::Rep::getSize() const
	{
		return 0;
	}

	//----------------------------------------
	template<typename T> INLINE void 
		TStringBase<T>::Rep::unRef()
	{
		if (--m_nReference < 0)
		{
			if (this != reinterpret_cast<Rep*>(ms_emptyStringRep))
			{
				freeMemory();
			}
		}
	}

	//----------------------------------------
	template<typename T> INLINE void 
		TStringBase<T>::Rep::freeMemory()
	{
		ASSERT(this != reinterpret_cast<Rep*>(ms_emptyStringRep));
		free(this);

	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE typename TStringBase<T>::Rep* 
		TStringBase<T>::Rep::clone() const
	{
		Rep* pRep = reinterpret_cast<Rep*>(malloc(getSize()));
		pRep->m_nlength = m_nlength;
		pRep->m_nCapacity = m_nCapacity;
		pRep->m_nReference = 0;
		return pRep;
	}

	//-------------------------------------------------------------------------
	template<typename T> typename TStringBase<T>::Rep* 
		TStringBase<T>::Rep::Create(int a_nLen)
	{
		unsigned int nCapacity = a_nLen;
		if (nCapacity < MIN_STRING_CAPACITY)
		{
			nCapacity = MIN_STRING_CAPACITY;
		}
		Rep* pRep = reinterpret_cast<Rep*>(malloc(sizeof(Rep) + sizeof(T) * (nCapacity + 1)));
		pRep->m_nlength = a_nLen;
		pRep->m_nCapacity = nCapacity;
		pRep->m_nReference = 0;
		return pRep;
	}



	//----------------------------------------
	//////////////////////////////////////////
	//TStringBase
	//////////////////////////////////////////
	//-------------------------------------------------------------------------
	template<typename T> TStringBase<T> TStringBase<T>::ms_emptyString;
	//----------------------------------------

	template<typename T> unsigned char 
		TStringBase<T>::ms_emptyStringRep[sizeof(int) + sizeof(int) + sizeof(int) + sizeof(T)];
	//----------------------------------------
	template<typename T> INLINE
	TStringBase<T>::TStringBase()
	{
		m_string = _GetEmptyStringRep().refCopy();
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE 
		TStringBase<T>::TStringBase(const T * a_str)
	{
		if (a_str != NULL&&a_str[0] != 0)
		{
			int nLen = StrLen(a_str);
			m_string = Rep::Create(nLen)->getData();
			MemCpy(m_string, a_str, nLen+1);
		}
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE 
		TStringBase<T>::TStringBase(const T * a_str, int a_nLen)
	{
		if (a_nLen == 0 || a_str == NULL)
		{
			m_string = _GetEmptyStringRep().refCopy();
		}
		else
		{
			ASSERT(a_str != NULL);
			int nLen;
			if (a_nLen == INVALID_INDEX)
			{
				nLen = StrLen(a_str);
			}
			else
			{
				nLen = StrLenSafe(a_str, a_nLen);
			}
			ASSERT(nLen >= 0);
			m_string = Rep::Create(nLen)->getData();
			MemCpy(m_string, a_str, nLen);
			m_string[nLen] = 0;
		}
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE
		TStringBase<T>::TStringBase(T a_ch, int a_nLen)
	{
		ASSERT(a_nLen >= 0);
		m_string = Rep::Create(a_nLen)->getData();
		StrSet(m_string, a_ch, a_nLen);
		m_string[a_nLen] = 0;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE 
		TStringBase<T>::TStringBase(const TStringBase<T>& a_szSrc)
	{
		m_string = a_szSrc._GetRep().refCopy();
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE
		TStringBase<T>::TStringBase(typename TStringBase<T>::Rep * a_pRep)
		:m_string( a_pRep->getData() )
	{
		
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE
		TStringBase<T>::~TStringBase()
	{
		_GetRep().unRef();
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::operator=(const TStringBase<T>& rhs)
	{
		T* szNewStr = rhs._GetRep().refCopy();
		_GetRep().unRef();
		m_string = szNewStr;
		return (*this);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::operator=(const T * rhs)
	{
		if( rhs == NULL || *rhs == 0 )
		{
			_GetRep().unRef();
			m_string = _GetEmptyStringRep().refCopy();
		}
		else
		{
			int nLen = StrLen(rhs);
			if( _GetRep().m_nCapacity < nLen || _GetRep().m_nReference > 0 )
			{
				_GetRep().unRef();
				m_string = Rep::Create(nLen)->getData();
			}
			MemCpy(m_string, rhs, nLen + 1);
			_GetRep().m_nlength = nLen;
		}
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE T 
		TStringBase<T>::operator[](int a_nIdx) const
	{
		ASSERT(a_nIdx >= 0 && a_nIdx < _GetRep().m_nlength);
		return m_string[a_nIdx];
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE int 
		TStringBase<T>::length() const
	{
		return _GetRep().m_nlength;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE void 
		TStringBase<T>::clear()
	{
		_GetRep().unRef();
		m_string = _GetEmptyStringRep().refCopy();
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE bool 
		TStringBase<T>::empty() const
	{
		return length() == 0;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE void 
		TStringBase<T>::printf(const T * a_szFormat, ...)
	{
		if (_GetRep().m_nReference >  0 || length() < MIN_STRING_CAPACITY )
		{
			_GetRep().unRef();
			m_string = Rep::Create(256)->getData();
		}

		while (1)
		{
			int nSize = _GetRep().m_nCapacity;
			va_list argPtr;
			va_start(argPtr, a_szFormat);
			int nChars = Vsnprintf(m_string, nSize, a_szFormat, argPtr);
			va_end(argPtr);

			if (nChars >= 0 && nChars < nSize)
			{
				_GetRep().m_nlength = nChars;
				break;
			}
			else
			{
				_GetRep().unRef();
				m_string = Rep::Create(nSize * 2 > 256 ? nSize * 2 : 256)->getData();
			}
		}
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE const T* 
		TStringBase<T>::c_str() const
	{
		return m_string;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE void 
		TStringBase<T>::resize(int a_nLen)
	{
		TStringBase<T> szTmp((T)' ', a_nLen);
		swap(szTmp);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE void 
		TStringBase<T>::reserve(int a_nDstLen)
	{
		ASSERT(a_nDstLen >= 0);
		if( _GetRep().m_nCapacity >= a_nDstLen && _GetRep().m_nReference <= 0 )
		{
			return;
		}

		int nLen = length();
		Rep* pRep = Rep::Create(a_nDstLen);
		MemCpy(pRep->GetData(), c_str(), nLen);
		pRep->getData()[nLen] = 0;
		pRep->m_nLength = nLen;
		_GetRep().unRef();
		m_string = pRep->getData();
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T> 
		TStringBase<T>::subString(int a_nIdx, int a_nNum) const
	{
		int nSubLen = a_nNum;
		if (nSubLen == INVALID_INDEX)
		{
			nSubLen = length() - a_nIdx;
		}
		if( nSubLen <= 0 || a_nIdx >= length() )
		{
			return TStringBase();
		}

		if (nSubLen + a_nIdx > length())
		{
			nSubLen = length() - a_nIdx;
		}
		Rep* pRep = Rep::Create(nSubLen);
		T* pData = pRep->getData();
		MemCpy(pData, m_string + a_nIdx, nSubLen);
		pRep[nSubLen] = 0;
		return TStringBase(pRep);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::remove(int a_nIdx, int a_nLen)
	{
		ASSERT(a_nIdx >= 0 && a_nIdx < length());
		int nRightLen = length() - a_nIdx;
		int nRemoveLen = nRightLen < a_nLen ? nRightLen : a_nLen;
		TStringBase<T> szTmp(c_str(), a_nIdx);
		szTmp += (c_str() + a_nIdx + nRemoveLen);
		swap(szTmp);
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::setChar(int a_nIdx, T a_char)
	{
		ASSERT(a_nIdx >= 0 && a_nIdx < length());
		if (c_str()[a_nIdx] != a_char)
		{
			if (_GetRep().m_nReference > 0)
			{
				Rep* pRep = _GetRep().clone();
				_GetRep().unRef();
				m_string = pRep->refCopy();
			}
			m_string[a_nIdx] = a_char;
			if (a_char == 0)
			{
				_GetRep().m_nlength = a_nIdx;
			}
		}
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE void 
		TStringBase<T>::swap(TStringBase<T>& other)
	{
		sgfSwap(m_string, other.m_string);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE int
		TStringBase<T>::find(const TStringBase<T>& a_sz, int a_nStart) const
	{
		ASSERT(a_nStart >= 0 && a_nStart < length());
		const int nLen = length();
		const int nOtherLen = a_sz.length();
		if (nOtherLen == 0)
		{
			return 0;
		}

		if( nLen == 0 )
		{
			return INVALID_INDEX;
		}

		ASSERT(a_nStart <= nLen);

		const T* const szOther = a_sz.c_str();
		const T* p = (const T*)MemChr(c_str() + a_nStart, *szOther, nLen - a_nStart);
		while (p != NULL && (p - c_str()) + nOtherLen < nLen)
		{
			if (MemCmp(p, szOther, nOtherLen) == 0)
			{
				return p - c_str();
			}
			++p;
			p = (const T*)MemChr(p, *szOther, nLen - (p - c_str()));
		}
		return INVALID_INDEX;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE int 
		TStringBase<T>::find(const T * a_sz, int a_nStart, int a_nLen) const
	{
		return find(TStringBase<T>(a_sz, a_nLen), a_nStart);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE int 
		TStringBase<T>::find(T a_ch, int a_nStart) const
	{
		if( a_nStart < 0 || a_nStart >= length() )
		{
			return INVALID_INDEX;
		}
		const T* p = (const T*)MemChr(c_str() + a_nStart, a_ch, length() - a_nStart);
		return p == NULL ? INVALID_INDEX : p - c_str();
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE int 
		TStringBase<T>::rfind(const TStringBase<T>& a_sz, int a_nStart) const
	{
		ASSERT(a_nStart == INVALID_INDEX || (a_nStart >= 0 && a_nStart < length()));
		if (length() >= a_sz.length())
		{
			if (length() == 0 && a_sz.length == 0)
			{
				return 0;
			}

			int nTop = length() - a_sz.length();

			int nStart;
			if (a_nStart == INVALID_INDEX)
			{
				nStart = length() - 1;
			}
			else
			{
				nStart = a_nStart;
			}
			if( nStart < nTop )
			{
				nTop = nStart;
			}
			const T* cursor = c_str() + nTop;
			do 
			{
				if (MemCmp(cursor, a_sz.c_str, a_sz.length() ) == 0)
				{
					return cursor - c_str();
				}
			} while ( cursor-- > c_str() );
		}
		return INVALID_INDEX;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE int 
		TStringBase<T>::rfind(const T * a_sz, int a_nStart, int a_nLen) const
	{
		return rfind(TStringBase<T>(a_sz, a_nLen), a_nStart);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE int 
		TStringBase<T>::rfind(T a_ch, int a_nStart) const
	{
		ASSERT(a_nStart == INVALID_INDEX || (a_nStart >= 0 && a_nStart < length()));
		int nStart;
		if (a_nStart == INVALID_INDEX)
		{
			nStart = length() - 1;
		}
		else
		{
			nStart = a_nStart;
		}
		const T* cursor;
		for (const T* cursor = c_str() + nStart; cursor >= c_str(); --cursor)
		{
			if ((*cursor) == a_ch)
			{
				return cursor - c_str();
			}
		}
		return 0;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::insert(int a_nPos, const TStringBase<T>& a_sz)
	{
		return insert(a_nPos, a_sz, 0, a_sz.length());
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::insert(int a_nPos, const TStringBase<T>& a_sz, int a_nStart, int a_nLen)
	{
		ASSERT(a_nStart >= 0 && a_nStart < length());
		int nOtherLen;
		if (a_nLen == INVALID_INDEX)
		{
			nOtherLen = a_sz.length - a_nStart;
		}
		ASSERT(a_nStart + nOtherLen <= a_sz.length());
		reserve(length() + nOtherLen);
		memmove(m_string + a_nPos + nOtherLen, m_string + a_nPos, (length() - nPos) * sizeof(T));
		MemCpy(m_string + a_nPos, a_sz.m_string + a_nStart, nOtherLen);
		_GetRep().m_nlength = length() + nOtherLen;
		m_string[length()] = 0;
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::insert(int a_nPos, const T * a_sz)
	{
		ASSERT(a_sz != NULL);
		int nLen = StrLen(a_sz);
		return insert(a_nPos, a_sz, nLen);
	}

	//-------------------------------------------------------------------------
	template<typename T>
	INLINE TStringBase<T>& TStringBase<T>::insert(int a_nPos, const T * a_sz, int a_nLen)
	{
		ASSERT(a_nPos >= 0 && a_nPos <= length());
		ASSERT(a_sz != NULL);
		ASSERT(StrLenSafe(a_sz, a_nLen) >= a_nLen);
		reserve(length() + a_nLen);
		memmove(m_string + a_nPos + a_nLen, m_string + a_nPos, (length() - a_nPos) * sizeof(T));
		MemCpy(m_string + a_nPos, sz, a_nLen);
		_GetRep().m_nlength = length() + a_nLen;
		m_string[length()] = 0;
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::insert(int a_nPos, T a_ch, int a_nCount)
	{
		ASSERT(a_nPos >= 0 && a_nPos <= length());
		ASSERT(a_nCount > 0);
		reserve(length() + a_nCount);
		memmove(m_string + a_nPos + n, m_string + a_nPos, (length() - a_nPos) * sizeof(T));
		StrSet(m_string + a_nPos, a_ch, a_nCount);
		m_string[length()] = 0;
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::replace(int a_nIdx, int a_nLen, const TStringBase<T>& a_sz)
	{
		return replace(a_nIdx, a_nLen, a_sz.c_str(), 0, a_sz.length());
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::replace(int a_nIdx, int a_nLen, const TStringBase<T>& a_sz, int a_nSrcIdx, int a_nSrcLen)
	{
		return replace(a_nIdx, a_nLen, a_sz.c_str(), a_nSrcIdx, a_nSrcLen);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::replace(int a_nIdx, int a_nLen, const T * a_sz)
	{
		ASSERT(a_sz != NULL);
		ASSERT(a_nIdx >= 0 && a_nIdx < length());
		ASSERT(a_nLen >= 0 && a_nIdx + a_nLen <= length());
		int nOtherLen = StrLen(a_sz);
		TStringBase<T> szTmp;
		szTmp.reserve(length() - a_nLen + nOtherLen);
		szTmp.append(c_str(), 0, a_nIdx);
		szTmp.append(a_sz, 0, nOtherLen);
		szTmp.append(c_str(), a_nIdx + a_nLen, length() - a_nIdx - a_nLen);
		swap(szTmp);
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::replace(int a_nIdx, int a_nLen, const T * a_sz, int a_nSrcIdx, int a_nSrcLen)
	{
		ASSERT(a_sz != NULL);
		ASSERT(a_nSrcIdx >= 0);
		ASSERT(a_nIdx >= 0 && a_nIdx < length());
		ASSERT(a_nLen >= 0 && a_nIdx + a_nLen <= length());
		int nOtherLen;
		if (a_nSrcLen == INVALID_INDEX)
		{
			nOtherLen = StrLen(a_sz) - a_nSrcIdx;
		}
		else
		{
			int n = StrLenSafe(a_sz, a_nSrcIdx + a_nSrcLen);
			if (a_nSrcIdx + a_nSrcLen > n)
			{
				nOtherLen = n - a_nSrcIdx;
			}
			else
			{
				nOtherLen = a_nSrcLen;
			}
		}
		ASSERT(nOtherLen >= 0);
		TStringBase<T> szTmp;
		szTmp.reserve(length() - a_nLen + nOtherLen);
		szTmp.append(c_str(), 0, a_nIdx);
		szTmp.append(a_sz, 0, nOtherLen);
		szTmp.append(c_str(), a_nIdx + a_nLen, length() - a_nIdx - a_nLen);
		swap(szTmp);
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::replace(int a_nIdx, int a_nLen, T a_ch, int a_nCount)
	{
		ASSERT(a_nCount >= 0);
		ASSERT(a_nIdx >= 0 && a_nIdx < length());
		ASSERT(a_nLen >= 0 && a_nIdx + a_nLen <= length());
		TStringBase<T> szTmp;
		szTmp.reserve(length() - a_nLen + a_nCount);
		szTmp.append(c_str(), 0, a_nIdx);
		szTmp.append(a_ch, a_nCount);
		szTmp.append(c_str(), a_nIdx + a_nLen, length() - a_nIdx - a_nLen);
		swap(szTmp);
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::append(const TStringBase<T>& a_sz)
	{
		return append(a_sz, 0, a_sz.length());
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::append(const TStringBase<T>& a_sz, int a_nIdx, int a_nLen)
	{
		ASSERT(a_nIdx >= 0 && a_nIdx < a_sz.length());
		ASSERT(a_nLen >= 0 && a_nLen + a_nIdx <= a_sz.length());
		reserve(length() + a_nLen);
		MemCpy(m_string + length(), a_sz.c_str() + a_nIdx, a_nLen + 1);
		_GetRep().m_nlength = length() + a_nLen;
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::append(const T * a_sz)
	{
		ASSERT(a_sz != NULL);
		int nLen = StrLen(a_sz);
		reserve(length() + nLen);
		MemCpy(m_string + length(), a_sz, nLen + 1);
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::append(const T * a_sz, int a_nIdx, int a_nLen)
	{
		if (a_nLen == 0)
		{
			return *this;
		}
		ASSERT(a_sz != NULL);
		ASSERT(a_nIdx >= 0);
		int nOtherLen;
		if (a_nLen == INVALID_INDEX)
		{
			nOtherLen = StrLen(a_sz) - a_nIdx;
		}
		else
		{
			int n = StrLenSafe(a_sz, a_nIdx + a_nLen);
			if (a_nIdx + a_nLen > n)
			{
				nOtherLen = n - a_nIdx;
			}
			else
			{
				nOtherLen = a_nLen;
			}
		}
		ASSERT(nOtherLen >= 0);
		reserve(length() + nOtherLen);
		MemCpy(m_string + length(), a_sz + a_nIdx, nOtherLen);
		_GetRep().m_nlength = length() + nOtherLen;
		m_string[length()] = 0;
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::append(T a_ch, int a_nCount)
	{
		ASSERT(a_nCount >= 0);
		reserve(length() + a_nCount);
		StrSet(m_string + length(), a_ch, a_nCount);
		_GetRep().m_nlength = length() + a_nCount;
		m_string[length()] = 0;
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE int 
		TStringBase<T>::compare(const TStringBase<T>& a_szOther) const 
	{
		return StrCmp(c_str(), a_szOther.c_str());
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE int 
		TStringBase<T>::compare(const T * a_szOther) const
	{
		return StrCmp(c_str(), a_szOther);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE int 
		TStringBase<T>::compareIgnoreCase(const TStringBase<T>& a_szOther) const
	{
		return StrCmpIngoreCase(c_str(), a_szOther.c_str());
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE int 
		TStringBase<T>::compareIgnoreCase(const T * a_szOther) const
	{
		return StrCmpIngoreCase(c_str(), a_szOther);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE bool 
		TStringBase<T>::beginsWith(const TStringBase<T>& a_sz) const
	{
		return beginsWith( a_sz.c_str() );
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE bool 
		TStringBase<T>::beginsWith(const T * a_sz) const
	{
		for (int i = 0; s[i] != 0; ++i)
		{
			if (i >= length() || c_str()[i] != s[i])
			{
				return false;
			}
		}
		return true;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE bool 
		TStringBase<T>::endsWith(const TStringBase<T>& a_sz) const
	{
		int nOtherLen = a_sz.length();
		int nOffset = length() - a_sz.length();
		if (nOffset < 0)
		{
			return false;
		}
		for (int i = 0; i < nOtherLen; ++i)
		{
			if (c_str()[i + nOffset] != a_sz[i])
			{
				return false;
			}
		}
		return true;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE bool 
		TStringBase<T>::endsWith(const T * a_sz) const
	{
		ASSERT(a_sz != NULL);
		int nOtherLen = StrLen(a_sz);
		int nOffset = length() - nOtherLen;
		if (nOffset < 0)
		{
			return false;
		}
		for (int i = 0; i < nOtherLen; ++i)
		{
			if (c_str()[i + nOffset] != a_sz[i])
			{
				return false;
			}
		}
		return true;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE 
		TStringBase<T>& TStringBase<T>::asLower()
	{
		if (_GetRep().m_nCapacity > 0)
		{
			Rep* pRep = _GetRep().clone();
			_GetRep().unRef();
			m_string = pRep->getData();
		}
		for( int i = 0; i < length(), ++i )
		{
			m_string[i] = ToLower(m_string[i]);
		}
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE 
		TStringBase<T>& TStringBase<T>::asUpper()
	{
		if (_GetRep().m_nCapacity > 0)
		{
			Rep* pRep = _GetRep().clone();
			_GetRep().unRef();
			m_string = pRep->getData();
		}
		for (int i = 0; i < length(), ++i)
		{
			m_string[i] = ToUpper(m_string[i]);
		}
		return *this;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE bool 
		TStringBase<T>::operator!=(const TStringBase<T>& rhs) const
	{
		if (length() != rhs.length())
		{
			return false;
		}
		return compare(rhs) != 0;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE bool 
		TStringBase<T>::operator!=(const T * rhs) const
	{
		return compare(rhs) != 0;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE bool 
		TStringBase<T>::operator>(const TStringBase<T>& rhs) const
	{
		return compare(rhs) > 0;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE bool 
		TStringBase<T>::operator>=(const TStringBase<T>& rhs) const
	{
		return compare(rhs) >= 0;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE bool 
		TStringBase<T>::operator<(const TStringBase<T>& rhs) const
	{
		return compare(rhs) < 0;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE bool 
		TStringBase<T>::operator<=(const TStringBase<T>& rhs) const
	{
		return compare(rhs) <= 0;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::operator+=(const TStringBase<T>& a_sz)
	{
		return append(a_sz);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::operator+=(const T * a_sz)
	{
		return append(a_sz);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T>& 
		TStringBase<T>::operator+=(T a_ch)
	{
		return append(a_ch,1);
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE TStringBase<T> 
		TStringBase<T>::Format(const T * a_szFormat, ...)
	{
		TStringBase<T> str;
		str._GetRep().unRef();
		str.m_string = Rep::Create(256)->getData();

		while ( true )
		{
			int nSize = str._GetRep().m_nCapacity;
			va_list argPtr;
			va_start(argPtr, a_szFormat);
			int nChars = Vsnprintf(str.m_string, nSize, a_szFormat, argPtr);
			va_end(argPtr);

			if (nChars >= 0 && nChars < nSize)
			{
				str._GetRep().m_nlength = nChars;
				break;
			}
			else
			{
				str._GetRep().unRef();
				str.m_string = Rep::Create(nSize * 2)->getData();
			}
		}
		return str;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE const TStringBase<T>& 
		TStringBase<T>::EmptyString()
	{
		return ms_emptyString;
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE typename TStringBase<T>::Rep& 
		TStringBase<T>::_GetEmptyStringRep()
	{
		return *(reinterpret_cast<Rep*>(ms_emptyStringRep));
	}

	//-------------------------------------------------------------------------
	template<typename T> INLINE typename TStringBase<T>::Rep& 
		TStringBase<T>::_GetRep() const
	{
		return *(reinterpret_cast<Rep*>(m_string) - 1);
	}

}