#pragma once
/********************************************************************
	created:	2018/07/11
	created:	11:7:2018   19:56
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11\sgfRHITypeMapDX11.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11
	file base:	sgfRHITypeMapDX11
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	inline D3D11_FILL_MODE			RHIToDX11_FillMode(ERHIFillMode a_eMode);
	inline D3D11_CULL_MODE			RHIToDX11_CullMode(ERHICullMode a_eMode);
	inline ERHIShaderConstantType	RHIFromDX11_FormatType(DXGI_FORMAT a_eFormat);
	inline D3D11_BLEND				RHIToDX11_Blend(ERHIBlend a_eBlend);
	inline D3D11_BLEND_OP			RHIToDX11_BlendOp(ERHIBlendFunc a_eFunc);
	inline D3D11_COMPARISON_FUNC	RHIToDX11_ComparisonFunc(ERHIComparisonFunc a_eFunc);
	inline D3D11_STENCIL_OP			RHIToDX11_StencilOp(ERHIStencilFunc a_eFunc);

	//-------------------------------------------------------------------------
	extern D3D11_FILL_MODE DX11_arrFillMode[ERHIFillMode_Count];
	D3D11_FILL_MODE 
		RHIToDX11_FillMode(ERHIFillMode a_eMode)
	{
		assert(a_eMode > ERHIFillMode_Invalid && a_eMode < ERHIFillMode_Count);
		return DX11_arrFillMode[a_eMode];
	}

	//-------------------------------------------------------------------------
	extern D3D11_CULL_MODE	DX11_arrCullMode[ERHICullMode_Count];
	D3D11_CULL_MODE
		RHIToDX11_CullMode(ERHICullMode a_eMode)
	{
		assert(a_eMode > ERHICullMode_Invalid && a_eMode < ERHICullMode_Count);
		return DX11_arrCullMode[a_eMode];
	}

	//-------------------------------------------------------------------------
	ERHIShaderConstantType 
		RHIFromDX11_FormatType(DXGI_FORMAT a_eFormat)
	{
		switch (a_eFormat)
		{
		case DXGI_FORMAT_R32G32B32A32_FLOAT:
			return ERHIShaderConstantType_4f;
		case DXGI_FORMAT_R32G32B32A32_UINT:
			return ERHIShaderConstantType_4i;
		case DXGI_FORMAT_R32G32B32A32_SINT:
			return ERHIShaderConstantType_4i;
		case DXGI_FORMAT_R32G32B32_FLOAT:
			return ERHIShaderConstantType_3f;
		case DXGI_FORMAT_R32G32B32_UINT:
			return ERHIShaderConstantType_3i;
		case DXGI_FORMAT_R32G32B32_SINT:
			return ERHIShaderConstantType_3i;
		case DXGI_FORMAT_R32G32_FLOAT:
			return ERHIShaderConstantType_2f;
		case DXGI_FORMAT_R32G32_UINT:
			return ERHIShaderConstantType_2i;
		case DXGI_FORMAT_R32G32_SINT:
			return ERHIShaderConstantType_2i;
		case DXGI_FORMAT_R32_FLOAT:
			return ERHIShaderConstantType_1f;
		case DXGI_FORMAT_R32_UINT:
			return ERHIShaderConstantType_1i;
		case DXGI_FORMAT_R32_SINT:
			return ERHIShaderConstantType_1i;
		default:
			return ERHIShaderConstantType_Invalid;
		}
	}

	//-------------------------------------------------------------------------
	extern D3D11_BLEND DX11_arrBlend[ERHIBlend_Count];
	D3D11_BLEND 
		RHIToDX11_Blend(ERHIBlend a_eBlend)
	{
		assert(a_eBlend > ERHIBlend_Invalid && a_eBlend < ERHIBlend_Count);
		return DX11_arrBlend[a_eBlend];
	}

	//-------------------------------------------------------------------------
	extern D3D11_BLEND_OP DX11_arrBlendFunc[ERHIBlendFunc_Count];
	D3D11_BLEND_OP 
		RHIToDX11_BlendOp(ERHIBlendFunc a_eFunc)
	{
		assert(a_eFunc > ERHIBlendFunc_Invalid && a_eFunc < ERHIBlendFunc_Count);
		return DX11_arrBlendFunc[a_eFunc];
	}

	//-------------------------------------------------------------------------
	extern D3D11_COMPARISON_FUNC DX11_arrComparisonFunc[ERHIComparisonFunc_Count];
	D3D11_COMPARISON_FUNC 
		RHIToDX11_ComparisonFunc(ERHIComparisonFunc a_eFunc)
	{
		assert(a_eFunc > ERHIComparisonFunc_Invalid && a_eFunc < ERHIComparisonFunc_Count);
		return DX11_arrComparisonFunc[a_eFunc];
	}

	//-------------------------------------------------------------------------
	extern D3D11_STENCIL_OP DX11_arrStencilOp[ERHIStencilFunc_Count];
	D3D11_STENCIL_OP
		RHIToDX11_StencilOp(ERHIStencilFunc a_eFunc)
	{
		assert(a_eFunc > ERHIStencilFunc_Invalid && a_eFunc < ERHIStencilFunc_Count);
		return DX11_arrStencilOp[a_eFunc];
	}

}