#include"sgfRHIPCH.h"
#include"sgfRHIFuncDX11.h"
#include "sgfRHIDX11Private.h"

namespace sgf
{
	void InitializeRHIFunc()
	{

	}

	void 
		RHISetViewportDX11(const RHIViewportDesc& a_desc)
	{
		D3D11_VIEWPORT dxViewport;
		dxViewport.Width = a_desc.m_nWidth;
		dxViewport.Height = a_desc.m_nHeight;
		dxViewport.TopLeftX = a_desc.m_nX;
		dxViewport.TopLeftY = a_desc.m_nY;
		dxViewport.MinDepth = a_desc.m_fMinDepth;
		dxViewport.MaxDepth = a_desc.m_fMaxDepth;
		RHIDeviceDX11::Get()->GetDeviceContext()->RSSetViewports(1, &dxViewport);
	}

}