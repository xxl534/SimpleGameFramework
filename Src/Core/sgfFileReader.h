#pragma once
/********************************************************************
	created:	2018/07/03
	created:	3:7:2018   7:43
	filename: 	E:\SimpleGameFramework\Src\Core\sgfFileReader.h
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfFileReader
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/
#include "sgfDataReader.h"
#include "sgfString.h"

namespace sgf
{
	class FileReader : public DataReader
	{
	public:
		virtual			~FileReader();

		virtual String	GetFileName() const;
		virtual int32	Size() const;
		virtual int32	ReadData(void* a_pDst, int32 a_nLen);
		virtual void*	ReadData(int32 a_nLen);
		virtual const char*	ReadLine();
		virtual void*	Data();
		virtual bool	IsEOF() const;
		virtual int32	Seek(int32 a_nOffset);
		virtual int32	GetCurrent() const;

		static FileReader*	OpenReadFile(const String& a_szFile);
	protected:
		FileReader();
	protected:
		String	m_szFileName;
		int32	m_nCurrent;
		int32	m_nSize;
		uint8*	m_pData;
	};
}