#pragma once
/********************************************************************
	created:	2018/06/20
	created:	20:6:2018   8:33
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11\sgfRHIDeviceDX11.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11
	file base:	sgfRHIDeviceDX11
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/
#include <d3d11.h>
#include <dxgi.h>
#include "../sgfRHIDevice.h"

namespace sgf
{
	class RHIDeviceDX11 : public RHIDevice
	{
		friend class RHIDevice;
	public:
		ID3D11RenderTargetView*	GetCurrentRenderTargetView() const;
		ID3D11DepthStencilView*	GetCurrentDepthStencilView() const;
	public:
		static void		SetMainWindowHandle(HWND a_hWnd);
		static void		SetMainWindowSize(int32 a_nWidth, int32 a_nHeight);
		static RHIDeviceDX11* Get();
	protected:
		virtual void _OnInit() override;
		virtual void _OnExit() override;
		virtual void _OnTick() override;
		virtual void _OnLostDevice() override;
		virtual void _OnResetDevice() override;
		virtual void _OnResize(int32 a_nWidth, int32 a_nHeight) override;

		virtual ERHIDeviceType GetType() const override;
	protected:
		RHIDeviceDX11();
		virtual ~RHIDeviceDX11();
	private:
		bool		_InitDevice();
		void		_Resize(int32 a_nWidht, int32 a_nHeight);
	private:
		ID3D11Texture2D*		m_pDepthStencilBuffer;
		ID3D11RenderTargetView* m_pRenderTargetView;
		ID3D11DepthStencilView* m_pDepthStencilView;
		D3D11_VIEWPORT			mScreenViewport;

		bool					m_bEnable4xMsaa;
		UINT					m_uMsaa4xQuality;
	private:
		static RHIDeviceDX11*	ms_pInstace;
		static HWND				ms_hWnd;
		static int32			ms_nWindowWidth;
		static int32			ms_nWindowHeight;

	};

	extern ID3D11Device*		DX11_pDevice;
	extern ID3D11DeviceContext*	DX11_PDeviceContext;
	extern IDXGISwapChain*		DX11_pSwapChain;
}