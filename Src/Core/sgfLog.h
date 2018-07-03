#pragma once
/********************************************************************
	created:	2018/07/03
	created:	3:7:2018   8:14
	filename: 	E:\SimpleGameFramework\Src\Core\sgfLog.h
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfLog
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/
#include <Windows.h>
#include <stdlib.h>
extern char g_szLogBuffer[4096];
#	ifdef _LOGFILE
#		define LOG_INFO_DEBUG(...)		{int len=sprintf(g_szLogBuffer,__VA_ARGS__);cs::Logger::Instance().Log(g_szLogBuffer,len);}
#		define LOG_WARNNING_DEBUG(...)	{int len=sprintf(g_szLogBuffer,__VA_ARGS__);cs::Logger::Instance().Log(g_szLogBuffer,len);}
#		define LOG_ERROR_DEBUG(...)		{int len=sprintf(g_szLogBuffer,__VA_ARGS__);cs::Logger::Instance().Log(g_szLogBuffer,len);}
#		define LOG_CALL_DEBUG			{int len=sprintf(g_szLogBuffer,"%s,%d,%s\n",__FUNCTION__,__LINE__,__FILE__);cs::Logger::Instance().Log(g_szLogBuffer,len);}
#	elif defined(_DEBUG)
#		define LOG_INFO_DEBUG(...)		{sprintf(g_szLogBuffer,__VA_ARGS__);sprintf(g_szLogBuffer,"%s\n",g_szLogBuffer);OutputDebugStringA(g_szLogBuffer);}
#		define LOG_WARNNING_DEBUG(...)	{sprintf(g_szLogBuffer,__VA_ARGS__);OutputDebugStringA(g_szLogBuffer);}
#		define LOG_ERROR_DEBUG(...)		{sprintf(g_szLogBuffer,__VA_ARGS__);OutputDebugStringA(g_szLogBuffer);}
#		define LOG_CALL_DEBUG			{sprintf(g_szLogBuffer,"%s,%d,%s\n",__FUNCTION__,__LINE__,__FILE__);OutputDebugStringA(g_szLogBuffer);}
#	else
#		define	LOG_INFO_DEBUG(...)
#		define LOG_WARNNING_DEBUG(...)
#		define LOG_ERROR_DEBUG(...)
#		define LOG_CALL_DEBUG
#	endif
#	define LOG_INFO(...)				{sprintf(g_szLogBuffer,__VA_ARGS__);sprintf(g_szLogBuffer,"%s\n",g_szLogBuffer);fprintf(stdout,g_szLogBuffer);}
#	define LOG_WARNNING(...)			{sprintf(g_szLogBuffer,__VA_ARGS__);fprintf(stdout,g_szLogBuffer);}
#	define LOG_ERROR(...)				{sprintf(g_szLogBuffer,__VA_ARGS__);fprintf(stderr,g_szLogBuffer);}
#	define LOG_CALL						{sprintf(g_szLogBuffer,"%s,%d,%s\n",__FUNCTION__,__LINE__,__FILE__);fprintf(stdout,g_szLogBuffer);}
#	ifdef _DEBUG
#		define LOG_WIN32_CONSOLE_DEBUG(...)	{printf(__VA_ARGS__);}
#	else
#		define LOG_WIN32_CONSOLE_DEBUG(...)
#	endif
#	define LOG_MESSAGEBOX(...)			{ cs::String szInfo = cs::String::Format( __VA_ARGS__ ); MessageBox( NULL, szInfo.c_str(),"", MB_OK ); }

#include "sgfSingleton.h"

namespace sgf
{
	class Logger : public TSingleton<Logger>
	{
		friend class TSingleton<Logger>;
	public:

		void		Init(const char* a_szFile);
		void		Destroy();

		void		Log(const char* a_szLog, int a_nLen);
		bool		IsValid();
	private:
		Logger();
		~Logger();
	private:
		class FileWriter*	m_pFileWriter;
	};
}