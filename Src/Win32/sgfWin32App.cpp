#include "sgfWin32AppPCH.h"
#include "sgfWin32App.h"
#include "sgfWin32RenderWindow.h"
#include <DbgHelp.h>
#include <time.h>
#include <d3d11.h>
#include <dxgi.h>

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
		,m_pRenderWindow(NULL)
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

	//-------------------------------------------------------------------------
	void 
		Win32App::Run()
	{
		/*if (m_pGameWorld)
		{

		}*/
		ShowWindow(m_pRenderWindow->GetHWND(), SW_NORMAL);
		UpdateWindow(m_pRenderWindow->GetHWND());

		// 			cs::RenderWindowSub* pRenderWindowSub = static_cast<cs::RenderWindowSub*>( 
		// 				m_pGameWorld->GetCameraByID( 1 )->GetRenderWindow()
		// 				);
		// 			ShowWindow( pRenderWindowSub->GetHWnd() , SW_NORMAL);
		// 			UpdateWindow( pRenderWindowSub->GetHWnd() );

		while (!IsExiting()) {

			MSG msg;
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			//else {
			//	//SendMessage(hWnd,WM_PAINT,0,0);
			//	//eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);

			//	_Update();
			//	///*
			//	//Swap Buffers.
			//	//Brings to the native display the current render surface.
			//	// */
			//	eglSwapBuffers(eglDisplay, eglSurface);
			//}
		}
	}

	//-------------------------------------------------------------------------
	void Win32App::Destroy()
	{
		
	}

	//-------------------------------------------------------------------------
	void 
		Win32App::Exit()
	{
		m_bExiting = true;
	}

	//-------------------------------------------------------------------------
	bool 
		Win32App::IsExiting()
	{
		return m_bExiting;
	}

	void Win32App::_LoadGameWorld(int argc, char** argv, GameWorld* a_pWorld, int a_nWidth, int a_nHeight)
	{
		m_nWidth = a_nWidth;
		m_nHeight = a_nHeight;

		m_pRenderWindow = new RenderWindowMain(m_nWidth, m_nHeight, m_fnProc, WINDOW_CLASS);
	}

	//-------------------------------------------------------------------------
	bool 
		Win32App::_SetupDirectX11( HWND a_hwnd)
	{
		ID3D11Device* pDX11Device;
		ID3D11DeviceContext* pDX11DeviceContext;
		UINT uCreateDeviceFlag = 0;
#if defined(_DEBUG)
		uCreateDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		D3D_FEATURE_LEVEL featureLevel;
		HRESULT hr = D3D11CreateDevice(
			0,
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			uCreateDeviceFlag,
			0, 0,
			D3D11_SDK_VERSION,
			&pDX11Device,
			&featureLevel,
			&pDX11DeviceContext
		);

		if (FAILED(hr))
		{
			MessageBox(0, "D3D11CreateDevice Failed!", 0, 0);
			return false;
		}

		if (featureLevel != D3D_FEATURE_LEVEL_11_0)
		{
			MessageBox(0, "Direct3D feature level 11 unsupported!", 0, 0);
			return false;
		}

		UINT uMsaa4xQuality;
		hr = pDX11Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &uMsaa4xQuality);
		if (FAILED(hr))
		{
			MessageBox(0, "D3D11 check device MSAA level failed!", 0, 0);
			return false;
		}
		ASSERT(uMsaa4xQuality > 0);

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		swapChainDesc.BufferDesc.Width = m_nWidth;
		swapChainDesc.BufferDesc.Height = m_nHeight;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		bool bEnableAA;
		if (bEnableAA)
		{
			swapChainDesc.SampleDesc.Count = 4;
			swapChainDesc.SampleDesc.Quality = uMsaa4xQuality - 1;
		}
		else
		{
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
		}

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = a_hwnd;
		swapChainDesc.Windowed = true;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = 0;

		IDXGISwapChain* pSwapChain;

		IDXGIDevice* dxgiDevice = 0;
		hr = pDX11Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
		ASSERT(!FAILED(hr));

		IDXGIAdapter* dxgiAdapter = 0;
		hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);
		ASSERT(!FAILED(hr));

		IDXGIFactory* dxgiFactory = 0;
		hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);
		ASSERT(!FAILED(hr));

		hr = dxgiFactory->CreateSwapChain(pDX11Device, &swapChainDesc, &pSwapChain);
		ASSERT(!FAILED(hr));

		SAFE_RELEASE(dxgiDevice);
		SAFE_RELEASE(dxgiAdapter);
		SAFE_RELEASE(dxgiFactory);

		//todo init RHIDX11 

		return true;
	}

}