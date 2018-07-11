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
	inline D3D11_FILL_MODE		RHIToDX11_FillMode(ERHIFillMode a_eMode);
	inline D3D11_CULL_MODE		RHIToDX11_CullMode(ERHICullMode a_eMode);


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


}