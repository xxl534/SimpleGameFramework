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


namespace sgf
{
	int		StrLen(const char* s);
	int		StrLen(const wchar* s);
	int		Vsnprintf(char* a_szBuff, int a_nCount, const char* a_szFormat, va_list a_args);
	int		Vsnprintf(wchar* a_szBuff, int a_nCount, const wchar* a_szFormat, va_list a_args);
	char*	MemChr(const char* a_sz, char a_ch, int a_nCount);
	wchar*	MemChr(const wchar* a_sz, wchar a_ch, int a_nCount);
	void	StrSet(char* a_szDst, char a_ch, int a_nCount);
	void	StrSet(wchar* a_szDst, wchar a_ch, int a_nCount);
	int		StrCmp(const char* a_szSrc, const char* a_szDst);
	int		StrCmp(const wchar* a_szSrc, const wchar* a_szDst);
	char	ToLower(char a_ch);
	wchar	ToLower(wchar a_ch);
	char	ToUpper(char a_ch);
	wchar	ToUpper(wchar a_ch);
	template<typename T> int MemCmp(const T* src, const T* dst, int a_nLen)
	{
		return memcmp(src, dst, a_nLen * sizeof(T));
	}
	template<typename T> void MemCpy(T* dst, const T* src, int n)
	{
		memcpy(dst, src, sizeof(T) * n);
	}
	template<typename T> int StrLenSafe(const T* sz, int len)
	{
		for (int i = 0; i < len; ++i)
		{
			if (sz[i] == 0)
			{
				return i;
			}
		}
		return len;
	}
	template<typename T> void StrSet(T* dst, T ch, int len )
	{
		memset(dst, ch, sizeof(T)*len);
	}
	template<typename T> int StrCmpIngoreCase(const T* a_szSrc, const T* a_szDst)
	{
		ASSERT(a_szSrc != NULL && a_szDst != NULL);
		if (a_szSrc == a_szDst)
		{
			return 0;
		}
		int nIdx = 0;
		while (a_szSrc[nIdx] != 0 || a_szDst[nIdx] != 0)
		{
			int n = ToLower(a_szSrc[nIdx]) - ToLower(a_szSrc[nIdx]);
			if (n != 0)
			{
				return n;
			}
			++nIdx;
		}
		return 0;
	}

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
			Rep*		clone() const;
			static Rep*	Create(int a_nLen);
			int			m_nlength;
			int			m_nCapacity;
			int			m_nReference;
		};
	public:
		TStringBase();
		TStringBase(const T* a_str);
		TStringBase(const T* a_str, int a_nLen);
		TStringBase(T a_char, int a_nLen);
		TStringBase(const TStringBase<T>& a_szSrc);
		~TStringBase();

		TStringBase<T>&	operator=(const TStringBase<T>& rhs);
		TStringBase<T>&	operator=(const T* rhs);
		T				operator[](int a_nIdx) const;

		int				length() const;
		void			clear();
		bool			empty() const;
		void			printf(const T* a_szFormat, ...);
		const T*		c_str() const;
		void			resize(int a_nLen);
		void			reserve(int a_nLen);

		TStringBase<T>	subString(int a_nIdx, int a_nNum = INVALID_INDEX) const;
		TStringBase<T>& remove(int a_nIdx, int a_nLen = 1 );
		TStringBase<T>& setChar(int a_nIdx, T a_char);
		void			swap(TStringBase<T>& other);

		int				find(const TStringBase<T>& a_sz, int a_nStart = 0) const;
		int				find(const T* a_sz, int a_nStart = 0, int a_nLen = INVALID_INDEX) const;
		int				find(T a_ch, int a_nStart = 0) const;
		int				rfind(const TStringBase<T>& a_sz, int a_nStart = INVALID_INDEX) const;
		int				rfind(const T* a_sz, int a_nStart = INVALID_INDEX, int a_nLen = INVALID_INDEX) const;
		int				rfind(T a_ch, int a_nStart = INVALID_INDEX) const;

		TStringBase<T>&	insert(int a_nPos, const TStringBase<T>& a_sz);
		TStringBase<T>&	insert(int a_nPos, const TStringBase<T>& a_sz, int a_nStart, int a_nLen = INVALID_INDEX);
		TStringBase<T>&	insert(int a_nPos, const T* a_sz);
		TStringBase<T>&	insert(int a_nPos, const T* a_sz, int a_nLen);
		TStringBase<T>&	insert(int a_nPos, T a_ch, int a_nCount = 1);

		TStringBase<T>&	replace(int a_nIdx, int a_nLen, const TStringBase<T>& a_sz);
		TStringBase<T>&	replace(int a_nIdx, int a_nLen, const TStringBase<T>& a_sz, int a_nSrcIdx, int a_nSrcLen);
		TStringBase<T>&	replace(int a_nIdx, int a_nLen, const T* a_sz);
		TStringBase<T>&	replace(int a_nIdx, int a_nLen, const T* a_sz, int a_nSrcIdx, int a_nSrcLen);
		TStringBase<T>&	replace(int a_nIdx, int a_nLen, T a_ch, int a_nCount);

		TStringBase<T>&	append(const TStringBase<T>& a_sz);
		TStringBase<T>&	append(const TStringBase<T>& a_sz, int a_nIdx, int a_nLen);
		TStringBase<T>&	append(const T* a_sz);
		TStringBase<T>&	append(const T* a_sz, int a_nIdx, int a_nLen);
		TStringBase<T>&	append(T a_ch, int a_nCount = 1);

		int				compare(const TStringBase<T>& a_szOther) const;
		int				compare(const T* a_szOther) const;
		int				compareIgnoreCase(const TStringBase<T>& a_szOther) const;
		int				compareIgnoreCase(const T* a_szOther) const;

		bool			beginsWith(const TStringBase<T>& a_sz) const;
		bool			beginsWith(const T* a_sz) const;
		bool			endsWith(const TStringBase<T>& a_sz) const;
		bool			endsWith(const T* a_sz) const;

		TStringBase<T>&	asLower();
		TStringBase<T>&	asUpper();

		bool			operator!=(const TStringBase<T>& rhs) const;
		bool			operator!=(const T* rhs) const;
		bool			operator> (const TStringBase<T>& rhs) const;
		bool			operator>=(const TStringBase<T>& rhs) const;
		bool			operator< (const TStringBase<T>& rhs) const;
		bool			operator<=(const TStringBase<T>& rhs) const;
		TStringBase<T>&	operator+=(const TStringBase<T>& a_sz);
		TStringBase<T>&	operator+=(const T* a_sz );
		TStringBase<T>&	operator+=(T a_ch);

		friend TStringBase	operator+(const TStringBase& lhs, const TStringBase& rhs)
		{
			int nlen = lhs.length() + rhs.length();
			Rep * pRep = Rep::Create(nlen);
			T* p = pRep->getData();
			MemCpy(p, lhs.c_str(), lhs.length());
			MemCpy(p + lhs.length(), rhs.c_str(), rhs.length() + 1);
			return TStringBase(pRep);
		}
		friend bool			operator==(const TStringBase& lhs, const TStringBase& rhs)
		{
			return lhs.length() == rhs.length() ? lhs.compare(rhs) == 0 : false;
		}
		friend bool			operator==(const TStringBase& lhs, const T* rhs)
		{
			return lhs.compare(rhs ? rhs : "") == 0;
		}
		friend bool			operator==(const T* lhs, const TStringBase& rhs)
		{
			return rhs.compare(lhs ? lhs : "") == 0;
		}
	public:
		static TStringBase<T> Format(const T* a_szFormat, ...);
		static const TStringBase<T>& EmptyString();
	protected:
		static Rep&		_GetEmptyStringRep();
	protected:
		explicit		TStringBase(Rep* a_pRep);
		Rep&			_GetRep() const;
	protected:
		T*				m_string;
	protected:
		static unsigned char	ms_emptyStringRep[sizeof(int) + sizeof(int) + sizeof(int) + sizeof(T)];
		static TStringBase<T>	ms_emptyString;
	};

	typedef TStringBase<char>	CString;
	typedef TStringBase<wchar>	WString;

	typedef CString				String;
}

#include "sgfString.inl"
