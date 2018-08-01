#include "sgfRHIPCH.h"
#include "sgfRHIEnum.h"

namespace sgf
{
	static const String s_szInvalid = "invalid";
	static const String s_arrShaderConstantString[ERHIShaderConstantType_Count] = 
	{
		"float",
		"float2",
		"float3",
		"float4",
		"int",
		"int2",
		"int3",
		"int4",
		"bool",
		"bool2",
		"bool3",
		"bool4",
		"mat2",
		"mat3",
		"mat4",
		"tex2d",
		"tex3d",
		"texCube",
	};

	static const int32	s_arrShaderConstantSize[ERHIShaderConstantType_Count] = 
	{
		(int32)sizeof(float),
		(int32)sizeof(float) * 2,
		(int32)sizeof(float) * 3,
		(int32)sizeof(float) * 4,
		(int32)sizeof(int32),
		(int32)sizeof(int32) * 2,
		(int32)sizeof(int32) * 3,
		(int32)sizeof(int32) * 4,
		(int32)sizeof(int32),
		(int32)sizeof(int32) * 2,
		(int32)sizeof(int32) * 3,
		(int32)sizeof(int32) * 4,
		(int32)sizeof(float) * 4,
		(int32)sizeof(float) * 9,
		(int32)sizeof(float) * 16,
		0,
		0,
		0,
	};

	//-------------------------------------------------------------------------
	const String& 
		RHIShaderConstantTypeToString(ERHIShaderConstantType a_eType)
	{
		if (a_eType > ERHIShaderConstantType_Invalid && a_eType < ERHIShaderConstantType_Count)
		{
			return s_arrShaderConstantString[a_eType];
		}
		return s_szInvalid;
	}

	//-------------------------------------------------------------------------
	ERHIShaderConstantType 
		RHIStringToShaderConstantType(const String& a_szType, ERHIShaderConstantType a_eDefault /*= ERHIShaderConstantType_Invalid*/)
	{
		for (int32 i = 0; i < ERHIShaderConstantType_Count; ++i)
		{
			if (a_szType == s_arrShaderConstantString[i])
			{
				return (ERHIShaderConstantType)i;
			}
		}
		return a_eDefault;
	}

	//-------------------------------------------------------------------------
	int32 
		RHIGetShaderConstantTypeSize(ERHIShaderConstantType a_eType)
	{
		if (a_eType > ERHIShaderConstantType_Invalid && a_eType < ERHIShaderConstantType_Count)
		{
			return s_arrShaderConstantSize[a_eType];
		}
		return 0;
	}

	//-------------------------------------------------------------------------
	static const String s_arrSamplerFilterString[ERHISamplerFilter_Count] = {
		"min_mag_mip_point",
		"min_mag_point_mip_linear",
		"min_point_mag_linear_mip_point",
		"min_point_mag_mip_linear",
		"min_linear_mag_mip_point",
		"min_linear_mag_point_mip_linear",
		"min_mag_linear_mip_point",
		"min_mag_mip_linear",
		"anisotropic",
		"comparison_min_mag_mip_point",
		"comparison_min_mag_point_mip_linear",
		"comparison_min_point_mag_linear_mip_point",
		"comparison_min_point_mag_mip_linear",
		"comparison_min_linear_mag_mip_point",
		"comparison_min_linear_mag_point_mip_linear",
		"comparison_min_mag_linear_mip_point",
		"comparison_min_mag_mip_linear",
		"comparison_anisotropic",
	};

	//-------------------------------------------------------------------------
	const String& 
		RHISamplerFilterToString(ERHISamplerFilter a_eFilter)
	{
		if (a_eFilter > ERHISamplerFilter_Invalid && a_eFilter < ERHISamplerFilter_Count)
		{
			return s_arrSamplerFilterString[a_eFilter];
		}
		return s_szInvalid;
	}

	//-------------------------------------------------------------------------
	ERHISamplerFilter 
		RHIStringToSamplerFilter(const String& a_szFilter, ERHISamplerFilter a_eDefault /*= ERHISamplerFilter_Invalid*/)
	{
		for (int32 i = 0; i < ERHISamplerFilter_Count; ++i)
		{
			if (s_arrSamplerFilterString[i] == a_szFilter)
			{
				return ERHISamplerFilter(i);
			}
		}
		return ERHISamplerFilter_Invalid;
	}

	//-------------------------------------------------------------------------
	static const String s_arrClampString[ERHIClampMode_Count] = {
		"repeat",
		"clamp",
		"mirror",
		"border",
		"clamp_to_edge",
	};

	//-------------------------------------------------------------------------
	const String& 
		RHIClampModeToString(ERHIClampMode a_eMode)
	{
		if (a_eMode > ERHIClampMode_Invalid && a_eMode < ERHIClampMode_Count)
		{
			return s_arrClampString[a_eMode];
		}
		return s_szInvalid;
	}

	//-------------------------------------------------------------------------
	ERHIClampMode 
		RHIStringToClampMode(const String & a_szType, ERHIClampMode a_eDefault)
	{
		for (int32 i = 0; i < ERHIClampMode_Count; ++i)
		{
			if (a_szType == s_arrClampString[i])
			{
				return (ERHIClampMode)i;
			}
		}
		return ERHIClampMode_Invalid;
	}

	//-------------------------------------------------------------------------
	static const String s_arrFillModeMap[ERHIFillMode_Count] =
	{
		"wireframe",
		"solid",
	};

	//-------------------------------------------------------------------------
	String
		RHIFillModeToString(ERHIFillMode a_eMode)
	{
		if (a_eMode > ERHIFillMode_Invalid&&a_eMode < ERHIFillMode_Count)
		{
			return s_arrFillModeMap[a_eMode];
		}
		return s_szInvalid;
	}

