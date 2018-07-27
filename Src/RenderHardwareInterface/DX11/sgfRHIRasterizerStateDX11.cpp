#include "sgfRHIDX11Private.h"
#include "sgfRHIRasterizerStateDX11.h"

namespace sgf
{
	typedef THashMap<RHIRasterizerStateDesc, RHIRasterizerStateDX11*>	RasterizerStateMapDX11;
	RasterizerStateMapDX11 DX11_mapRasterizerState;
	RHIRasterizerStateDX11* DX11_pRasterizerState = NULL;
	//-------------------------------------------------------------------------
	RHIRasterizerStateDX11::RHIRasterizerStateDX11(const RHIRasterizerStateDesc& a_sDesc)
		:m_pDX11State(NULL)
	{
		m_sDesc = a_sDesc;

		D3D11_RASTERIZER_DESC sDescDX11;
		sDescDX11.FillMode = RHIToDX11_FillMode(a_sDesc.m_eFillMode);
		sDescDX11.CullMode = RHIToDX11_CullMode(a_sDesc.m_eCullMode);
		sDescDX11.FrontCounterClockwise = m_sDesc.m_nFrontCounterClockwise;
		sDescDX11.DepthBias = m_sDesc.m_nDepthBias;
		sDescDX11.DepthBiasClamp = m_sDesc.m_fDepthBiasClamp;
		sDescDX11.SlopeScaledDepthBias = m_sDesc.m_fSlopeScaleDepthBias;
		sDescDX11.DepthClipEnable = m_sDesc.m_nDepthClipEnable;
		sDescDX11.ScissorEnable = m_sDesc.m_nScissorEnable;
		sDescDX11.MultisampleEnable = m_sDesc.m_nMultisampleEnable;
		sDescDX11.AntialiasedLineEnable = m_sDesc.m_nAntialiasedLineEnable;

		DX11_pDevice->CreateRasterizerState(&sDescDX11, &m_pDX11State);
	}

	//-------------------------------------------------------------------------
	RHIRasterizerStateDX11::~RHIRasterizerStateDX11()
	{
		SAFE_RELEASE(m_pDX11State);
	}

	//-------------------------------------------------------------------------
	void 
		RHIRasterizerStateDX11::Setup()
	{
		DX11_pDeviceContext->RSSetState(m_pDX11State);
	}

	//-------------------------------------------------------------------------
	void 
		RHIRasterizerStateDX11::Init()
	{

	}

	//-------------------------------------------------------------------------
	void 
		RHIRasterizerStateDX11::Exit()
	{
		for (RasterizerStateMapDX11::iterator it = DX11_mapRasterizerState.begin(); it != DX11_mapRasterizerState.end(); ++it)
		{
			it->second->Release();
		}
		DX11_mapRasterizerState.clear();
		DX11_pRasterizerState = NULL;
	}

	//-------------------------------------------------------------------------
	void 
		RHIRasterizerStateDX11::Tick()
	{
		
	}

	//-------------------------------------------------------------------------
	RHIRasterizerStateRef
		RHICreateRasterizerStateDX11(const RHIRasterizerStateDesc& a_sDesc)
	{
		RasterizerStateMapDX11::iterator it = DX11_mapRasterizerState.find(a_sDesc);
		if (it != DX11_mapRasterizerState.end())
		{
			return it->second;
		}
		else
		{
			RHIRasterizerStateDX11* pState = new RHIRasterizerStateDX11(a_sDesc);
			pState->AddRef();
			DX11_mapRasterizerState.insert(a_sDesc, pState);
			return pState;
		}
	}

	//-------------------------------------------------------------------------
	RHIRasterizerStateRef
		RHIGetRasterizerStateDX11()
	{
		return DX11_pRasterizerState;
	}

	//-------------------------------------------------------------------------
	void 
		RHISetRasterizerStateDX11(const RHIRasterizerStateRef& a_refState)
	{
		if (a_refState != DX11_pRasterizerState)
		{
			DX11_pRasterizerState = a_refState.GetReference<RHIRasterizerStateDX11>();
			DX11_pRasterizerState->Setup();
		}
	}
}
