#include "sgfRHIPCH.h"
#include "sgfRHIDX11Private.h"
#include "sgfShaderConstantBufferDX11.h"

namespace sgf
{
	ERHIShaderConstantType s_arrVectorType[4][D3D_SVT_FLOAT + 1] = {
		{	
			ERHIShaderConstantType_Invalid,
			ERHIShaderConstantType_1b,
			ERHIShaderConstantType_1i,
			ERHIShaderConstantType_1f
		},
		{	ERHIShaderConstantType_Invalid,
			ERHIShaderConstantType_2b,
			ERHIShaderConstantType_2i,
			ERHIShaderConstantType_2f
		},
		{	
			ERHIShaderConstantType_Invalid,
			ERHIShaderConstantType_2b,
			ERHIShaderConstantType_3i,
			ERHIShaderConstantType_3f
		},
		{	
			ERHIShaderConstantType_Invalid,
			ERHIShaderConstantType_4b,
			ERHIShaderConstantType_4i,
			ERHIShaderConstantType_4f
		}
	};
	
	//----------------------------------------
	ERHIShaderConstantType
		RHIFromDX11_VariableType(D3D11_SHADER_TYPE_DESC a_sDesc)
	{
		if (a_sDesc.Class == D3D_SVC_SCALAR)
		{
			switch (a_sDesc.Type)
			{
			case D3D_SVT_BOOL:
				return ERHIShaderConstantType_1b;
			case D3D_SVT_INT:
				return ERHIShaderConstantType_1i;
			case D3D_SVT_FLOAT:
				return ERHIShaderConstantType_1f;
			default:
				break;
			}
		}
		else if( a_sDesc.Class == D3D_SVC_VECTOR )
		{
			if (a_sDesc.Type > D3D_SVT_VOID && a_sDesc.Type <= D3D_SVT_FLOAT && a_sDesc.Rows > 0 && a_sDesc.Rows <= 4 )
			{
				return s_arrVectorType[a_sDesc.Rows - 1][a_sDesc.Type];
			 }
		}
		else if( a_sDesc.Class == D3D_SVC_MATRIX_COLUMNS )
		{
			if (a_sDesc.Type == D3D_SVT_FLOAT)
			{
				if (a_sDesc.Rows == 4 && a_sDesc.Columns == 4)
				{
					return ERHIShaderConstantType_Matrix4;
				}
				else if (a_sDesc.Rows == 3 && a_sDesc.Columns == 3)
				{
					return ERHIShaderConstantType_Matrix3;
				}
				else if(a_sDesc.Rows == 2 && a_sDesc.Columns == 2)
				{
					return ERHIShaderConstantType_Matrix2;
				}
			 }
		}
		return ERHIShaderConstantType_Invalid;
	}

	ShaderConstantBufferDX11::ShaderConstantBufferDX11(ID3D11ShaderReflectionConstantBuffer* a_pReflectionBuffer)
		:m_pBuffer(NULL)
		,m_nSize(0)
	{
		D3D11_SHADER_BUFFER_DESC sBufferDesc;
		a_pReflectionBuffer->GetDesc(&sBufferDesc);

		m_szName = sBufferDesc.Name;
		m_nSize = (int32)((sBufferDesc.Size + 15) / 16) * 16;

		for (UINT j = 0; j < sBufferDesc.Variables; ++j)
		{
			ID3D11ShaderReflectionVariable* pVariable = a_pReflectionBuffer->GetVariableByIndex(j);
			RHIShaderConstantDecl decl;
			D3D11_SHADER_VARIABLE_DESC sVarDesc;
			pVariable->GetDesc(&sVarDesc);

			D3D11_SHADER_TYPE_DESC sTypeDesc;
			ID3D11ShaderReflectionType* pType = pVariable->GetType();
			pType->GetDesc(&sTypeDesc);

			decl.m_szName = sVarDesc.Name;
			decl.m_nHandle = sVarDesc.StartOffset;
			decl.m_nCount = sTypeDesc.Elements > 0 ? sTypeDesc.Elements : 1;
			decl.m_eType = RHIFromDX11_VariableType(sTypeDesc);
			decl.m_nStride = RHIGetShaderConstantTypeSize(decl.m_eType);

			m_arrVariableDecl.push_back(decl);
		}

		D3D11_BUFFER_DESC cbDesc;
		cbDesc.ByteWidth = m_nSize;
		cbDesc.Usage = D3D11_USAGE_DYNAMIC;
		cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbDesc.MiscFlags = 0;
		cbDesc.StructureByteStride = 0;

		HR(DX11_pDevice->CreateBuffer(&cbDesc, NULL, &m_pBuffer));
	}

	//----------------------------------------
	ShaderConstantBufferDX11::~ShaderConstantBufferDX11()
	{
		SAFE_RELEASE(m_pBuffer);
	}

	//----------------------------------------
	ID3D11Buffer* 
		ShaderConstantBufferDX11::GetBuffer()
	{
		return m_pBuffer;
	}

}