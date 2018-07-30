#include "sgfRHIPCH.h"
#include "sgfRHIDX11Private.h"
#include "sgfRHIDepthStencilStateDX11.h"

namespace sgf
{
	typedef THashMap<RHIDepthStencilStateDesc, RHIDepthStencilStateDX11*> DepthStencilStateMapDX11;
	RHIDepthStencilStateDX11*	DX11_pDepthStencilState = NULL;
	DepthStencilStateMapDX11	DX11_mapDepthStencilState;
	//-------------------------------------------------------------------------
	RHIDepthStencilStateRef
		RHICreateDepthStencilStateDX11(const RHIDepthStencilStateDesc& a_sDesc)
	{
		DepthStencilStateMapDX11::iterator it = DX11_mapDepthStencilState.find(a_sDesc);
		if (it != DX11_mapDepthStencilState.end())
		{
			return it->second;
		}
		else
		{
			RHIDepthStencilStateDX11* pState = new RHIDepthStencilStateDX11(a_sDesc);
			pState->AddRef();
			DX11_mapDepthStencilState.insert(a_sDesc, pState);
			return pState;
		}
	}

	//-------------------------------------------------------------------------
	RHIDepthStencilStateRef
		RHIGetDepthStencilStateDX11()
	{
		return DX11_pDepthStencilState;
	}

	//-------------------------------------------------------------------------
	void
		RHISetDepthStencilStateDX11(const RHIDepthStencilStateRef& a_refState)
	{
		if (a_refState != DX11_pDepthStencilState)
		{
			DX11_pDepthStencilState = a_refState.GetReference<RHIDepthStencilStateDX11>();
			DX11_pDepthStencilState->Setup();
		}
	}

	//-------------------------------------------------------------------------
	RHIDepthStencilStateDX11::RHIDepthStencilStateDX11(const RHIDepthStencilStateDesc& a_sDesc)
		:m_pState(NULL)
	{
		m_sDesc = a_sDesc;
		D3D11_DEPTH_STENCIL_DESC sDescDx;
		sDescDx.DepthEnable = m_sDesc.m_nDepthEnable;
		sDescDx.DepthWriteMask = (D3D11_DEPTH_WRITE_MASK)m_sDesc.m_nDepthWriteMask;
		sDescDx.DepthFunc = RHIToDX11_ComparisonFunc(m_sDesc.m_eDepthFunc);
		sDescDx.StencilEnable = a_sDesc.m_nStencilEnable;
		sDescDx.StencilReadMask = a_sDesc.m_nStencilReadMask;
		sDescDx.StencilWriteMask = a_sDesc.m_nStencilWriteMask;

		sDescDx.FrontFace.StencilFailOp = RHIToDX11_StencilOp(m_sDesc.m_sFrontFaceFuncDesc.m_eStendcilFailOper);
		sDescDx.FrontFace.StencilDepthFailOp = RHIToDX11_StencilOp(m_sDesc.m_sFrontFaceFuncDesc.m_eStendcilDepthFailOper);
		sDescDx.FrontFace.StencilPassOp = RHIToDX11_StencilOp(m_sDesc.m_sFrontFaceFuncDesc.m_eStendcilPassOper);
		sDescDx.FrontFace.StencilFunc = RHIToDX11_ComparisonFunc(m_sDesc.m_sFrontFaceFuncDesc.m_eStencilFunc);

		sDescDx.BackFace.StencilFailOp = RHIToDX11_StencilOp(m_sDesc.m_sBackFaceFuncDesc.m_eStendcilFailOper);
		sDescDx.BackFace.StencilDepthFailOp = RHIToDX11_StencilOp(m_sDesc.m_sBackFaceFuncDesc.m_eStendcilDepthFailOper);
		sDescDx.BackFace.StencilPassOp = RHIToDX11_StencilOp(m_sDesc.m_sBackFaceFuncDesc.m_eStendcilPassOper);
		sDescDx.BackFace.StencilFunc = RHIToDX11_ComparisonFunc(m_sDesc.m_sBackFaceFuncDesc.m_eStencilFunc);

		HR(DX11_pDevice->CreateDepthStencilState(&sDescDx, &m_pState));
	}

	//-------------------------------------------------------------------------
	RHIDepthStencilStateDX11::~RHIDepthStencilStateDX11()
	{
		SAFE_RELEASE(m_pState);
	}

	//-------------------------------------------------------------------------
	void 
		RHIDepthStencilStateDX11::Setup()
	{
		DX11_pDeviceContext->OMSetDepthStencilState(m_pState, 0);
	}

	//-------------------------------------------------------------------------
	void 
		RHIDepthStencilStateDX11::Init()
	{

	}

	//-------------------------------------------------------------------------
	void 
		RHIDepthStencilStateDX11::Exit()
	{
		for (DepthStencilStateMapDX11::iterator it = DX11_mapDepthStencilState.begin(); it != DX11_mapDepthStencilState.end(); ++it)
		{
			it->second->Release();
		}
		DX11_mapDepthStencilState.clear();
	}

	//-------------------------------------------------------------------------
	void 
		RHIDepthStencilStateDX11::Tick()
	{

	}

}