	//-------------------------------------------------------------------------
	ERHIFillMode
		RHIStringToFillMode(const String& a_szType, ERHIFillMode a_eDefault)
	{
		for (int32 i = 0; i < ERHIFillMode_Count; i++)
		{
			if (a_szType == s_arrFillModeMap[i])
			{
				return (ERHIFillMode)i;
			}
		}
		return a_eDefault;
	}

	//-------------------------------------------------------------------------
	static const String s_arrCullModeMap[ERHICullMode_Count] =
	{
		"front",
		"back",
		"none",
	};

	//-------------------------------------------------------------------------
	String
		RHICullModeToString(ERHICullMode a_eMode)
	{
		if (a_eMode > ERHICullMode_Invalid&&a_eMode < ERHICullMode_Count)
		{
			return s_arrCullModeMap[a_eMode];
		}
		return s_szInvalid;
	}

	//-------------------------------------------------------------------------
	ERHICullMode
		RHIStringToCullMode(const String& a_szType, ERHICullMode a_eDefault)
	{
		for (int32 i = 0; i < ERHICullMode_Count; i++)
		{
			if (a_szType == s_arrCullModeMap[i])
			{
				return (ERHICullMode)i;
			}
		}
		return a_eDefault;
	}

	//-------------------------------------------------------------------------
	static const String s_arrBlendMap[ERHIBlend_Count] =
	{
		"zero",
		"one",
		"src_color",
		"inv_src_color",
		"src_alpha",
		"inv_src_alpha",
		"dest_alpha",
		"inv_dest_alpha",
		"dest_color",
		"inv_dest_color",
		"src_alpha_sat",
		"blend_factor",
		"inv_blend_factor",
		"src1_color",
		"inv_src1_color",
		"src1_alpha",
		"inv_src1_alpha",
	};

	//-------------------------------------------------------------------------
	String
		RHIBlendToString(ERHIBlend a_eBlend)
	{
		if (a_eBlend > ERHIBlend_Invalid&&a_eBlend < ERHIBlend_Count)
		{
			return s_arrBlendMap[a_eBlend];
		}
		return s_szInvalid;
	}

	//-------------------------------------------------------------------------
	ERHIBlend
		RHIStringToBlend(const String& szBlend, ERHIBlend a_eDefault)
	{
		for (int32 i = 0; i < ERHIBlend_Count; i++)
		{
			if (szBlend == s_arrBlendMap[i])
			{
				return (ERHIBlend)i;
			}
		}
		return a_eDefault;
	}

	//-------------------------------------------------------------------------
	static const String s_arrBlendFuncMap[ERHIBlendFunc_Count] =
	{
		"add",
		"sub",
		"rev_sub",
		"min",
		"max",
	};

	//-------------------------------------------------------------------------
	String
		RHIBlendFuncToString(ERHIBlendFunc a_eFunc)
	{
		if (a_eFunc > ERHIBlendFunc_Invalid&&a_eFunc < ERHIBlendFunc_Count)
		{
			return s_arrBlendFuncMap[a_eFunc];
		}
		return s_szInvalid;
	}

	//-------------------------------------------------------------------------
	ERHIBlendFunc
		RHIStringToBlendFunc(const String& a_szFunc, ERHIBlendFunc a_eDefault)
	{
		for (int32 i = 0; i < ERHIBlendFunc_Count; i++)
		{
			if (a_szFunc == s_arrBlendFuncMap[i])
			{
				return (ERHIBlendFunc)i;
			}
		}
		return a_eDefault;
	}

	//-------------------------------------------------------------------------
	static const String s_arrComparisonFuncMap[ERHIComparisonFunc_Count] =
	{
		"never",
		"less",
		"equal",
		"l_equal",
		"greater",
		"not_equal",
		"g_equal",
		"always",
	};

	//-------------------------------------------------------------------------
	String
		RHIComparisonFuncToString(ERHIComparisonFunc a_eFunc)
	{
		if (a_eFunc > ERHIComparisonFunc_Invalid&&a_eFunc < ERHIComparisonFunc_Count)
		{
			return s_arrComparisonFuncMap[a_eFunc];
		}
		return s_szInvalid;
	}

	//-------------------------------------------------------------------------
	ERHIComparisonFunc
		RHIStringToComparisonFunc(const String& a_szFunc, ERHIComparisonFunc a_eDefault)
	{
		for (int32 i = 0; i < ERHIComparisonFunc_Count; i++)
		{
			if (a_szFunc == s_arrComparisonFuncMap[i])
			{
				return (ERHIComparisonFunc)i;
			}
		}
		return a_eDefault;
	}

	//-------------------------------------------------------------------------
	const String s_arrStencilFuncMap[ERHIStencilFunc_Count] =
	{
		"keep",
		"zero",
		"replace",
		"incr_sat",
		"decr_sat",
		"invert",
		"incr",
		"decr",
	};

	//-------------------------------------------------------------------------
	String
		RHIStencilFuncToString(ERHIStencilFunc a_eFunc)
	{
		if (a_eFunc > ERHIStencilFunc_Invalid&&a_eFunc < ERHIStencilFunc_Count)
		{
			return s_arrStencilFuncMap[a_eFunc];
		}
		return s_szInvalid;
	}

	//-------------------------------------------------------------------------
	ERHIStencilFunc
		RHIStringToStencilFunc(const String& a_szFunc, ERHIStencilFunc a_eDefault)
	{
		for (int32 i = 0; i < ERHIStencilFunc_Count; i++)
		{
			if (a_szFunc == s_arrStencilFuncMap[i])
			{
				return (ERHIStencilFunc)i;
			}
		}
		return a_eDefault;
	}
}