#include"sgfRHIPCH.h"
#include"sgfRHIDX11Private.h"
#include"sgfShaderDX11.h"
#include "sgfShaderConstantBufferDX11.h"

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
	ShaderDX11::ShaderDX11()
	{

	}

	//----------------------------------------
	ShaderDX11::~ShaderDX11()
	{
		for (TArray<ShaderConstantBufferDX11*>::iterator it = m_arrConstantBuffer.begin(); it != m_arrConstantBuffer.end(); ++it)
		{
			SAFE_DELETE(*it);
		}
	}

	//----------------------------------------
	void
		ShaderDX11::_InitAttribute(ID3D11ShaderReflection* a_pReflection)
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
		ShaderDX11::_InitUniform(ID3D11ShaderReflection * a_pReflection)
	{
		D3D11_SHADER_DESC sDesc;
		a_pReflection->GetDesc(&sDesc);

		for (UINT i = 0; i < sDesc.ConstantBuffers; ++i)
		{
			ID3D11ShaderReflectionConstantBuffer* pBuffer = a_pReflection->GetConstantBufferByIndex(i);
			ShaderConstantBufferDX11* pConstantBuffer = new ShaderConstantBufferDX11(pBuffer);
			m_arrConstantBuffer.push_back(pConstantBuffer);
		}
	}

	//----------------------------------------
	TArray<D3D_SHADER_MACRO, false, false>
		ShaderDX11::_ToDx11Marco(const TArray<RHIEffect::Macro>& a_arrMacro)
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

	//----------------------------------------
	String 
		ShaderDX11::GetUniqueName(const String & a_szFile, const TArray<RHIEffect::Macro>& a_arrMacro)
	{
		String szUniqueName = a_szFile;
		for (int32 i = 0; i < a_arrMacro.size(); ++i)
		{
			szUniqueName.append(a_arrMacro[i].a_szKey);
			szUniqueName.append(a_arrMacro[i].a_szValue);
		}
		return szUniqueName;
	}

	//----------------------------------------
}