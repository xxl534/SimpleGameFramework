#include "sgfCorePCH.h"
#include "sgfLog.h"
#include "sgfFileWriter.h"


char g_szLogBuffer[] = "\0";
namespace sgf
{
	//-------------------------------------------------------------------------
	Logger::Logger()
		:m_pFileWriter(NULL)
	{

	}

	//-------------------------------------------------------------------------
	Logger::~Logger()
	{
		Destroy();
	}

	//-------------------------------------------------------------------------
	void 
		Logger::Init(const char* a_szFile)
	{
		Destroy();
		m_pFileWriter = FileWriter::OpenWriteFile(a_szFile);
	}

	//-------------------------------------------------------------------------
	void 
		Logger::Destroy()
	{
		SAFE_DELETE(m_pFileWriter);
	}

	//-------------------------------------------------------------------------
	void Logger::Log(const char* a_szLog, int a_nLen)
	{
		if (!m_pFileWriter)
		{
			Init("/game_log.txt");
		}
		if (m_pFileWriter)
		{
			m_pFileWriter->WriteData(a_szLog, a_nLen );
			m_pFileWriter->Save();
		}
	}

	//-------------------------------------------------------------------------
	bool 
		Logger::IsValid()
	{
		return m_pFileWriter != NULL;
	}

}