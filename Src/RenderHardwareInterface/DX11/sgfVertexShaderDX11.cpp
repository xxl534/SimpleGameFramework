#include "sgfRHIPCH.h"
#include "sgfRHIDX11Private.h"
#include "sgfVertexShaderDX11.h"

namespace sgf
{
	typedef THashMap<String, VertexShaderDX11*> VertexShaderMapDX11;
	VertexShaderMapDX11 DX11_mapVertexShader;

	//----------------------------------------
	VertexShaderDX11::VertexShaderDX11(const String& a_szVS, const TArray<RHIEffect::Macro>& a_arrMacro)
		:m_pShader(NULL)
	{
		_Initialize(a_szVS, a_arrMacro);
	}

	//----------------------------------------
	VertexShaderDX11::~VertexShaderDX11()
	{
		SAFE_RELEASE(m_pShader);
	}

	//----------------------------------------
	void 
		VertexShaderDX11::Setup(const RHIShaderConstantsRef& a_refCons, const RHIShaderTexturesRef& a_refTexs)
	{

	}

	//----------------------------------------
	void 
		VertexShaderDX11::Exit()
	{
		for (VertexShaderMapDX11::iterator it = DX11_mapVertexShader.begin(); it != DX11_mapVertexShader.end(); ++it)
		{
			it->second->Release();
		}
		DX11_mapVertexShader.clear();
	}

	//----------------------------------------
	void 
		VertexShaderDX11::_Initialize(const String & a_szFile, const TArray<RHIEffect::Macro>& a_arrMacro)
	{
		TArray<D3D_SHADER_MACRO, false, false> arrDxMacro = _ToDx11Marco(a_arrMacro);
		ID3D10Blob* sCompiledShader = NULL;
		ID3D10Blob* sCompilationMsgs = NULL;
		HRESULT hr = D3DCompileFromFile(StringHelper::Utf8ToUtf16(a_szFile).c_str(), arrDxMacro.begin(), NULL, "main", "vs_5_0", D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, NULL, &sCompiledShader, &sCompilationMsgs);
		if (sCompilationMsgs != NULL)
		{
			MessageBox(0, (char*)sCompilationMsgs->GetBufferPointer(), 0, 0);
			SAFE_RELEASE(sCompilationMsgs);
		}
		HR(hr);
		HR(DX11_pDevice->CreateVertexShader(sCompiledShader->GetBufferPointer(), sCompiledShader->GetBufferSize(), NULL, &m_pShader));
		ID3D11ShaderReflection* pReflect;
		HR(D3DReflect(sCompiledShader->GetBufferPointer(), sCompiledShader->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pReflect));
		SAFE_RELEASE(sCompiledShader);

		_InitAttribute(pReflect);
		_InitUniform(pReflect);
	}

	//----------------------------------------
	ShaderDx11Ref 
		CreateVertexShaderDX11(const String & a_szVS, const TArray<RHIEffect::Macro>& a_arrMacro)
	{
		String szUniqueName = ShaderDX11::GetUniqueName(a_szVS, a_arrMacro);
		VertexShaderMapDX11::iterator it = DX11_mapVertexShader.find(szUniqueName);
		if (it != DX11_mapVertexShader.end())
		{
			return it->second;
		}
		else
		{
			VertexShaderDX11* pShader = new VertexShaderDX11(a_szVS, a_arrMacro);
			pShader->AddRef();
			DX11_mapVertexShader.insert(szUniqueName, pShader);
			return pShader;
		}
	}

}