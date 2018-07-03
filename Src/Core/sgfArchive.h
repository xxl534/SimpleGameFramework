#pragma once
/********************************************************************
	created:	2018/07/03
	created:	3:7:2018   8:39
	filename: 	E:\SimpleGameFramework\Src\Core\sgfArchive.h
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfArchive
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/
#include "sgfString.h"
#include "sgfArray.h"

namespace sgf
{
	class Archive
	{
	public:			
		Archive(const String& a_szDir);
		virtual		~Archive();

		virtual const String&	GetPath() const;
		virtual bool			IsDirectoryExist() const;
		virtual TArray<String>	ListFile(const String& a_szFilter = "*.*", bool a_bCheckRead = true);
		virtual TArray<String>	ListDirectory(bool a_bCheckRead = true);
		virtual bool			Delete();
	public:
		static bool				Delete(const String& a_szPath);
		static void				Rename(const String& a_szOld, const String& a_szNew);
		static bool				IsRelative(const String& a_szFile);
		static String			GetWriteFullPath(const String& a_szFile);
		static String			GetReadFullPath(const String& a_szFile);
		static bool				IsFileExist(const String& a_szFile);
		static bool				IsWriteFileExist(const String& a_szFile);
		static bool				IsDirectoryExist(const String& a_szDir);
		static bool				CreateDirectory(const String& a_szDir);
		static const String&	GetResourceRootPath();
		static void				SetResourceRootPath(const String& a_szPath);
		static String			AdjustPath(const String& a_szPath);
		static const String&	GetWriteRootPath();
		static void				SetWriteRootPath(const String& a_szPath);
	private:
		TArray<String>			_ListFile(const String& a_szDir, const String& a_szFilter);
		TArray<String>			_ListReadFile(const String& a_szDir, const String& a_szFilter);
		TArray<String>			_ListDirectory(const String& a_szDir);
		TArray<String>			_ListReadDirectory(const String& a_szDir);
	private:
		static bool				_RecurMakeDirectory(const String& a_szPath);
	private:
		String					m_szDir;
	private:
		static String			ms_szRootPath;
		static String			ms_szWriteRootPath;
		static String			ms_szAbsRootPathPrefix;
		static String			ms_szAbsWriteRootPathPrefix;

	};
}