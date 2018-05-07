#include "sgfWin32AppPCH.h"
#include "sgfWin32App.h"
#include <DbgHelp.h>
#include <time.h>

#pragma comment(lib, "DbgHelp.lib")

int g_nVersion = 0;
namespace sgf
{
	LRESULT CALLBACK _WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
		return 0;
	}

	//-------------------------------------------------------------------------
	LONG WINAPI _TopLevelExceptionFilter(struct _EXCEPTION_POINTERS* a_pExceptionInfo)
	{
		LONG ret = EXCEPTION_CONTINUE_SEARCH;

		time_t nowTime;
		time(&nowTime);
		struct tm t;
		localtime_s( &t, &nowTime);
		char szFile[1024] = { 0 };
		sprintf_s(szFile, "%d %4d.%02d.%02d.%02d.%02d.%02d.dmp",
			g_nVersion,
			t.tm_year + 1900,
			t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
		HANDLE hFile = ::CreateFile(szFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFile != INVALID_HANDLE_VALUE)
		{
			MINIDUMP_EXCEPTION_INFORMATION exInfo;
			exInfo.ThreadId = ::GetCurrentThreadId();
			exInfo.ExceptionPointers = a_pExceptionInfo;
			exInfo.ClientPointers = NULL;

			BOOL bOk = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpWithFullMemory, &exInfo, NULL, NULL);
			if (bOk)
			{
				ret = EXCEPTION_EXECUTE_HANDLER;
			}
			::CloseHandle(hFile);
		}
		return ret;
	}

	//-------------------------------------------------------------------------
	BOOL WINAPI _ConsoleHandle(DWORD CEvent)
	{
		if (CEvent == CTRL_CLOSE_EVENT)
		{
			Application::Instance().Exit();
			Sleep(10000);
		}
		return TRUE;
	}
	//-------------------------------------------------------------------------
	Win32App::Win32App(const String& a_szAppName /*= WINDOW_CLASS*/, WNDPROC a_proc /*= NULL*/, int32 a_nVersion, int32 a_nOffsetX /*= 200*/, int32 a_nOffsetY /*= 200 */)
		:m_szAppName( a_szAppName )
		,m_fnProc( a_proc ? a_proc : _WndProc )
		,m_nOffsetX( a_nOffsetX )
		,m_nOffsetY( a_nOffsetY )
		,m_bExiting( false )
		,m_pGameWorld(NULL)
		,m_nWidth( DEFAULT_WINDOW_WIDTH )
		,m_nHeight(DEFAULT_WINDOW_HEIGHT)
	{
		g_nVersion = a_nVersion;
#ifndef _DEBUG
		::SetUnhandledExceptionFilter(_TopLevelExceptionFilter);
#endif
	}

	//-------------------------------------------------------------------------
	Win32App::~Win32App()
	{

	}

	//-------------------------------------------------------------------------
	void 
		Win32App::Initialize(int argc, char** argv, GameWorld* a_pWorld /*= NULL*/, int a_nWidth /*= 1280*/, int a_nHeight /*= 720*/)
	{
		if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)_ConsoleHandle, TRUE) == FALSE)
		{
			printf("The console handler is not working!");
		}
		_LoadGameWorld(argc, argv, a_pWorld, a_nWidth, a_nHeight);
	}

	void Win32App::Run()
	{
		
	}

	void Win32App::Destroy()
	{
		
	}

	void Win32App::Exit()
	{
		
	}

	void Win32App::_LoadGameWorld(int argc, char** argv, GameWorld* a_pWorld, int a_nWidth, int a_nHeight)
	{
		m_nWidth = a_nWidth;
		m_nHeight = a_nHeight;
	}

}