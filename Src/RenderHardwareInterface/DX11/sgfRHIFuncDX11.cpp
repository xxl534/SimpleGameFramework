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

		RHICreateVertexBuffer = RHICreateVertexBufferDX11;
		RHISetVertexBuffer = RHISetVertexBufferDX11;
		RHILockVertexBuffer = RHILockVertexBufferDX11;
		RHIUnlockVertexBuffer = RHIUnlockVertexBufferDX11;

		RHICreateIndexBuffer = RHICreateIndexBufferDX11;
		RHISetIndexBuffer = RHISetIndexBufferDX11;
		RHILockIndexBuffer = RHILockIndexBufferDX11;
		RHIUnlockIndexBuffer = RHIUnlockIndexBufferDX11;

		RHICreateTextureFromFile = RHICreateTextureFromFileDX11;
	
		RHICreateRasterizerState = RHICreateRasterizerStateDX11;
		RHIGetRasterizerState = RHIGetRasterizerStateDX11;
		RHISetRasterizerState = RHISetRasterizerStateDX11;

		RHICreateBlendState = RHICreateBlendStateDX11;

		RHICreateDepthStencilState = RHICreateDepthStencilStateDX11;

		RHICreateShader = RHICreateShaderDX11;
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
		DX11_pDeviceContext->RSSetViewports(1, &dxViewport);
	}

	//-------------------------------------------------------------------------
	void 
		RHIClearDX11(bool a_bCleanColor, const ColorByte4& a_col, bool a_bCleanDepth, float a_fDepth, bool a_bCleanStencil, uint32 a_uStencil)
	{
		if (a_bCleanColor)
		{
			Color col(a_col);
			DX11_pDeviceContext->ClearRenderTargetView(RHIDeviceDX11::Get()->GetCurrentRenderTargetView(), col.f);
		}
		if (a_bCleanDepth || a_bCleanStencil)
		{
			UINT uFlag = ( a_bCleanDepth ? D3D11_CLEAR_DEPTH : 0 )|( a_bCleanStencil ? D3D11_CLEAR_STENCIL : 0 );
			DX11_pDeviceContext->ClearDepthStencilView(RHIDeviceDX11::Get()->GetCurrentDepthStencilView(), uFlag, a_fDepth, a_uStencil);
		}
		//todo
		DX11_pSwapChain->Present(0, 0);
	}

}