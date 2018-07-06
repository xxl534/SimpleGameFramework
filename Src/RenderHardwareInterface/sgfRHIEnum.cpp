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

}