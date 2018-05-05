#pragma once
/*************************************
	created: 2018/04/22 09:46 
	filename:	G:\Visual Studio 2015\SimpleGameFrame\Src\Win32\sgfWin32App.h
	file path:	G:\Visual Studio 2015\SimpleGameFrame\Src\Win32
	file base:	sgfWin32App
	file ext:	h	
	author: 	xiexuelong
	
	purpose:
*************************************/

#define WINDOW_CLASS "Win32 Application"

namespace sgf
{
	class Win32App
	{
	public:
		Win32App( const String& a_szAppName = WINDOW_CLASS, WNDPROC a_proc = NULL, int32 a_nVersion = 0, int32 a_nOffsetX = 200, int32 a_nOffsetY = 200 );

	};
}