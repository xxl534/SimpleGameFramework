#include "sgfCorePCH.h"
#include "sgfArchive.h"

namespace sgf
{
	String Archive::ms_szRootPath = "";
	String Archive::ms_szWriteRootPath = "";
	String Archive::ms_szAbsRootPathPrefix = "";
	String Archive::ms_szAbsWriteRootPathPrefix = "";
	//-------------------------------------------------------------------------
	Archive::Archive(const String& a_szDir)
	{
		if (IsRelative(a_szDir))
		{
			m_szDir = GetRootPath() + a_szDir;
		}
		else
		{
			m_szDir = a_szDir;
		}
	}

	//-------------------------------------------------------------------------
	Archive::~Archive()
	{

	}

	//-------------------------------------------------------------------------
	const String& 
		Archive::GetPath() const
	{
		return m_szDir;
	}

	//-------------------------------------------------------------------------
	bool 
		Archive::IsDirectoryExist() const
	{
		return IsDirectoryExist(m_szDir);
	}

	//-------------------------------------------------------------------------
	bool 
		Archive::CreateDirectory(const String& a_szDir)
	{
		String szPath = GetWriteFullPath(a_szDir);
		return _RecurMakeDirectory(szPath);
	}

	//-------------------------------------------------------------------------
	const String& 
		Archive::GetRootPath()
	{
		return ms_szRootPath;
	}

	//-------------------------------------------------------------------------
	void 
		Archive::SetRootPath(const String& a_szPath)
	{
		String szPath = a_szPath;
		int nIdx = a_szPath.find(":/");
		if (nIdx == -1)
		{
			nIdx = a_szPath.find(":\\");
		}
		if (nIdx == -1)
		{
			char szCurrDir[512];
			GetCurrentDirectory(512, szCurrDir);
			String strCurDir(szCurrDir);
			szPath = strCurDir + "/" + a_szPath;
		}
		szPath += "/";
		ms_szRootPath = AdjustPath(szPath);
	}

	//-------------------------------------------------------------------------
	String 
		Archive::AdjustPath(const String& a_szPath)
	{
		String szPath = a_szPath;
		int nIdx = -1;
		while ((nIdx = szPath.find('\\')) != INVALID_INDEX)
		{
			szPath.replace(nIdx, 1, '/', 1);
		}
		nIdx = -1;
		while ((nIdx = szPath.find("//")) != INVALID_INDEX)
		{
			szPath.replace(nIdx, 2, '/', 1);
		}
		nIdx = -1;
		TArray<String> arrItem;
		while ((nIdx = szPath.find('/')) != -1)
		{
			arrItem.push_back(szPath.subString(0, nIdx));
			szPath = szPath.subString(nIdx + 1);
		}
		arrItem.push_back(szPath);
		szPath = String::EmptyString();
		for (int i = arrItem.size() - 1; i >= 0; --i)
		{
			String& szItem = arrItem[i];
			if ( szItem.empty() || szItem == ".")
			{
				arrItem.erase(i);
			}
		}
		nIdx = 0;
		while (nIdx < arrItem.size())
		{
			String szItem = arrItem[nIdx];
			if (szItem == "..")
			{
				if (nIdx > 0 && arrItem[nIdx - 1] != "..")
				{
					arrItem.erase(nIdx - 1, 2);
					nIdx = nIdx - 1;
					continue;
				}
			}
			++nIdx;
		}
		for( int i = 0; i < arrItem.size() - 1; ++i )
		{ 
			szPath += (arrItem[i] + "/");
		}
		if (arrItem.size() > 0)
		{
			szPath += arrItem.back();
		}
		return szPath;
	}

	//-------------------------------------------------------------------------
	const String& 
		Archive::GetWriteRootPath()
	{
		return ms_szWriteRootPath;
	}

	//-------------------------------------------------------------------------
	void 
		Archive::SetWriteRootPath(const String& a_szPath)
	{
		String szPath = a_szPath;
		int nIdx = a_szPath.find(":/");
		if (nIdx == -1)
		{
			nIdx = a_szPath.find(":\\");
		}
		if (nIdx == -1)
		{
			char szCurrDir[512];
			GetCurrentDirectory(512, szCurrDir);
			String strCurDir(szCurrDir);
			szPath = strCurDir + "/" + a_szPath;
		}
		szPath += "/";
		ms_szWriteRootPath = AdjustPath(szPath);
	}

