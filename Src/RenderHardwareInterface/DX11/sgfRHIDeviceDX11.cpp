#include "sgfRHIPCH.h"
#include "sgfRHIDeviceDX11.h"

namespace sgf
{
	HWND RHIDeviceDX11::ms_hWnd = 0;
	int32 RHIDeviceDX11::ms_nWindowWidth = 0;
	int32 RHIDeviceDX11::ms_nWindowHeight = 0;

	//-------------------------------------------------------------------------
	RHIDeviceDX11::RHIDeviceDX11()
		:m_pDevice(NULL)
		,m_pDeviceContext(NULL)
		,m_pSwapChain(NULL)
	{
	}

	RHIDeviceDX11::~RHIDeviceDX11()
	{
	}

	//-------------------------------------------------------------------------
	void 
		RHIDeviceDX11::SetMainWindowHandle(HWND a_hWnd)
	{
		ms_hWnd = a_hWnd;
	}

	//-------------------------------------------------------------------------
	void 
		RHIDeviceDX11::SetMainWindowSize(int32 a_nWidth, int32 a_nHeight)
	{
		ms_nWindowWidth = a_nWidth;
		ms_nWindowHeight = a_nHeight;
	}

	//-------------------------------------------------------------------------
	void 
		RHIDeviceDX11::_OnInit()
	{
		bool bInit = _InitDevice();
		ASSERT(bInit == true);
		throw std::exception("The method or operation is not implemented.");
	}

	//-------------------------------------------------------------------------
	void 
		RHIDeviceDX11::_OnExit()
	{
		throw std::exception("The method or operation is not implemented.");
	}

	//-------------------------------------------------------------------------
	void 
		RHIDeviceDX11::_OnTick()
	{
		throw std::exception("The method or operation is not implemented.");
	}

	//-------------------------------------------------------------------------
	void 
		RHIDeviceDX11::_OnLostDevice()
	{
		throw std::exception("The method or operation is not implemented.");
	}

	//-------------------------------------------------------------------------
	void 
		RHIDeviceDX11::_OnResetDevice()
	{
		throw std::exception("The method or operation is not implemented.");
	}

	//-------------------------------------------------------------------------
	void 
		RHIDeviceDX11::_OnResize(int32 a_nWidth, int32 a_nHeight)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	//-------------------------------------------------------------------------
	ERHIDeviceType 
		RHIDeviceDX11::GetType() const
	{
		return ERHIDeviceType_DX11;
	}

	//-------------------------------------------------------------------------
	bool 
		RHIDeviceDX11::_InitDevice()
	{
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
			&m_pDevice,
			&featureLevel,
			&m_pDeviceContext
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
		hr = m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &uMsaa4xQuality);
		if (FAILED(hr))
		{
			MessageBox(0, "D3D11 check device MSAA level failed!", 0, 0);
			return false;
		}
		ASSERT(uMsaa4xQuality > 0);

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		swapChainDesc.BufferDesc.Width = ms_nWindowWidth;
		swapChainDesc.BufferDesc.Height = ms_nWindowHeight;
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
		swapChainDesc.OutputWindow = ms_hWnd;
		swapChainDesc.Windowed = true;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = 0;

		IDXGIDevice* dxgiDevice = 0;
		hr = m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
		ASSERT(!FAILED(hr));

		IDXGIAdapter* dxgiAdapter = 0;
		hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);
		ASSERT(!FAILED(hr));

		IDXGIFactory* dxgiFactory = 0;
		hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);
		ASSERT(!FAILED(hr));

		hr = dxgiFactory->CreateSwapChain(m_pDevice, &swapChainDesc, &m_pSwapChain);
		ASSERT(!FAILED(hr));

		SAFE_RELEASE(dxgiDevice);
		SAFE_RELEASE(dxgiAdapter);
		SAFE_RELEASE(dxgiFactory);

		_Resize(ms_nWindowWidth, ms_nWindowHeight);
		return true;
	}

	//-------------------------------------------------------------------------
	void 
		RHIDeviceDX11::_Resize(int32 a_nWidht, int32 a_nHeight)
	{
		ASSERT(m_pDevice != NULL);
		ASSERT(m_pDeviceContext != NULL);
		ASSERT(m_pSwapChain != NULL);


	}

	

}


