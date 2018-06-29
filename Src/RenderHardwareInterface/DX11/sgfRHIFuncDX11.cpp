#include"sgfRHIPCH.h"
#include"sgfRHIDX11Private.h"
#include"sgfRHIFuncDX11.h"

namespace sgf
{
	void InitializeRHIFunc()
	{
		RHISetViewport = RHISetViewportDX11;
		RHIClear = RHIClearDX11;

		RHICreateVertexInput = RHICreateVertexInputDX11;
		RHISetVertexInput = RHISetVertexInputDX11;
	}

	//-------------------------------------------------------------------------
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

	//-------------------------------------------------------------------------
	void 
		RHIClearDX11(bool a_bCleanColor, const ColorByte4& a_col, bool a_bCleanDepth, float a_fDepth, bool a_bCleanStencil, uint32 a_uStencil)
	{
		if (a_bCleanColor)
		{
			Color col(a_col);
			RHIDeviceDX11::Get()->GetDeviceContext()->ClearRenderTargetView(RHIDeviceDX11::Get()->GetCurrentRenderTargetView(), col.f);
		}
		if (a_bCleanDepth || a_bCleanStencil)
		{
			UINT uFlag = ( a_bCleanDepth ? D3D11_CLEAR_DEPTH : 0 )|( a_bCleanStencil ? D3D11_CLEAR_STENCIL : 0 );
			RHIDeviceDX11::Get()->GetDeviceContext()->ClearDepthStencilView(RHIDeviceDX11::Get()->GetCurrentDepthStencilView(), uFlag, a_fDepth, a_uStencil);
		}
		//todo
		RHIDeviceDX11::Get()->GetSwapChain()->Present(0, 0);
	}

}