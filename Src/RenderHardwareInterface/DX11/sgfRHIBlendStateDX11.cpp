#include "sgfRHIDX11Private.h"
#include "sgfRHIBlendStateDX11.h"

namespace sgf
{
	typedef THashMap<RHIBlendStateDesc, RHIBlendStateDX11*> BlendStateMapDX11;
	RHIBlendStateDX11*	DX11_pBlendState = NULL;
	BlendStateMapDX11 DX11_mapBlendState;
	//-------------------------------------------------------------------------
	RHIBlendStateDX11::RHIBlendStateDX11(const RHIBlendStateDesc& a_sDesc)
		:m_pBlendState(NULL)
	{
		D3D11_BLEND_DESC sDescDX11;
		sDescDX11.AlphaToCoverageEnable = a_sDesc.m_nAlphaToCoverageEnable;
		sDescDX11.IndependentBlendEnable = a_sDesc.m_nIndependentBlendEnable;
		for (int32 i = 0; i < RHI_BLEND_TARGET_COUNT_MAX; ++i)
		{
			sDescDX11.RenderTarget[i].BlendEnable = a_sDesc.m_arrRenderTarget[i].m_nBlendEnable;
			sDescDX11.RenderTarget[i].SrcBlend = RHIToDX11_Blend(a_sDesc.m_arrRenderTarget[i].m_eSrcBlend);
			sDescDX11.RenderTarget[i].DestBlend = RHIToDX11_Blend(a_sDesc.m_arrRenderTarget[i].m_eDstBlend);
			sDescDX11.RenderTarget[i].BlendOp = RHIToDX11_BlendOp(a_sDesc.m_arrRenderTarget[i].m_eBlendOper);
			sDescDX11.RenderTarget[i].SrcBlendAlpha = RHIToDX11_Blend(a_sDesc.m_arrRenderTarget[i].m_eSrcAlphaBlend);
			sDescDX11.RenderTarget[i].DestBlendAlpha = RHIToDX11_Blend(a_sDesc.m_arrRenderTarget[i].m_eDstAlphaBlend);
			sDescDX11.RenderTarget[i].BlendOpAlpha = RHIToDX11_BlendOp(a_sDesc.m_arrRenderTarget[i].m_eAlphaBlendOper);
			sDescDX11.RenderTarget[i].RenderTargetWriteMask = a_sDesc.m_arrRenderTarget[i].m_nRenderTargetWriteMask;
		}
		DX11_pDevice->CreateBlendState(&sDescDX11, &m_pBlendState);
	}

	//-------------------------------------------------------------------------
	RHIBlendStateDX11::~RHIBlendStateDX11()
	{
		m_pBlendState->Release();
	}

	//-------------------------------------------------------------------------
	void 
		RHIBlendStateDX11::Setup()
	{
		float blendFactor[4] = { 0.f, 0.f, 0.f, 0.f };
		DX11_pDeviceContext->OMSetBlendState(m_pBlendState, blendFactor, 0xffffffff);
	}

	//-------------------------------------------------------------------------
	void 
		RHIBlendStateDX11::Init()
	{

	}

	//-------------------------------------------------------------------------
	void 
		RHIBlendStateDX11::Exit()
	{
		for (BlendStateMapDX11::iterator it = DX11_mapBlendState.begin(); it != DX11_mapBlendState.end(); ++it)
		{
			it->second->Release();
		}
		DX11_mapBlendState.clear();
	}

	//-------------------------------------------------------------------------
	void 
		RHIBlendStateDX11::Tick()
	{

	}

	//-------------------------------------------------------------------------
	RHIBlendStateRef
		RHICreateBlendStateDX11(const RHIBlendStateDesc& a_sDesc)
	{
		BlendStateMapDX11::iterator it = DX11_mapBlendState.find(a_sDesc);
		if (it != DX11_mapBlendState.end())
		{
			return it->second;
		}
		else
		{
			RHIBlendStateDX11* pBlend = new RHIBlendStateDX11(a_sDesc);
			pBlend->AddRef();
			DX11_mapBlendState.insert(a_sDesc, pBlend);
			return pBlend;
		}
	}

	//-------------------------------------------------------------------------
	RHIBlendStateRef
		RHIGetBlendStateDX11()
	{
		return DX11_pBlendState;
	}

	//-------------------------------------------------------------------------
	void 
		RHISetBlendStateDX11(const RHIBlendStateRef& a_refBlend)
	{
		if (a_refBlend != DX11_pBlendState)
		{
			DX11_pBlendState = a_refBlend.GetReference<RHIBlendStateDX11>();
			DX11_pBlendState->Setup();
		}
	}
}