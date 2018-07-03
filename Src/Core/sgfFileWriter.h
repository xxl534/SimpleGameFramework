#pragma once
/********************************************************************
	created:	2018/07/03
	created:	3:7:2018   8:38
	filename: 	E:\SimpleGameFramework\Src\Core\sgfFileWriter.h
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfFileWriter
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/
#include "sgfDataWriter.h"
#include "sgfString.h"

namespace sgf
{
	class FileWriter : public DataWriter
	{
	public:
		virtual ~FileWriter();

		virtual const String&	GetFileName() const;
		virtual int32			Size() const;
		virtual void			WriteData(const void* a_pDst, int32 a_nLen);

		virtual void			Save();
		
	public:
		static FileWriter*		OpenWriteFile(const String& a_szFile, bool a_bTemp = true);
	private:
		FileWriter();
	private:
		String					m_szFileName;
		int32					m_nSize;
		FILE*					m_pFile;
		bool					m_bTemp;
	};
}