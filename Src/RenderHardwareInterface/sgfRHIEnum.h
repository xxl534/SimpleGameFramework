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

	//-------------------------------------------------------------------------
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

	//-------------------------------------------------------------------------
	enum ERHIFillMode
	{
		ERHIFillMode_Invalid = -1,
		ERHIFillMode_Wireframe,		//貌似GLES2是不支持这么搞滴
		ERHIFillMode_Solid,
		ERHIFillMode_Count,
	};
	extern String					RHIFillModeToString(ERHIFillMode eMode);
	extern ERHIFillMode				RHIStringToFillMode(const String& szType, ERHIFillMode eDefault = ERHIFillMode_Invalid);

	//------------------------------------------------------------------------
	enum ERHICullMode
	{
		ERHICullMode_Invalid = -1,
		ERHICullMode_Front,
		ERHICullMode_Back,
		ERHICullMode_None,
		ERHICullMode_Count,
	};
	extern String					RHICullModeToString(ERHICullMode eMode);
	extern ERHICullMode				RHIStringToCullMode(const String& szType, ERHICullMode eDefault = ERHICullMode_Invalid);

	//-------------------------------------------------------------------------
	enum ERHIBlend
	{
		ERHIBlend_Invalid = -1,
		ERHIBlend_Zero,
		ERHIBlend_One,
		ERHIBlend_SrcColor,
		ERHIBlend_InvSrcColor,
		ERHIBlend_SrcAlpha,
		ERHIBlend_InvSrcAlpha,
		ERHIBlend_DestAlpha,
		ERHIBlend_InvDestAlpha,
		ERHIBlend_DestColor,
		ERHIBlend_InvDestColor,
		ERHIBlend_SrcAlphaSat,
		ERHIBlend_BlendFactor,
		ERHIBlend_InvBlendFactor,
		ERHIBlend_Src1Color,
		ERHIBlend_InvSrc1Color,
		ERHIBlend_Src1Alpha,
		ERHIBlend_InvSrc1Alpha,
		ERHIBlend_Count,
	};
	extern String					RHIBlendToString(ERHIBlend eBlend);
	extern ERHIBlend				RHIStringToBlend(const String& szBlend, ERHIBlend eDefault = ERHIBlend_Invalid);

	//-------------------------------------------------------------------------
	enum ERHIBlendFunc
	{
		ERHIBlendFunc_Invalid = -1,
		ERHIBlendFunc_Add,
		ERHIBlendFunc_Sub,
		ERHIBlendFunc_RevSub,
		ERHIBlendFunc_Min,
		ERHIBlendFunc_Max,
		ERHIBlendFunc_Count,
	};
	extern String					RHIBlendFuncToString(ERHIBlendFunc eFunc);
	extern ERHIBlendFunc			RHIStringToBlendFunc(const String& szFunc, ERHIBlendFunc eDefault = ERHIBlendFunc_Invalid);

	//-------------------------------------------------------------------------
	enum ERHIComparisonFunc
	{
		ERHIComparisonFunc_Invalid = -1,
		ERHIComparisonFunc_Never,
		ERHIComparisonFunc_Less,
		ERHIComparisonFunc_Equal,
		ERHIComparisonFunc_LEqual,
		ERHIComparisonFunc_Greater,
		ERHIComparisonFunc_NotEqual,
		ERHIComparisonFunc_GEqual,
		ERHIComparisonFunc_Always,
		ERHIComparisonFunc_Count,
	};
	extern String					RHIComparisonFuncToString(ERHIComparisonFunc eFunc);
	extern ERHIComparisonFunc		RHIStringToComparisonFunc(const String& szFunc, ERHIComparisonFunc eDefault = ERHIComparisonFunc_Invalid);

	//-------------------------------------------------------------------------
	enum ERHIStencilFunc
	{
		ERHIStencilFunc_Invalid = -1,
		ERHIStencilFunc_Keep,
		ERHIStencilFunc_Zero,
		ERHIStencilFunc_Replace,
		ERHIStencilFunc_IncrSat,
		ERHIStencilFunc_DecrSat,
		ERHIStencilFunc_Invert,
		ERHIStencilFunc_Incr,
		ERHIStencilFunc_Decr,
		ERHIStencilFunc_Count,
	};
	extern String					RHIStencilFuncToString(ERHIStencilFunc eFunc);
	extern ERHIStencilFunc			RHIStringToStencilFunc(const String& szFunc, ERHIStencilFunc eDefault = ERHIStencilFunc_Invalid);
}
