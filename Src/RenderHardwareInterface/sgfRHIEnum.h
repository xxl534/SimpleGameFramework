#pragma once

/********************************************************************
	created:	2018/06/20
	created:	20:6:2018   8:29
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\sgfRHIEnum.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface
	file base:	sgfRHIEnum
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	enum ERHIDeviceType
	{
		ERHIDeviceType_Invalid = -1,
		ERHIDeviceType_DX11,
	};

	enum ERHIShaderConstanceType
	{
		ERHIShaderConstanceType_Invalid = -1,
		ERHIShaderConstanceType_1f,
		ERHIShaderConstanceType_2f,
		ERHIShaderConstanceType_3f,
		ERHIShaderConstanceType_4f,
		ERHIShaderConstanceType_1i,
		ERHIShaderConstanceType_2i,
		ERHIShaderConstanceType_3i,
		ERHIShaderConstanceType_4i,
		ERHIShaderConstanceType_1b,
		ERHIShaderConstanceType_2b,
		ERHIShaderConstanceType_3b,
		ERHIShaderConstanceType_4b,
		ERHIShaderConstanceType_Matrix2,
		ERHIShaderConstanceType_Matrix3,
		ERHIShaderConstanceType_Matrix4,
		ERHIShaderConstanceType_Sampler2D,
		ERHIShaderConstanceType_Sampler3D,
		ERHIShaderConstanceType_SamplerCube,
		ERHIShaderConstanceType_Count,
	};

}
