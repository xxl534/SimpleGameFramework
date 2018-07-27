#include "sgfCorePCH.h"
#include "sgfString.h"

namespace sgf
{ 
	//----------------------------------------
	int
		StrLen(const char * s)
	{
		ASSERT(s);
		return strlen(s);
	}

	//----------------------------------------
	int 
		StrLen(const wchar * s)
	{
		ASSERT(s);
		size_t len = 0;
		while ((*s++) != '\0')
		{
			++len;
		}
		return len;
	}

	//-------------------------------------------------------------------------
	int 
		Vsnprintf(char* a_szBuff, int a_nCount, const char* a_szFormat, va_list a_args)
	{
		int nRet = 0;
#ifdef _MSC_VER
		nRet = _vsprintf_p(a_szBuff, a_nCount, a_szFormat, a_args);
#else
		nRet = vsprintf(a_szBuff, a_nCount, a_szFormat, a_args);
#endif
		return nRet;
	}

	//-------------------------------------------------------------------------
	int 
		Vsnprintf(wchar* a_szBuff, int a_nCount, const wchar* a_szFormat, va_list a_args)
	{
#ifdef _MSC_VER
		return _vswprintf_p(a_szBuff, a_nCount, a_szFormat, a_args);
#else
		return 0;
#endif // _MSC_VER
	}

	//-------------------------------------------------------------------------
	char* 
		MemChr(const char* a_sz, char a_ch, int a_nCount)
	{
		return (char*)memchr(a_sz, a_ch, a_nCount);
	}

	//-------------------------------------------------------------------------
	wchar* 
		MemChr(const wchar* a_sz, wchar a_ch, int a_nCount)
	{
		wchar* sz = (wchar*)a_sz;
		for (int i = 0; i < a_nCount; ++i)
		{
			if (sz[i] == a_ch)
			{
				return (sz + i);
			}
			
			if( sz[i] == 0)
			{
				return NULL;
			}
		}
		return NULL;
	}

	//-------------------------------------------------------------------------
	void 
		StrSet(char* a_szDst, char a_ch, int a_nCount)
	{
		memset(a_szDst, a_ch, a_nCount);
	}

	//-------------------------------------------------------------------------
	void 
		StrSet(wchar * a_szDst, wchar a_ch, int a_nCount)
	{
		for (int i = 0; i < a_nCount; ++i)
		{
			a_szDst[i] = a_ch;
		}
	}

	//-------------------------------------------------------------------------
	int 
		StrCmp(const char* a_szSrc, const char* a_szDst)
	{
		ASSERT(a_szDst != NULL && a_szSrc != NULL);
		return strcmp(a_szSrc, a_szDst);
	}

	//-------------------------------------------------------------------------
	int 
		StrCmp(const wchar* a_szSrc, const wchar* a_szDst)
	{
		ASSERT(a_szDst != NULL && a_szSrc != NULL);
		if( a_szDst == a_szSrc )
		{
			return 0;
		}
		int nIdx = 0;
		while (a_szSrc[nIdx] != 0 || a_szDst[nIdx] != 0)
		{
			int n = a_szSrc[nIdx]- a_szSrc[nIdx];
			if (n != 0)
			{
				return n;
			}
			++nIdx;
		}
		return 0;
	}

	//-------------------------------------------------------------------------
	char 
		ToLower(char a_ch)
	{
		return (a_ch >= 'A'&&a_ch <= 'Z')
			? (char)(a_ch + ('a' - 'A'))
			: a_ch;
	}

	//-------------------------------------------------------------------------
	wchar 
		ToLower(wchar a_ch)
	{
		return (a_ch >= L'A'&&a_ch <= L'Z')
			? (wchar)(a_ch + (L'a' - L'A'))
			: a_ch;
	}

	//-------------------------------------------------------------------------
	char 
		ToUpper(char a_ch)
	{
		return (a_ch >= 'A'&&a_ch <= 'Z')
			? (char)(a_ch - ('a' - 'A'))
			: a_ch;
	}

	//-------------------------------------------------------------------------
	wchar 
		ToUpper(wchar a_ch)
	{
		return (a_ch >= L'A'&&a_ch <= L'Z')
			? (wchar)(a_ch - (L'a' - L'A'))
			: a_ch;
	}

	static wchar fs_szWideBuffer[4096];
	//-------------------------------------------------------------------------
	WString 
		StringHelper::Utf8ToUtf16(const CString& a_szUtf8)
	{
		MultiByteToWideChar(CP_UTF8, 0, a_szUtf8.c_str(), -1, fs_szWideBuffer, 4096);
		return WString(fs_szWideBuffer, 4096);
	}

	//-------------------------------------------------------------------------
	WString 
		StringHelper::AnsiToUtf16(const CString& a_szAnsi)
	{
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, a_szAnsi.c_str(), -1, fs_szWideBuffer, 4096);
		return WString(fs_szWideBuffer, 4096);
	}

}
