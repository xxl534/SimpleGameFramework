#include "sgfCorePCH.h"
#include "sgfArchive.h"

namespace sgf
{

	Archive::Archive(const String& a_szDir)
	{

	}

	Archive::~Archive()
	{

	}

	const String& Archive::GetPath() const
	{

	}

	bool Archive::IsDirectoryExist() const
	{

	}

	bool Archive::IsDirectoryExist(const String& a_szDir)
	{

	}

	bool Archive::CreateDirectory(const String& a_szDir)
	{

	}

	const String& Archive::GetResourceRootPath()
	{

	}

	void Archive::SetResourceRootPath(const String& a_szPath)
	{

	}

	sgf::String Archive::AdjustPath(const String& a_szPath)
	{

	}

	const String& Archive::GetWriteRootPath()
	{

	}

	void Archive::SetWriteRootPath(const String& a_szPath)
	{

	}

	TArray<String> Archive::_ListFile(const String& a_szDir, const String& a_szFilter)
	{

	}

	TArray<String> Archive::_ListReadFile(const String& a_szDir, const String& a_szFilter)
	{

	}

	TArray<String> Archive::_ListDirectory(const String& a_szDir)
	{

	}

	TArray<String> Archive::_ListReadDirectory(const String& a_szDir)
	{

	}

	bool Archive::_RecurMakeDirectory(const String& a_szPath)
	{

	}

	sgf::String Archive::ms_szRootPath;

	sgf::String Archive::ms_szWriteRootPath;

	sgf::String Archive::ms_szAbsRootPathPrefix;

	sgf::String Archive::ms_szAbsWriteRootPathPrefix;

	TArray<String> Archive::ListFile(const String& a_szFilter /*= "*.*"*/, bool a_bCheckRead /*= true*/)
	{

	}

	TArray<String> Archive::ListDirectory(bool a_bCheckRead /*= true*/)
	{

	}

	bool Archive::Delete()
	{

	}

	bool Archive::Delete(const String& a_szPath)
	{

	}

	void Archive::Rename(const String& a_szOld, const String& a_szNew)
	{

	}

	bool Archive::IsRelative(const String& a_szFile)
	{

	}

	sgf::String Archive::GetWriteFullPath(const String& a_szFile)
	{

	}

	sgf::String Archive::GetReadFullPath(const String& a_szFile)
	{

	}

	bool Archive::IsFileExist(const String& a_szFile)
	{

	}

	bool Archive::IsWriteFileExist(const String& a_szFile)
	{

	}

}