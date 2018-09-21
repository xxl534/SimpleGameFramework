#include "sgfRHIPCH.h"
#include "sgfRHIDX11Private.h"
#include "sgfPixelShaderDX11.h"

namespace sgf
{
	typedef THashMap<String, PixelShaderDX11*> PixelShaderMapDX11;
	PixelShaderMapDX11 DX11_mapPixelShader;

	//----------------------------------------
	PixelShaderDX11::PixelShaderDX11(const String& a_szFile, const TArray<RHIEffect::Macro>& a_arrMacro)
		:m_pShader(NULL)
	{
		_Initialize(a_szFile, a_arrMacro);
	}

	//----------------------------------------
	PixelShaderDX11::~PixelShaderDX11()
	{
		SAFE_RELEASE(m_pShader);
	}

	//----------------------------------------
	void 
		PixelShaderDX11::Setup(const RHIShaderConstantsRef& a_refCons, const RHIShaderTexturesRef& a_refTexs)
	{

	}

	//----------------------------------------
	void 
		PixelShaderDX11::Exit()
	{
		for (PixelShaderMapDX11::iterator it = DX11_mapPixelShader.begin(); it != DX11_mapPixelShader.end(); ++it)
		{
			it->second->Release();
		}
		DX11_mapPixelShader.clear();
	}

	//----------------------------------------
	void 
		PixelShaderDX11::_Initialize(const String& a_szFile, const TArray<RHIEffect::Macro>& a_arrMacro)
	{
		TArray<D3D_SHADER_MACRO, false, false> arrDxMacro = _ToDx11Marco(a_arrMacro);
		ID3D10Blob* sCompiledShader = NULL;
		ID3D10Blob* sCompilationMsgs = NULL;
		HRESULT hr = D3DCompileFromFile(StringHelper::Utf8ToUtf16(a_szFile).c_str(), arrDxMacro.begin(), NULL, "main", "ps_5_0", D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, NULL, &sCompiledShader, &sCompilationMsgs);
		if (sCompilationMsgs != NULL)
		{
			MessageBox(0, (char*)sCompilationMsgs->GetBufferPointer(), 0, 0);
			SAFE_RELEASE(sCompilationMsgs);
		}
		HR(hr);
		HR(DX11_pDevice->CreatePixelShader(sCompiledShader->GetBufferPointer(), sCompiledShader->GetBufferSize(), NULL, &m_pShader));
		ID3D11ShaderReflection* pReflect;
		HR(D3DReflect(sCompiledShader->GetBufferPointer(), sCompiledShader->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pReflect));
		SAFE_RELEASE(sCompiledShader);

		_InitAttribute(pReflect);
		_InitUniform(pReflect);
	}

	//----------------------------------------
	ShaderDx11Ref 
		CreatePixelShaderDX11(const String & a_szPS, const TArray<RHIEffect::Macro>& a_arrMacro)
	{
		String szUniqueName = ShaderDX11::GetUniqueName(a_szPS, a_arrMacro);
		PixelShaderMapDX11::iterator it = DX11_mapPixelShader.find(szUniqueName);
		if (it != DX11_mapPixelShader.end())
		{
			return it->second;
		}
		else
		{
			PixelShaderDX11* pShader = new PixelShaderDX11(a_szPS, a_arrMacro);
			pShader->AddRef();
			DX11_mapPixelShader.insert(szUniqueName, pShader);
			return pShader;
		}
	}

}