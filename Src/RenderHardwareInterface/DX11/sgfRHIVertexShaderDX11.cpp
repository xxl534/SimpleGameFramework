#include "sgfRHIPCH.h"
#include "sgfRHIDX11Private.h"
#include "sgfRHIVertexShaderDX11.h"

namespace sgf
{
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
			else if (a_sDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
			{
				eFormat = DXGI_FORMAT_R32_FLOAT;
			}
		}
		else if (a_sDesc.Mask <= 3)
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

	//----------------------------------------
	RHIVertexShaderDX11::RHIVertexShaderDX11(const String& a_szVS, const TArray<RHIEffect::Macro>& a_arrMacro)
		:m_pShader(NULL)
	{
		_Initialize(a_szVS, a_arrMacro);
	}

	//----------------------------------------
	RHIVertexShaderDX11::~RHIVertexShaderDX11()
	{
		SAFE_RELEASE(m_pShader);
	}

	//----------------------------------------
	void 
		RHIVertexShaderDX11::Setup(const RHIShaderConstantsRef& a_refCons, const RHIShaderTexturesRef& a_refTexs)
	{

	}

	//----------------------------------------
	void 
		RHIVertexShaderDX11::_Initialize(const String & a_szFile, const TArray<RHIEffect::Macro>& a_arrMacro)
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
	void 
		RHIVertexShaderDX11::_InitAttribute(ID3D11ShaderReflection* a_pReflection)
	{
		D3D11_SHADER_DESC sDesc;
		a_pReflection->GetDesc(&sDesc);

		D3D11_SIGNATURE_PARAMETER_DESC sInputDesc;
		for (UINT i = 0; i < sDesc.InputParameters; ++i)
		{
			a_pReflection->GetInputParameterDesc(i, &sInputDesc);
			AttributeDecl sAttrDecl;
			sAttrDecl.m_szSemanticName = sInputDesc.SemanticName;
			sAttrDecl.m_nSemanticIndex = sInputDesc.SemanticIndex;
			DXGI_FORMAT eFormat = _ParseInputParameterFormat(sInputDesc);
			sAttrDecl.m_eType = RHIFromDX11_FormatType(eFormat);
			m_arrAttrDecl.push_back(sAttrDecl);
		}
	}

	//----------------------------------------
	void 
		RHIVertexShaderDX11::_InitUniform(ID3D11ShaderReflection * a_pReflection)
	{
		D3D11_SHADER_DESC sDesc;
		a_pReflection->GetDesc(&sDesc);

		for (UINT i = 0; i < sDesc.ConstantBuffers; ++i)
		{
			D3D11_SHADER_BUFFER_DESC sBufferDesc;
			ID3D11ShaderReflectionConstantBuffer* pBuffer = a_pReflection->GetConstantBufferByIndex(i);
			pBuffer->GetDesc(&sBufferDesc);

			D3D11_SHADER_INPUT_BIND_DESC sBindDesc;
			a_pReflection->GetResourceBindingDesc(i, &sBindDesc);

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
				decl.m_nStride = sVarDesc.Size;
				decl.m_nCount = sTypeDesc.Rows * sTypeDesc.Columns * (sTypeDesc.Elements > 0 ? sTypeDesc.Elements : 1);
				decl.m_eType = RHIFromDX11_VariableType(sTypeDesc.Type);
			}

		}
	}

	//----------------------------------------
	TArray<D3D_SHADER_MACRO, false, false> 
		RHIVertexShaderDX11::_ToDx11Marco(const TArray<RHIEffect::Macro>& a_arrMacro)
	{
		TArray<D3D_SHADER_MACRO, false, false> arrDxMacro;
		arrDxMacro.resize(a_arrMacro.size() + 1);
		for (int32 i = 0; i < a_arrMacro.size(); ++i)
		{
			arrDxMacro[i].Name = a_arrMacro[i].a_szKey.c_str();
			arrDxMacro[i].Definition = a_arrMacro[i].a_szValue.c_str();
		}
		arrDxMacro.back().Name = NULL;
		arrDxMacro.back().Definition = NULL;
		return arrDxMacro;
	}

}