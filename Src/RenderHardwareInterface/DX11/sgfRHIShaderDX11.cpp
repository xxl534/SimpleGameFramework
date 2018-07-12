#include "sgfRHIDX11Private.h"
#include "sgfRHIShaderDX11.h"

namespace sgf
{ 
	typedef THashMap<String, RHIShaderDX11*> ShaderMapDX11;
	ShaderMapDX11 DX11_mapShader;
	RHIShaderDX11* DX11_pShader = NULL;
	//-------------------------------------------------------------------------
	RHIShaderDX11::RHIShaderDX11(const String& a_szVS, const String& a_szPS, const TArray<RHIShader::Macro>& a_arrMacro)
	{
		_Initialize(a_szVS, a_szPS, a_arrMacro);
	}

	//-------------------------------------------------------------------------
	RHIShaderDX11::~RHIShaderDX11()
	{

	}

	//-------------------------------------------------------------------------
	void 
		RHIShaderDX11::Setup(const RHIShaderConstantsRef& a_refCons, const RHIShaderTexturesRef& a_refTexs)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	//-------------------------------------------------------------------------
	RHIShaderConstantsRef 
		RHIShaderDX11::CreateShaderConstants()
	{
		throw std::exception("The method or operation is not implemented.");
	}

	//-------------------------------------------------------------------------
	RHIShaderTexturesRef 
		RHIShaderDX11::CreateShaderTextures()
	{
		throw std::exception("The method or operation is not implemented.");
	}
	
	//-------------------------------------------------------------------------
	void 
		RHIShaderDX11::OnLostDevice()
	{
		
	}

	//-------------------------------------------------------------------------
	void 
		RHIShaderDX11::OnResetDevice()
	{
		
	}

	//-------------------------------------------------------------------------
	void RHIShaderDX11::_Initialize(const String& a_szVS, const String& a_szPS, const TArray<RHIShader::Macro>& a_arrMacro)
	{
		
	}

	//-------------------------------------------------------------------------
	String 
		_UniqueShaderName(const String& a_szVS, const String& a_szPS, const TArray<RHIShader::Macro>& a_arrMacro)
	{
		String szUniqueName = a_szVS + a_szPS;
		for (int32 i = 0; i > a_arrMacro.size(); ++i)
		{
			szUniqueName.append(a_arrMacro[i].a_szKey);
			szUniqueName.append(a_arrMacro[i].a_szValue);
		}
		return szUniqueName;
	}
	//-------------------------------------------------------------------------
	RHIShaderRef
		RHICreateShaderDX11(const String& a_szVS, const String& a_szPS, const TArray<RHIShader::Macro>& a_arrMacro)
	{
		String szUniqueName = _UniqueShaderName(a_szVS, a_szPS, a_arrMacro);
		ShaderMapDX11::iterator it = DX11_mapShader.find(szUniqueName);
		if (it != DX11_mapShader.end())
		{
			return it->second;
		}
		else
		{
			RHIShaderDX11* pShader = new RHIShaderDX11(a_szVS, a_szPS, a_arrMacro);
			pShader->AddRef();
			DX11_mapShader.insert(szUniqueName, pShader);
			return pShader;
		}
	}
}
