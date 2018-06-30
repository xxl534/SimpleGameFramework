#pragma once
/********************************************************************
	created:	2018/06/30
	created:	30:6:2018   16:40
	filename: 	E:\SimpleGameFramework\Src\Core\sgfDataWriter.h
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfDataWriter
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	class DataWriter
	{
	public:
		virtual			~DataWriter(){}

		virtual int32	Size() const = 0;
		virtual void	WriteData(const void* a_pData, int32 a_nLen) = 0;
		template<typename T>
		void Write(T a_val)
		{
			WriteData(&a_val, sizeof(T));
		}
	};

	class DataWriterIterator
	{
	public:
		DataWriterIterator( DataWriter* a_pWriter):m_pWriter( a_pWriter ){}

		DataWriterIterator& operator*()
		{
			return *this;
		}

		template<typename T>
		DataWriterIterator& operator=( const T& t)
		{
			m_pWriter->WriteData(&t, sizeof(T));
			return *this;
		}

		DataWriterIterator& operator++(int a_n)
		{
			return *this;
		}

		DataWriterIterator operator++()
		{
			return *this;
		}
	private:
		DataWriter* m_pWriter;
	};
}