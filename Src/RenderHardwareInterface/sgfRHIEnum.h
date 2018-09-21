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
	extern String					RHIFillModeToString(ERHIFillMode a_eMode);
	extern ERHIFillMode				RHIStringToFillMode(const String& a_szType, ERHIFillMode a_eDefault = ERHIFillMode_Invalid);

	//------------------------------------------------------------------------
	enum ERHICullMode
	{
		ERHICullMode_Invalid = -1,
		ERHICullMode_Front,
		ERHICullMode_Back,
		ERHICullMode_None,
		ERHICullMode_Count,
	};
	extern String					RHICullModeToString(ERHICullMode a_eMode);
	extern ERHICullMode				RHIStringToCullMode(const String& a_szType, ERHICullMode a_eDefault = ERHICullMode_Invalid);

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
	extern String					RHIBlendToString(ERHIBlend a_eBlend);
	extern ERHIBlend				RHIStringToBlend(const String& a_szBlend, ERHIBlend a_eDefault = ERHIBlend_Invalid);

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
	extern String					RHIBlendFuncToString(ERHIBlendFunc a_eFunc);
	extern ERHIBlendFunc			RHIStringToBlendFunc(const String& a_szFunc, ERHIBlendFunc a_eDefault = ERHIBlendFunc_Invalid);

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
	extern String					RHIComparisonFuncToString(ERHIComparisonFunc a_eFunc);
	extern ERHIComparisonFunc		RHIStringToComparisonFunc(const String& a_szFunc, ERHIComparisonFunc a_eDefault = ERHIComparisonFunc_Invalid);

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
	extern String					RHIStencilFuncToString(ERHIStencilFunc a_eFunc);
	extern ERHIStencilFunc			RHIStringToStencilFunc(const String& a_szFunc, ERHIStencilFunc a_eDefault = ERHIStencilFunc_Invalid);

	//-------------------------------------------------------------------------
	enum ERHIColorWriteEnable
	{
		ERHIColorWriteEnable_Invalid = -1,
		ERHIColorWriteEnable_Red = 1,
		ERHIColorWriteEnable_Green = 2,
		ERHIColorWriteEnable_Blue = 4,
		ERHIColorWriteEnable_Alpha = 8,
		ERHIColorWriteEnable_All = (((ERHIColorWriteEnable_Red | ERHIColorWriteEnable_Green) | ERHIColorWriteEnable_Blue) | ERHIColorWriteEnable_Alpha)
	};

	//-------------------------------------------------------------------------
	enum ERHIShaderMatrix
	{
		ERHIShaderMatrix_Invalid = -1,
		ERHIShaderMatrix_World,
		ERHIShaderMatrix_Model,
		ERHIShaderMatrix_View,
		ERHIShaderMatrix_Projection,
		ERHIShaderMatrix_ViewProjection,
		ERHIShaderMatrix_TextureViewProjection,
		ERHIShaderMatrix_WorldView,
		ERHIShaderMatrix_WorldViewInv,
		ERHIShaderMatrix_WorldViewProjection,
		ERHIShaderMatrix_WorldViewProjectionInv,
		ERHIShaderMatrix_SkeletonPalette,
		ERHIShaderMatrix_Max,
	};

	//-------------------------------------------------------------------------
	enum ERHIShaderFloat4
	{
		ERHIShaderFloat4_LightmapTile = ERHIShaderMatrix_Max,
		ERHIShaderFloat4_LightmapFactor,
		ERHIShaderFloat4_PointLightPosition,
		ERHIShaderFloat4_Max,
	};

	//-------------------------------------------------------------------------
	enum ERHIShaderFloat3
	{
		ERHIShaderFloat3_CameraEyeAt = ERHIShaderFloat4_Max,
		ERHIShaderFloat3_CameraLookAt,
		ERHIShaderFloat3_CameraLookUp,
		ERHIShaderFloat3_PointLightColor,
		ERHIShaderFloat3_AmbientColor,
		ERHIShaderFloat3_DirectionalLight0Color,
		ERHIShaderFloat3_DirectionalLight0Dir,
		ERHIShaderFloat3_Max,
	};

	//-------------------------------------------------------------------------
	enum ERHIShaderFloat2
	{
		ERHIShaderFloat2_Max = ERHIShaderFloat3_Max,
	};

	//-------------------------------------------------------------------------
	enum ERHIShaderFloat
	{
		ERHIShaderFloat_Time = ERHIShaderFloat2_Max,
		ERHIShaderFloat_RunningTime,
		ERHIShaderFloat_RunningTimeNoRate,
		ERHIShaderFloat_Elapsed,
		ERHIShaderFloat_ElapsedNoRate,
		ERHIShaderFloat_CameraFov,

		ERHIShaderFloat_DesignWidth,
		ERHIShaderFloat_DesignHeight,
		ERHIShaderFloat_AppWidth,
		ERHIShaderFloat_AppHeight,

		ERHIShaderFloat_FogStart,
		ERHIShaderFloat_FogEnd,
		ERHIShaderFloat_FogRcpDiff,

		ERHIShaderFloat_LightingProfile,

		ERHIShaderFloat_Max,
	};

	//-------------------------------------------------------------------------
	enum ERHIShaderInt4
	{
		ERHIShaderInt4_Max = ERHIShaderFloat_Max,
	};

	//-------------------------------------------------------------------------
	enum ERHIShaderInt3
	{
		ERHIShaderInt3_Max = ERHIShaderInt4_Max,
	};

	//-------------------------------------------------------------------------
	enum ERHIShaderInt2
	{
		ERHIShaderInt2_Max = ERHIShaderInt3_Max,
	};

	//-------------------------------------------------------------------------
	enum ERHIShaderInt
	{
		ERHIShaderInt_Max = ERHIShaderInt2_Max,
	};

	//-------------------------------------------------------------------------
	enum ERHIShaderBool4
	{
		ERHIShaderBool4_Max = ERHIShaderInt_Max,
	};

	//-------------------------------------------------------------------------
	enum ERHIShaderBool3
	{
		ERHIShaderBool3_Max = ERHIShaderBool4_Max,
	};

	//-------------------------------------------------------------------------
	enum ERHIShaderBool2
	{
		ERHIShaderBool2_Max = ERHIShaderBool3_Max,
	};

	//-------------------------------------------------------------------------
	enum ERHIShaderBool
	{
		ERHIShaderBool_FogEnable = ERHIShaderBool2_Max,
		ERHIShaderBool_SkinEnable,
		ERHIShaderBool_LightmapEnable,
		ERHIShaderBool_Max,
	};

	//-------------------------------------------------------------------------
	enum ERHIShaderConstantBuildin
	{
		ERHIShaderConstantBuildin_Max = ERHIShaderBool_Max,
	};
}
