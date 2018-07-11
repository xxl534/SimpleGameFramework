#include "sgfRHIPCH.h"
#include "sgfRHIDX11Private.h"
#include "sgfRHIDeviceDX11.h"
#include "sgfRHIVertexInputDX11.h"


namespace sgf
{
	ID3D11Device*			DX11_pDevice = NULL;
	ID3D11DeviceContext*	DX11_pDeviceContext = NULL;
	IDXGISwapChain*			DX11_pSwapChain = NULL;
	static const String		s_szDeviceName = "DX11";
	//-------------------------------------------------------------------------
	RHIDeviceDX11* RHIDeviceDX11::ms_pInstace = NULL;
	HWND RHIDeviceDX11::ms_hWnd = 0;
	int32 RHIDeviceDX11::ms_nWindowWidth = 0;
	int32 RHIDeviceDX11::ms_nWindowHeight = 0;
	
	//-------------------------------------------------------------------------
	RHIDeviceDX11::RHIDeviceDX11()
		:m_pDepthStencilBuffer(NULL)
		,m_pRenderTargetView(NULL)
		,m_pDepthStencilView(NULL)
		,m_bEnable4xMsaa( true )
		,m_uMsaa4xQuality(0)
	{
		ASSERT(ms_pInstace == NULL);
		ms_pInstace = this;
	}

	RHIDeviceDX11::~RHIDeviceDX11()
	{
		ms_pInstace = NULL;
	}

	//-------------------------------------------------------------------------
	const String& 
		RHIDeviceDX11::GetName() const
	{
		return s_szDeviceName;
	}

	//-------------------------------------------------------------------------
	ID3D11RenderTargetView* 
		RHIDeviceDX11::GetCurrentRenderTargetView() const
	{
		return m_pRenderTargetView;
	}

	//-------------------------------------------------------------------------
	ID3D11DepthStencilView* 
		RHIDeviceDX11::GetCurrentDepthStencilView() const
	{
		return m_pDepthStencilView;
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
	RHIDeviceDX11* 
		RHIDeviceDX11::Get()
	{
		return ms_pInstace;
	}

	//-------------------------------------------------------------------------
	void 
		RHIDeviceDX11::_OnInit()
	{
		bool bInit = _InitDevice();
		ASSERT(bInit == true);

		InitializeRHIFunc();

		RHIVertexInputDX11::Init();
		//todo implement
	}

	//-------------------------------------------------------------------------
	void 
		RHIDeviceDX11::_OnExit()
	{
		RHIVertexInputDX11::Exit();
		//todo implement
	}

	//-------------------------------------------------------------------------
	void 
		RHIDeviceDX11::_OnTick()
	{
		RHIVertexInputDX11::Tick();
		//todo implement
	}

	//-------------------------------------------------------------------------
	void 
		RHIDeviceDX11::_OnLostDevice()
	{
		HardwareResource::LostDevice();
		//todo implement
	}

	//-------------------------------------------------------------------------
	void 
		RHIDeviceDX11::_OnResetDevice()
	{
		HardwareResource::ResetDevice();
		//todo implement
	}

	//-------------------------------------------------------------------------
	void 
		RHIDeviceDX11::_OnResize(int32 a_nWidth, int32 a_nHeight)
	{
		_Resize(a_nWidth, a_nHeight);
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
			&DX11_pDevice,
			&featureLevel,
			&DX11_pDeviceContext
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

		
		hr = DX11_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_uMsaa4xQuality);
		if (FAILED(hr))
		{
			MessageBox(0, "D3D11 check device MSAA level failed!", 0, 0);
			return false;
		}
		ASSERT(m_uMsaa4xQuality > 0);

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		swapChainDesc.BufferDesc.Width = ms_nWindowWidth;
		swapChainDesc.BufferDesc.Height = ms_nWindowHeight;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		if (m_bEnable4xMsaa)
		{
			swapChainDesc.SampleDesc.Count = 4;
			swapChainDesc.SampleDesc.Quality = m_uMsaa4xQuality - 1;
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
		hr = DX11_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
		ASSERT(!FAILED(hr));

		IDXGIAdapter* dxgiAdapter = 0;
		hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);
		ASSERT(!FAILED(hr));

		IDXGIFactory* dxgiFactory = 0;
		hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);
		ASSERT(!FAILED(hr));

		hr = dxgiFactory->CreateSwapChain(DX11_pDevice, &swapChainDesc, &DX11_pSwapChain);
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
		ASSERT(DX11_pDevice != NULL);
		ASSERT(DX11_pDeviceContext != NULL);
		ASSERT(DX11_pSwapChain != NULL);

		// Release the old views, as they hold references to the buffers we
		// will be destroying.  Also release the old depth/stencil buffer.

		SAFE_RELEASE(m_pDepthStencilBuffer);
		SAFE_RELEASE(m_pRenderTargetView);
		SAFE_RELEASE(m_pDepthStencilView);

		// Resize the swap chain and recreate the render target view.
		HRESULT hr = DX11_pSwapChain->ResizeBuffers(1, a_nWidht, a_nHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
		ASSERT(!FAILED(hr));
		ID3D11Texture2D* pBackBuffer;
		hr = DX11_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
		ASSERT(!FAILED(hr));
		hr = DX11_pDevice->CreateRenderTargetView(pBackBuffer, 0, &m_pRenderTargetView);
		SAFE_RELEASE(pBackBuffer);

		// Create the depth/stencil buffer and view.
		D3D11_TEXTURE2D_DESC depthStencilDesc;

		depthStencilDesc.Width		= a_nWidht;
		depthStencilDesc.Height		= a_nHeight;
		depthStencilDesc.MipLevels	= 1;
		depthStencilDesc.ArraySize	= 1;
		depthStencilDesc.Format		= DXGI_FORMAT_D24_UNORM_S8_UINT;
		if( m_bEnable4xMsaa )
		{
			depthStencilDesc.SampleDesc.Count = 4;
			depthStencilDesc.SampleDesc.Quality = m_uMsaa4xQuality - 1;
		}
		else
		{
			depthStencilDesc.SampleDesc.Count = 1;
			depthStencilDesc.SampleDesc.Quality = 0;
		}
		depthStencilDesc.Usage		= D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags	= D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags	= 0;

		hr = DX11_pDevice->CreateTexture2D(&depthStencilDesc, 0, &m_pDepthStencilBuffer);
		ASSERT(!FAILED(hr));
		hr = DX11_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, 0, &m_pDepthStencilView);

		// Bind the render target view and depth/stencil view to the pipeline.
		DX11_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

		// todo Set the viewport transform.
	}

}


