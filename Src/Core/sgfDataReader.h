#pragma once
/********************************************************************
	created:	2018/06/30
	created:	30:6:2018   16:53
	filename: 	E:\SimpleGameFramework\Src\Core\sgfDataReader.h
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfDataReader
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	class DataReader
	{
	public:
		virtual	~DataReader() {}

		virtual int32	Size() const = 0;
		virtual int32	ReadData(void* pDest, int32 len) = 0;
		virtual void*	ReadData(int32 len) = 0;
		virtual const char*	ReadLine() = 0;
		template<typename T>
		void			Read(T* pDest)
		{
			ReadData(pDest, sizeof(T));
		}
		virtual void*	Data() = 0;
		virtual bool	IsEOF() const = 0;
		virtual int32	Seek(int32 nOffset) = 0;
		virtual int32	GetCurrent() const = 0;
	};
}