	//-------------------------------------------------------------------------
	TArray<String> 
		Archive::_ListFile(const String& a_szDir, const String& a_szFilter)
	{
		TArray<String> arrFile;
		char buf[1024];
		_getcwd(buf, 1024);
		_chdir(a_szDir.c_str());

		_finddata_t data;
		intptr_t hFile;
		memset(&data, 0, sizeof(_finddata_t));
		if ((hFile = _findfirst(a_szFilter.c_str(), &data)) != -1)
		{
			do 
			{
				if ((data.attrib & _A_SUBDIR) == 0 &&
					(data.attrib & _A_SYSTEM) == 0 &&
					(data.attrib & _A_HIDDEN) == 0)
				{
					arrFile.push_back(data.name);
				}
			} while ( _findnext( hFile, &data) == 0 );
		}
		_chdir(buf);
		return arrFile;
	}

	//-------------------------------------------------------------------------
	TArray<String> Archive::_ListDirectory(const String& a_szDir)
	{
		TArray<String> arrDirectory;
		char buf[1024];
		_getcwd(buf, 1024);
		_chdir(a_szDir.c_str());

		_finddata_t data;
		intptr_t hFile;
		memset(&data, 0, sizeof(_finddata_t));
		if ((hFile = _findfirst("*", &data)) != -1)
		{
			do
			{
				if ((data.attrib & _A_SUBDIR) &&
					(data.attrib & _A_SYSTEM) == 0 &&
					(data.attrib & _A_HIDDEN) == 0 &&
					(data.attrib & _A_RDONLY) == 0 &&
					strcmp(".", data.name) != 0 &&
					strcmp("..", data.name) != 0
					)
				{
					arrDirectory.push_back(data.name);
				}
			} while (_findnext(hFile, &data) == 0);
		}
		_chdir(buf);
		return arrDirectory;
	}

	//-------------------------------------------------------------------------
	bool 
		Archive::_RecurMakeDirectory(const String& a_szPath)
	{
		if (IsWriteFileExist(a_szPath))
		{
			return true;
		}
		int nIdx = a_szPath.rfind('/');
		if (nIdx == INVALID_INDEX)
		{
			return false;
		}
		String szParent = a_szPath.subString(0, nIdx);
		if (_RecurMakeDirectory(szParent))
		{
			if (_mkdir(a_szPath.c_str()) == 0)
			{
				return true;
			}
		}
		return false;
	}

	//-------------------------------------------------------------------------
	TArray<String> 
		Archive::ListFile(const String& a_szFilter /*= "*.*"*/, bool a_bCheckRead /*= true*/)
	{
		TArray<String> arrFile = _ListFile(GetWriteFullPath(m_szDir), a_szFilter);

		if (a_bCheckRead)
		{
			THashSet<String> setFile;
			for (TArray<String>::iterator it = arrFile.begin(); it != arrFile.end(); ++it)
			{
				setFile.insert((*it));
			}
			TArray<String> arrReadFile = _ListFile(GetReadFullPath(m_szDir), a_szFilter);
			for (TArray<String>::iterator it = arrReadFile.begin(); it != arrReadFile.end(); ++it)
			{
				setFile.insert((*it));
			}
			arrFile.clear();
			for (THashSet<String>::iterator it = setFile.begin(); it != setFile.end(); ++it)
			{
				arrFile.push_back(it.value());
			}
		}
		return arrFile;
	}

	//-------------------------------------------------------------------------
	TArray<String> Archive::ListDirectory(bool a_bCheckRead /*= true*/)
	{
		TArray<String> arrDir = _ListDirectory(GetWriteFullPath(m_szDir));
		if (arrDir.empty() && a_bCheckRead)
		{
			arrDir = _ListDirectory(GetReadFullPath(m_szDir));
		}
		return arrDir;
	}

	//-------------------------------------------------------------------------
	bool 
		Archive::Delete()
	{
		return Delete(m_szDir);
	}

