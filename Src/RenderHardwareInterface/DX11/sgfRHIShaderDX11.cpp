#include "sgfRHIPCH.h"
#include "sgfRHIDX11Private.h"
#include <d3d11shader.h>
#include "sgfRHIShaderDX11.h"


namespace sgf
{ 
	typedef THashMap<String, RHIShaderDX11*> ShaderMapDX11;
	typedef THashMap<String, ID3D11VertexShader*> VertexShaderMapDX11;
	typedef THashMap<String, ID3D11PixelShader*> PixelShaderMapDX11;
	typedef THashMap<void*, ID3D11ShaderReflection*> ShaderReflectionMapDX11;
	ShaderMapDX11 DX11_mapShader;
	VertexShaderMapDX11 DX11_mapVertexShader;
	PixelShaderMapDX11	DX11_mapPixelShader;
	ShaderReflectionMapDX11	DX11_mapShaderReflection;
	RHIShaderDX11* DX11_pShader = NULL;
	//-------------------------------------------------------------------------
	RHIShaderDX11::RHIShaderDX11(const String& a_szVS, const String& a_szPS, const TArray<RHIShader::Macro>& a_arrMacro)
		:m_pVertexShader(NULL)
		,m_pPixelShader(NULL)
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
		RHIShaderDX11::Init()
	{

	}

	//-------------------------------------------------------------------------
	void 
		RHIShaderDX11::Tick()
	{

	}

	//-------------------------------------------------------------------------
	void 
		RHIShaderDX11::Exit()
	{
		for (ShaderMapDX11::iterator it = DX11_mapShader.begin(); it != DX11_mapShader.end(); ++it)
		{
			it->second->Release();
		}
		DX11_mapShader.clear();
		for (VertexShaderMapDX11::iterator it = DX11_mapVertexShader.begin(); it != DX11_mapVertexShader.end(); ++it)
		{
			SAFE_RELEASE(it->second);
		}
		DX11_mapVertexShader.clear();
		for (PixelShaderMapDX11::iterator it = DX11_mapPixelShader.begin(); it != DX11_mapPixelShader.end(); ++it)
		{
			SAFE_RELEASE(it->second);
		}
		DX11_mapPixelShader.clear();
	}

	//-------------------------------------------------------------------------
	String 
		_UniqueIndividualShaderName(const String& a_szShader, const TArray<RHIShader::Macro>& a_arrMacro)
	{
		String szName = a_szShader;
		for (int32 i = 0; i < a_arrMacro.size(); ++i)
		{
			szName.append(a_arrMacro[i].a_szKey);
			szName.append(a_arrMacro[i].a_szValue);
		}
		return szName;
	}

	//-------------------------------------------------------------------------
	TArray<D3D_SHADER_MACRO,false,false> 
		_GetDX11Marco(const TArray<RHIShader::Macro>& a_arrMacro)
	{
		TArray<D3D_SHADER_MACRO, false, false> arrDXMacro(a_arrMacro.size() + 1);
		for (int32 i = 0; i < a_arrMacro.size(); ++i)
		{
			arrDXMacro[i].Name = a_arrMacro[i].a_szKey.c_str();
			arrDXMacro[i].Definition = a_arrMacro[i].a_szValue.c_str();
		}
		arrDXMacro.back().Name = NULL;
		arrDXMacro.back().Definition = NULL;
		return arrDXMacro;
	}

	//-------------------------------------------------------------------------
	ID3D11VertexShader* 
		_CreateVertexShader(const String& a_szVS, const TArray<RHIShader::Macro>& a_arrMacro, ID3D11ShaderReflection** out_ppReflection)
	{
		TArray<D3D_SHADER_MACRO, false, false> arrDXMacro = _GetDX11Marco(a_arrMacro);
		ID3D10Blob* sCompiledShader = NULL;
		ID3D10Blob* sCompilationMsgs = NULL;
		HRESULT hr = D3DCompileFromFile(StringHelper::Utf8ToUtf16(a_szVS).c_str(), arrDXMacro.begin(), NULL, "main", "vs_5_0", D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, NULL, &sCompiledShader, &sCompilationMsgs);
		if (sCompilationMsgs != NULL)
		{
			MessageBox(0, (char*)sCompilationMsgs->GetBufferPointer(), 0, 0);
			SAFE_RELEASE(sCompilationMsgs);
		}
		HR(hr);
		ID3D11VertexShader* pVertexShader = NULL;
		HR(DX11_pDevice->CreateVertexShader(sCompiledShader->GetBufferPointer(), sCompiledShader->GetBufferSize(), NULL, &pVertexShader));
		ID3D11ShaderReflection* pReflect;
		HR(D3DReflect(sCompiledShader->GetBufferPointer(), sCompiledShader->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pReflect));
		*out_ppReflection = pReflect;

		SAFE_RELEASE(sCompiledShader);
		return pVertexShader;
	}

