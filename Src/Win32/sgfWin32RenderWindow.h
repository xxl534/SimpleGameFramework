#pragma once
/********************************************************************
	created:	2018/05/06
	created:	6:5:2018   16:34
	filename: 	E:\SimpleGameFramework\Src\Win32\sgfWin32RenderWindow.h
	file path:	E:\SimpleGameFramework\Src\Win32
	file base:	sgfWin32RenderWindow
	file ext:	h
	author:		xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	class RenderWindowNative : public RenderWindow
	{
	public:
		RenderWindowNative(int32 a_nWidth, int32 a_nHeight, WNDPROC a_fnProc, const String& a_szName);
		virtual ~RenderWindowNative();

		virtual void	SwapBuffers(bool a_bWaitForVSync = true) {}
		virtual HWND	GetHWND() const;
		virtual HDC		GetHDC() const;
	protected:
		virtual void	_CreateWindow(int32 a_nWidth, int32 a_nHeight, WNDPROC a_fnProc, const String& a_szName);
		virtual void	_SetupViewPort();

		HWND	m_hWnd;
		HDC		m_hDC;
	};

	class RenderWindowMain : public RenderWindowNative
	{
	public:
		RenderWindowMain(int32 a_nWidth, int32 a_nHeight, WNDPROC a_fnProc, const String& a_szName);
		virtual ~RenderWindowMain();
	};
}