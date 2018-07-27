#include "sgfRHIPCH.h"
#include "sgfRHIVertexInputDX11.h"

namespace sgf
{
	RHIVertexInputDX11*	DX11_pVertexInput = NULL;

	typedef THashMap<RHIVertexInputDesc, RHIVertexInputDX11*> VertexInputMapDX11;
	VertexInputMapDX11 DX11_mapVertexInput;
	//-------------------------------------------------------------------------
	RHIVertexInputDX11::RHIVertexInputDX11(const RHIVertexInputDesc& a_desc)
		:RHIVertexInput( a_desc )
	{

	}

	//-------------------------------------------------------------------------
	void 
		RHIVertexInputDX11::Init()
	{

	}

	//-------------------------------------------------------------------------
	void 
		RHIVertexInputDX11::Exit()
	{
		DX11_pVertexInput = NULL;
		for (VertexInputMapDX11::iterator it = DX11_mapVertexInput.begin(); it != DX11_mapVertexInput.end(); ++it)
		{
			it->second->Release();
		}
		DX11_mapVertexInput.clear();
	}

	//-------------------------------------------------------------------------
	void 
		RHIVertexInputDX11::Tick()
	{
		DX11_pVertexInput = NULL;
	}

	//-------------------------------------------------------------------------
	RHIVertexInputRef 
		RHICreateVertexInputDX11(const RHIVertexInputDesc& a_desc)
	{
		VertexInputMapDX11::iterator it = DX11_mapVertexInput.find(a_desc);
		if (it != DX11_mapVertexInput.end())
		{
			return it->second;
		}
		else
		{
			RHIVertexInputDX11* pInput = new RHIVertexInputDX11(a_desc);
			pInput->AddRef();
			DX11_mapVertexInput.insert(a_desc, pInput);
			return pInput;
		}
	}

	//-------------------------------------------------------------------------
	void 
		RHISetVertexInputDX11(const RHIVertexInputRef& a_refInput)
	{
		DX11_pVertexInput = a_refInput.GetReference<RHIVertexInputDX11>();
	}
}