	//-------------------------------------------------------------------------
	ID3D11VertexShader* 
		_ParseVertexShader(const String& a_szVS, const TArray<RHIShader::Macro>& a_arrMacro)
	{
		String szName = _UniqueIndividualShaderName(a_szVS, a_arrMacro);
		VertexShaderMapDX11::iterator it = DX11_mapVertexShader.find(szName);
		if (it != DX11_mapVertexShader.end())
		{
			return it->second;
		}
		else
		{
			ID3D11ShaderReflection* pReflect;
			ID3D11VertexShader* pVertexShader = _CreateVertexShader(a_szVS, a_arrMacro, &pReflect);
			DX11_mapVertexShader.insert(szName, pVertexShader);
			if (pVertexShader)
			{
				DX11_mapShaderReflection.insert(pVertexShader, pReflect);
			}
			return pVertexShader;
		}
	}

	//-------------------------------------------------------------------------
	ID3D11PixelShader*
		_CreatePixelShader(const String& a_szPS, const TArray<RHIShader::Macro>& a_arrMacro, ID3D11ShaderReflection** out_ppReflection)
	{
		TArray<D3D_SHADER_MACRO, false, false> arrDXMacro = _GetDX11Marco(a_arrMacro);
		ID3D10Blob* sCompiledShader = NULL;
		ID3D10Blob* sCompilationMsgs = NULL;
		HRESULT hr = D3DCompileFromFile(StringHelper::Utf8ToUtf16(a_szPS).c_str(), arrDXMacro.begin(), NULL, "main", "ps_5_0", D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, NULL, &sCompiledShader, &sCompilationMsgs);
		if (sCompilationMsgs != NULL)
		{
			MessageBox(0, (char*)sCompilationMsgs->GetBufferPointer(), 0, 0);
			SAFE_RELEASE(sCompilationMsgs);
		}
		HR(hr);
		ID3D11PixelShader* pPixelShader = NULL;
		HR(DX11_pDevice->CreatePixelShader(sCompiledShader->GetBufferPointer(), sCompiledShader->GetBufferSize(), NULL, &pPixelShader));
		ID3D11ShaderReflection* pReflect;
		HR(D3DReflect(sCompiledShader->GetBufferPointer(), sCompiledShader->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pReflect));
		*out_ppReflection = pReflect;
		SAFE_RELEASE(sCompiledShader);
		return pPixelShader;
	}

	//-------------------------------------------------------------------------
	ID3D11PixelShader*
		_ParserPixelShader(CONST String& a_szPS, const TArray<RHIShader::Macro>& a_arrMacro)
	{
		String szName = _UniqueIndividualShaderName(a_szPS, a_arrMacro);
		PixelShaderMapDX11::iterator it = DX11_mapPixelShader.find(szName);
		if (it != DX11_mapPixelShader.end())
		{
			return it->second;
		}
		else
		{
			ID3D11ShaderReflection* pReflect;
			ID3D11PixelShader* pPixelShader = _CreatePixelShader(a_szPS, a_arrMacro, &pReflect);
			DX11_mapPixelShader.insert(szName, pPixelShader);
			if( pPixelShader )
			{
				DX11_mapShaderReflection.insert(pPixelShader, pReflect);
			}
			return pPixelShader;
		}
	}

	//-------------------------------------------------------------------------
	void 
		RHIShaderDX11::_Initialize(const String& a_szVS, const String& a_szPS, const TArray<RHIShader::Macro>& a_arrMacro)
	{
		m_pVertexShader = _ParseVertexShader(a_szVS, a_arrMacro);
		m_pPixelShader = _ParserPixelShader(a_szPS, a_arrMacro);
		_InitAttribute();
		_InitUniform();
	}

