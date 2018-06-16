#include "sgfWin32AppPCH.h"
#include "sgfWin32RenderWindow.h"

namespace sgf
{
	//-------------------------------------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//Win32RenderWindow
	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------

	RenderWindowNative::RenderWindowNative(int32 a_nWidth, int32 a_nHeight, WNDPROC a_fnProc, const String& a_szName)
		:m_hWnd( 0 )
		, m_hDC( 0 )
	{
		m_nWidth = a_nWidth;
		m_nHeight = a_nHeight;
		_CreateWindow(a_nWidth, a_nHeight, a_fnProc, a_szName);
		_SetupViewPort();
	}

	//-------------------------------------------------------------------------
	RenderWindowNative::~RenderWindowNative()
	{
		ReleaseDC(m_hWnd, m_hDC);
		DestroyWindow(m_hWnd);
	}

	//-------------------------------------------------------------------------
	HWND 
		RenderWindowNative::GetHWND() const
	{
		return m_hWnd;
	}

	//-------------------------------------------------------------------------
	HDC 
		RenderWindowNative::GetHDC() const
	{
		return m_hDC;
	}

	//-------------------------------------------------------------------------
	void 
		RenderWindowNative::_CreateWindow(int32 a_nWidth, int32 a_nHeight, WNDPROC a_fnProc, const String& a_szName)
	{
		WNDCLASS wc;
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = a_fnProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetModuleHandle(0);
		wc.hIcon = LoadIcon(0, IDI_WINLOGO);
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		wc.lpszMenuName = 0;
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.lpszClassName = a_szName.c_str();

		RegisterClass(&wc);

		RECT sRect;
		SetRect(&sRect, 0, 0, a_nWidth, a_nHeight);
		AdjustWindowRect(&sRect, WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU | WS_POPUP , false);
		m_hWnd = CreateWindow(a_szName.c_str(), a_szName.c_str(), WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU | WS_POPUP,
			0, 0, sRect.right - sRect.left, sRect.bottom - sRect.top, NULL, NULL, GetModuleHandle(0), NULL);

		m_hDC = GetDC(m_hWnd);
		DragAcceptFiles(m_hWnd, true);
		
		if (m_hDC == 0)
		{
			MessageBox(0, "Failed to create device context", "Error", MB_OK | MB_ICONEXCLAMATION);
			m_bValid = false;
			return;
		}

	}

	//-------------------------------------------------------------------------
	void 
		RenderWindowNative::_SetupViewPort()
	{
		m_sViewportDesc.Setup(0, 0, m_nWidth, m_nHeight);
	}

	//-------------------------------------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//RenderWindowMain
	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------
	RenderWindowMain::RenderWindowMain(int32 a_nWidth, int32 a_nHeight, WNDPROC a_fnProc, const String& a_szName)
		:RenderWindowNative( a_nWidth, a_nHeight, a_fnProc, a_szName )
	{

	}

	RenderWindowMain::~RenderWindowMain()
	{

	}

}