#pragma once
/*************************************
	created: 2018/04/22 10:14 
	filename:	G:\Visual Studio 2015\SimpleGameFrame\Src\Core\sgfString.h
	file path:	G:\Visual Studio 2015\SimpleGameFrame\Src\Core
	file base:	sgfString
	file ext:	h	
	author: 	xiexuelong
	
	purpose:
*************************************/
int sgfStrLen(const char* s);
int sgfStrLen(const wchar* s);
int sgfStrLen(const unsigned int* s);
namespace sgf
{
	template<typename T>
	class TStringBase
	{
		struct Rep
		{
			T*			getData();
			const T*	getData() const;
			T*			refCopy();
			int			getSize() const;
			void		unRef();
			void		freeMemory();
			int			m_nlength;
			int			m_nCapacity;
			int			m_nReference;
		};
public:
		TStringBase();
		TStringBase(const T* a_str);
		TStringBase(const T* a_str, int a_nLen);
		TStringBase(const TStringBase<T>& a_szSrc);
		~TStringBase();
	protected:
		static Rep&		_GetEmptyStringRep();
	protected:
		T*				m_string;
	protected:
		static unsigned char ms_emptyStringRep[sizeof(int) + sizeof(int) + sizeof(int) + sizeof(T)];
	};

}

#include "sgfString.inl"