	DXGI_FORMAT
		_ParseInputParameterFormat(D3D11_SIGNATURE_PARAMETER_DESC& a_sDesc)
	{
		DXGI_FORMAT eFormat = DXGI_FORMAT_UNKNOWN;
		if (a_sDesc.Mask == 1)
		{
			if (a_sDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
			{
				eFormat = DXGI_FORMAT_R32_UINT;
			}
			else if (a_sDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
			{
				eFormat = DXGI_FORMAT_R32_SINT;
			}
			else if( a_sDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
			{
				eFormat = DXGI_FORMAT_R32_FLOAT;
			}
		}
		else if(a_sDesc.Mask <= 3)
		{
			if (a_sDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
			{
				eFormat = DXGI_FORMAT_R32G32_UINT;
			}
			else if (a_sDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
			{
				eFormat = DXGI_FORMAT_R32G32_SINT;
			}
			else if (a_sDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
			{
				eFormat = DXGI_FORMAT_R32G32_FLOAT;
			}
		}
		else if (a_sDesc.Mask <= 7)
		{
			if (a_sDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
			{
				eFormat = DXGI_FORMAT_R32G32B32_UINT;
			}
			else if (a_sDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
			{
				eFormat = DXGI_FORMAT_R32G32B32_SINT;
			}
			else if (a_sDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
			{
				eFormat = DXGI_FORMAT_R32G32B32_FLOAT;
			}
		}
		else if (a_sDesc.Mask <= 15)
		{
			if (a_sDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
			{
				eFormat = DXGI_FORMAT_R32G32B32A32_UINT;
			}
			else if (a_sDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
			{
				eFormat = DXGI_FORMAT_R32G32B32A32_SINT;
			}
			else if (a_sDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
			{
				eFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
			}
		}
		return eFormat;
	}

	//-------------------------------------------------------------------------
	void 
		RHIShaderDX11::_InitAttribute()
	{
		if (m_pVertexShader && DX11_mapShaderReflection.hasKey( m_pVertexShader ) )
		{
			ID3D11ShaderReflection* pReflect = DX11_mapShaderReflection[m_pVertexShader];
			D3D11_SHADER_DESC sDesc;
			pReflect->GetDesc(&sDesc);

			D3D11_SIGNATURE_PARAMETER_DESC sInputDesc;
			for (UINT i = 0; i < sDesc.InputParameters; ++i)
			{
				pReflect->GetInputParameterDesc(i, &sInputDesc);
				AttributeDecl sAttrDecl;
				sAttrDecl.m_szSemanticName = sInputDesc.SemanticName;
				sAttrDecl.m_nSemanticIndex = sInputDesc.SemanticIndex;
				DXGI_FORMAT eFormat = _ParseInputParameterFormat(sInputDesc);
				sAttrDecl.m_eType = RHIFromDX11_FormatType(eFormat);
				m_arrAttrDecl.push_back(sAttrDecl);
			}
		}
	}

	//-------------------------------------------------------------------------
	void 
		RHIShaderDX11::_InitUniform()
	{

	}

	void RHIShaderDX11::_InitShaderUniform(void* a_pShader)
	{
		if (DX11_mapShaderReflection.hasKey(a_pShader))
		{
			ID3D11ShaderReflection* pReflect = DX11_mapShaderReflection[a_pShader];
			D3D11_SHADER_DESC sDesc;
			pReflect->GetDesc(&sDesc);

			for (UINT i = 0; i < sDesc.ConstantBuffers; ++i)
			{
				D3D11_SHADER_BUFFER_DESC sBufferDesc;
				ID3D11ShaderReflectionConstantBuffer* pBuffer = pReflect->GetConstantBufferByIndex(i);
				pBuffer->GetDesc(&sBufferDesc);

				for (UINT j = 0; j < sBufferDesc.Variables; ++j)
				{
					ID3D11ShaderReflectionVariable* pVariable = pBuffer->GetVariableByIndex(j);
					D3D11_SHADER_VARIABLE_DESC sVarDesc;
					pVariable->GetDesc(&sVarDesc);

					D3D11_SHADER_TYPE_DESC sTypeDesc;
					ID3D11ShaderReflectionType* pType = pVariable->GetType();
					pType->GetDesc(&sTypeDesc);

					RHIShaderConstantDecl decl;
					decl.m_szName = sVarDesc.Name;
					decl.m_nCount = sVarDesc.Size;
				}
			}
		}
	}

	//-------------------------------------------------------------------------
	String 
		_UniqueShaderName(const String& a_szVS, const String& a_szPS, const TArray<RHIShader::Macro>& a_arrMacro)
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
