#include "sgfRHIPCH.h"
#include "sgfRHIDX11Private.h"
#include "sgfRHIEffectDX11.h"
#include "sgfVertexShaderDX11.h"
#include "sgfPixelShaderDX11.h"

namespace sgf
{ 
	typedef THashMap<String, RHIEffectDX11*> EffectMapDX11;
	EffectMapDX11 DX11_mapEffect;
	RHIEffectDX11* DX11_pEffect = NULL;
	//-------------------------------------------------------------------------
	RHIEffectDX11::RHIEffectDX11(const String& a_szVS, const String& a_szPS, const TArray<RHIEffect::Macro>& a_arrMacro)
	{
		_Initialize(a_szVS, a_szPS, a_arrMacro);
	}

	//-------------------------------------------------------------------------
	RHIEffectDX11::~RHIEffectDX11()
	{

	}

	//-------------------------------------------------------------------------
	void 
		RHIEffectDX11::Setup(const RHIShaderConstantsRef& a_refCons, const RHIShaderTexturesRef& a_refTexs)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	//-------------------------------------------------------------------------
	RHIShaderConstantsRef 
		RHIEffectDX11::CreateShaderConstants()
	{
		throw std::exception("The method or operation is not implemented.");
	}

	//-------------------------------------------------------------------------
	RHIShaderTexturesRef 
		RHIEffectDX11::CreateShaderTextures()
	{
		throw std::exception("The method or operation is not implemented.");
	}

	//-------------------------------------------------------------------------
	void 
		RHIEffectDX11::Init()
	{

	}

	//-------------------------------------------------------------------------
	void 
		RHIEffectDX11::Tick()
	{

	}

	//-------------------------------------------------------------------------
	void 
		RHIEffectDX11::Exit()
	{
		for (EffectMapDX11::iterator it = DX11_mapEffect.begin(); it != DX11_mapEffect.end(); ++it)
		{
			it->second->Release();
		}
		DX11_mapEffect.clear();
		VertexShaderDX11::Exit();
		PixelShaderDX11::Exit();
	}

	//-------------------------------------------------------------------------
	void 
		RHIEffectDX11::_Initialize(const String& a_szVS, const String& a_szPS, const TArray<RHIEffect::Macro>& a_arrMacro)
	{
		m_refVertexShader = CreateVertexShaderDX11(a_szVS, a_arrMacro);
		m_refPixelShader = CreatePixelShaderDX11(a_szPS, a_arrMacro);
	}

	//-------------------------------------------------------------------------
	String 
		_UniqueEffectName(const String& a_szVS, const String& a_szPS, const TArray<RHIEffect::Macro>& a_arrMacro)
	{
		String szUniqueName = a_szVS + a_szPS;
		for (int32 i = 0; i < a_arrMacro.size(); ++i)
		{
			szUniqueName.append(a_arrMacro[i].a_szKey);
			szUniqueName.append(a_arrMacro[i].a_szValue);
		}
		return szUniqueName;
	}
	//-------------------------------------------------------------------------
	RHIEffectRef
		RHICreateEffectDX11(const String& a_szVS, const String& a_szPS, const TArray<RHIEffect::Macro>& a_arrMacro)
	{
		String szUniqueName = _UniqueEffectName(a_szVS, a_szPS, a_arrMacro);
		EffectMapDX11::iterator it = DX11_mapEffect.find(szUniqueName);
		if (it != DX11_mapEffect.end())
		{
			return it->second;
		}
		else
		{
			RHIEffectDX11* pEffect = new RHIEffectDX11(a_szVS, a_szPS, a_arrMacro);
			pEffect->AddRef();
			DX11_mapEffect.insert(szUniqueName, pEffect);
			return pEffect;
		}
	}
}
