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
		TStringBase::Rep<T>::refCopy()
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
	}

	//----------------------------------------
	template<typename T> INLINE void 
		TStringBase<T>::Rep::freeMemory()
	{
	}


	//----------------------------------------
	//////////////////////////////////////////
	//TStringBase
	//////////////////////////////////////////
	//----------------------------------------

	template<typename T> unsigned char 
		TStringBase<T>::ms_emptyStringRep[sizeof(int) + sizeof(int) + sizeof(int) + sizeof(T)];
	//----------------------------------------
	template<typename T> INLINE
	TStringBase<T>::TStringBase()
	{
		m_string = _GetEmptyStringRep().refCopy();
	}

	template<typename T> INLINE 
		TStringBase<T>::TStringBase(const T * a_str)
	{
		if (a_str != NULL&&a_str[0] != 0)
		{
			int nLen = 
		}
	}

	template<typename T> INLINE 
		TStringBase<T>::TStringBase(const T * a_str, int a_nLen)
	{
	}

	template<typename T> INLINE 
		TStringBase<T>::TStringBase(const TStringBase<T>& a_szSrc)
	{
	}

	template<typename T> INLINE
		TStringBase<T>::~TStringBase()
	{
	}

	template<typename T> INLINE typename TStringBase<T>::Rep& 
		TStringBase<T>::_GetEmptyStringRep()
	{
		// TODO: 在此处插入 return 语句
	}

}