	//-------------------------------------------------------------------------
	bool 
		Archive::Delete(const String& a_szPath)
	{
		String szWritePath = GetWriteFullPath(a_szPath);
		if (IsWriteDirectoryExist(szWritePath))
		{
			Archive dir(szWritePath);
			TArray<String> arrDirectory = dir.ListDirectory(false);
			for (int i = 0; i < arrDirectory.size(); ++i)
			{
				Delete(a_szPath + "/" + arrDirectory[i]);
			}

			TArray<String> arrFile = dir.ListFile("*.*", false);
			for (int i = 0; i < arrFile.size(); ++i)
			{
				Delete(a_szPath + "/" + arrFile[i]);
			}

			if (rmdir(szWritePath.c_str()) == 0)
			{
				return true;
			}
		}
		else if (IsWriteFileExist(szWritePath))
		{
			if (remove(szWritePath.c_str()) == 0)
			{
				return true;
			}
		}
		return false;
	}

	//-------------------------------------------------------------------------
	void 
		Archive::Rename(const String& a_szOld, const String& a_szNew)
	{
		rename(GetWriteFullPath(a_szOld).c_str(), GetWriteFullPath(a_szNew).c_str());
	}

	//-------------------------------------------------------------------------
	bool 
		Archive::IsRelative(const String& a_szFile)
	{
		if (!a_szFile.length() > 1)
		{
			String szSub = a_szFile.subString(1);
			if (szSub.beginsWith(":/") || szSub.beginsWith(":\\"))
			{
				return false;
			}
		}
		return true;
	}

	//-------------------------------------------------------------------------
	String Archive::GetWriteFullPath(const String& a_szPath )
	{
		if (IsRelative(a_szPath))
		{
			return GetWriteRootPath() + a_szPath;
		}
		else
		{
			if (GetWriteRootPath() != GetRootPath())
			{
				if (!GetRootPath().empty() && a_szPath.beginsWith(GetRootPath()))
				{
					String szFinalPath = a_szPath;
					szFinalPath.replace(0, GetRootPath().length(), GetWriteRootPath());
					return szFinalPath;
				}
			}
		}
		return a_szPath;
	}

	//-------------------------------------------------------------------------
	String Archive::GetReadFullPath(const String& a_szPath)
	{
		if (IsRelative(a_szPath))
		{
			if (IsWriteFileExist(a_szPath))
			{
				return GetWriteFullPath(a_szPath);
			}
			if (IsWriteDirectoryExist(a_szPath))
			{
				return GetWriteFullPath(a_szPath);
			}
			return GetRootPath() + a_szPath;
		}
		return a_szPath;
	}

	//-------------------------------------------------------------------------
	bool 
		Archive::IsFileExist(const String& a_szFile)
	{
		if (a_szFile.empty())
		{
			return false;
		}

		String szWriteFile = GetWriteFullPath(a_szFile);
		FILE* pFile = fopen(szWriteFile.c_str(), "rb");
		if (!pFile)
		{
			pFile = fopen(GetReadFullPath(a_szFile).c_str(), "rb");
		}

		if (pFile)
		{
			fclose(pFile);
			return true;
		}
		return false;
	}

	bool Archive::IsWriteFileExist(const String& a_szFile)
	{
		if (a_szFile.empty())
		{
			return false;
		}

		String szWritePath = GetWriteFullPath(a_szFile);
		FILE* pFile = fopen(szWritePath.c_str(), "rb");
		if (pFile)
		{
			fclose(pFile);
			return true;
		}
		return false;
	}

	//-------------------------------------------------------------------------
	bool
		Archive::IsDirectoryExist(const String& a_szDir)
	{
		if (a_szDir.empty())
		{
			return false;
		}
		String szWritePath = GetWriteFullPath(a_szDir);
		String szReadPath = GetReadFullPath(a_szDir);
		_finddata_t data;
		intptr_t hFile;
		if ((hFile = _findfirst(szWritePath.c_str, &data)) != -1 ||
			(hFile = _findfirst(szReadPath.c_str(), &data)) != -1)
		{
			_findclose(hFile);
			return (data.attrib&_A_SUBDIR) != 0;
		}
		return false;
	}

	//-------------------------------------------------------------------------
	bool
		Archive::IsWriteDirectoryExist(const String & a_szDir)
	{
		if (a_szDir.empty())
		{
			return false;
		}
		String szWritePath = GetWriteFullPath(a_szDir);
		_finddata_t data;
		intptr_t hFile;
		if ((hFile = _findfirst(szWritePath.c_str, &data)) != -1 )
		{
			_findclose(hFile);
			return (data.attrib&_A_SUBDIR) != 0;
		}
		return false;
	}
}