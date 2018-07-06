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

	enum ERHIShaderConstantType
	{
		ERHIShaderConstantType_Invalid = -1,
		ERHIShaderConstantType_1f,
		ERHIShaderConstantType_2f,
		ERHIShaderConstantType_3f,
		ERHIShaderConstantType_4f,
		ERHIShaderConstantType_1i,
		ERHIShaderConstantType_2i,
		ERHIShaderConstantType_3i,
		ERHIShaderConstantType_4i,
		ERHIShaderConstantType_1b,
		ERHIShaderConstantType_2b,
		ERHIShaderConstantType_3b,
		ERHIShaderConstantType_4b,
		ERHIShaderConstantType_Matrix2,
		ERHIShaderConstantType_Matrix3,
		ERHIShaderConstantType_Matrix4,
		ERHIShaderConstantType_Sampler2D,
		ERHIShaderConstantType_Sampler3D,
		ERHIShaderConstantType_SamplerCube,
		ERHIShaderConstantType_Count,
	};

	extern const String&			RHIShaderConstantTypeToString(ERHIShaderConstantType a_eType);
	extern ERHIShaderConstantType	RHIStringToShaderConstantType(const String& a_szType, ERHIShaderConstantType a_eDefault = ERHIShaderConstantType_Invalid);
	extern int32					RHIGetShaderConstantTypeSize(ERHIShaderConstantType a_eType);

	enum ERHIResourceUsage
	{
		ERHIResourceUsage_Static,		// The resource will be created, filled, and never repacked.
		ERHIResourceUsage_Dynamic,		// The resource will be repacked in-frequently.
		ERHIResourceUsage_Volatile,		// The resource will be repacked EVERY frame.
	};

	enum ERHISamplerFilter
	{
		ERHISamplerFilter_Invalid = -1,
		ERHISamplerFilter_Min_Mag_Mip_Point,
		ERHISamplerFilter_Min_Mag_Point_Mip_Linear,
		ERHISamplerFilter_Min_Point_Mag_Linear_Mip_Point,
		ERHISamplerFilter_Min_Point_Mag_Mip_Linear,
		ERHISamplerFilter_Min_Linear_Mag_Mip_Point,
		ERHISamplerFilter_Min_Linear_Mag_Point_Mip_Linear,
		ERHISamplerFilter_Min_Mag_Linear_Mip_Point,
		ERHISamplerFilter_Min_Mag_Mip_Linear,
		ERHISamplerFilter_Anisotropic,
		ERHISamplerFilter_Comparison_Min_Mag_Mip_Point,
		ERHISamplerFilter_Comparison_Min_Mag_Point_Mip_Linear,
		ERHISamplerFilter_Comparison_Min_Point_Mag_Linear_Mip_Point,
		ERHISamplerFilter_Comparison_Min_Point_Mag_Mip_Linear,
		ERHISamplerFilter_Comparison_Min_Linear_Mag_Mip_Point,
		ERHISamplerFilter_Comparison_Min_Linear_Mag_Point_Mip_Linear,
		ERHISamplerFilter_Comparison_Min_Mag_Linear_Mip_Point,
		ERHISamplerFilter_Comparison_Min_Mag_Mip_Linear,
		ERHISamplerFilter_Comparison_Anisotropic,
		ERHISamplerFilter_Count,
	};
	extern const String&			RHISamplerFilterToString(ERHISamplerFilter a_eFilter);
	extern ERHISamplerFilter		RHIStringToSamplerFilter(const String& a_szFilter, ERHISamplerFilter a_eDefault = ERHISamplerFilter_Invalid);
	//-------------------------------------------------------------------------
	enum ERHIClampMode
	{
		ERHIClampMode_Invalid = -1,
		ERHIClampMode_Repeat,
		ERHIClampMode_Clamp,
		ERHIClampMode_Mirror,
		ERHIClampMode_Border,
		ERHIClampMode_ClampToEdge,
		ERHIClampMode_Count,
	};
	extern const String&			RHIClampModeToString(ERHIClampMode a_eMode);
	extern ERHIClampMode			RHIStringToClampMode(const String& a_szType, ERHIClampMode a_eDefault = ERHIClampMode_Invalid);


	enum ERHIPixelFormat
	{
		ERHIPixelFormat_Default = -1,
		ERHIPixelFormat_A8,
		ERHIPixelFormat_R8G8B8A8,
		ERHIPixelFormat_R8G8B8X8,
		ERHIPixelFormat_R4G4B4A4,
		ERHIPixelFormat_R5G6B5,
		ERHIPixelFormat_R8G8B8,
		ERHIPixelFormat_PVR_RGB,
		ERHIPixelFormat_PVR_RGBA,
		ERHIPixelFormat_XTC,
		ERHIPixelFormat_DXT,
		ERHIPixelFormat_ETC1,
		ERHIPixelFormat_Depth,
	};
}
