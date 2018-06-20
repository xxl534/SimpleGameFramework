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
	public:
		static void		SetMainWindowHandle(HWND a_hWnd);
		static void		SetMainWindowSize(int32 a_nWidth, int32 a_nHeight);
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
		ID3D11Device*			m_pDevice;
		ID3D11DeviceContext*	m_pDeviceContext;
		IDXGISwapChain*			m_pSwapChain;
	private:
		static HWND				ms_hWnd;
		static int32			ms_nWindowWidth;
		static int32			ms_nWindowHeight;

	};
}