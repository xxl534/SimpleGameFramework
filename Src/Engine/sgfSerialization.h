#pragma once
/********************************************************************
	created:	2018/07/06
	created:	6:7:2018   8:01
	filename: 	E:\SimpleGameFramework\Src\Engine\sgfSerialization.h
	file path:	E:\SimpleGameFramework\Src\Engine
	file base:	sgfSerialization
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	class Serialization
	{
	public:
		static bool		ReadFloatArray(const char* a_szSrc, float* a_pData, int32 a_nCount);
		static bool		ReadFloat2Array(const char* a_szSrc, float* a_pData, int32 a_nCount);
		static bool		ReadFloat3Array(const char* a_szSrc, float* a_pData, int32 a_nCount);
		static bool		ReadFloat4Array(const char* a_szSrc, float* a_pData, int32 a_nCount);
		static bool		ReadIntArray(const char* a_szSrc, int32* a_pData, int32 a_nCount);
		static bool		ReadInt2Array(const char* a_szSrc, int32* a_pData, int32 a_nCount);
		static bool		ReadInt3Array(const char* a_szSrc, int32* a_pData, int32 a_nCount);
		static bool		ReadInt4Array(const char* a_szSrc, int32* a_pData, int32 a_nCount);
		static bool		ReadMatrix2Array(const char* a_szSrc, float* a_pData, int32 a_nCount);
		static bool		ReadMatrix3Array(const char* a_szSrc, float* a_pData, int32 a_nCount);
		static bool		ReadMatrix4Array(const char* a_szSrc, float* a_pData, int32 a_nCount);

		static bool		ReadFloatArray( String& a_szBuffer, const float* a_pData, int32 a_nCount);
		static bool		ReadFloat2Array(String& a_szBuffer, const float* a_pData, int32 a_nCount);
		static bool		ReadFloat3Array(String& a_szBuffer, const float* a_pData, int32 a_nCount);
		static bool		ReadFloat4Array(String& a_szBuffer, const float* a_pData, int32 a_nCount);
		static bool		ReadIntArray(String& a_szBuffer, const int32* a_pData, int32 a_nCount);
		static bool		ReadInt2Array(String& a_szBuffer, const int32* a_pData, int32 a_nCount);
		static bool		ReadInt3Array(String& a_szBuffer, const int32* a_pData, int32 a_nCount);
		static bool		ReadInt4Array(String& a_szBuffer, const int32* a_pData, int32 a_nCount);
		static bool		ReadMatrix2Array(String& a_szBuffer, const float* a_pData, int32 a_nCount);
		static bool		ReadMatrix3Array(String& a_szBuffer, const float* a_pData, int32 a_nCount);
		static bool		ReadMatrix4Array(String& a_szBuffer, const float* a_pData, int32 a_nCount);

		static int32		GetTypeAlignSize(int32 a_nSize, int32 a_nAlignment = 4);
		static int32		GetStringAlignSize(const String& a_szStr, int32 a_nAlignment = 4);

	public: //keys
		//shader
		static String	k_ShaderEffect;
		static String	k_ShaderEffectTexture;
		static String	k_ShaderEffectProp;
		static String	k_ShaderEffectType;
		static String	k_ShaderEffectClampU;
		static String	k_ShaderEffectClampV;
		static String	k_ShaderEffectClampW;
		static String	k_ShaderEffectFilter;
		static String	k_ShaderEffectPass;
		static String	k_ShaderEffectQueue;
		static String	k_ShaderEffectTechDefault;
		static String	k_ShaderEffectTechFog;
		static String	k_ShaderEffectTechSkinning;
		static String	k_ShaderEffectTechLightmap;
		static String	k_ShaderEffectShader;
		static String	k_ShaderEffectVS;
		static String	k_ShaderEffectPS;
		//shader rasterizer
		static String	k_Rasterizer;
		static String	k_RasterizerFillMode;
		static String	k_RasterizerCullMode;
		static String	k_RasterizerFront;
		static String	k_RasterizerDepthBias;
		static String	k_RasterizerDepthBiasClamp;
		static String	k_RasterizerSlopeScaleDepthBias;
		static String	k_RasterizerDepthClipEnable;
		static String	k_RasterizerScissor;
		static String	k_RasterizerMultiSample;
		static String	k_RasterizerAntialiasedLine;
		//shader blend
		static String	k_Blend;
		static String	k_BlendAlphaToCoverage;
		static String	k_BlendIndependent;
		static String	k_BlendTarget;
		static String	k_BlendEnable;
		static String	k_BlendSrcColor;
		static String	k_BlendDstColor;
		static String	k_BlendColorFunc;
		static String	k_BlendSrcAlpha;
		static String	k_BlendDstAlpha;
		static String	k_BlendAlphaFunc;
		static String	k_BlendWriteR;
		static String	k_BlendWriteG;
		static String	k_BlendWriteB;
		static String	k_BlendWriteA;
		//shader depth stencil
		static String	k_DepthStencil;
		static String	k_DepthStencilDepthEnable;
		static String	k_DepthStencilDepthWriteMask;
		static String	k_DepthStencilStencilEnable;
		static String	k_DepthStencilStencilReadMask;
		static String	k_DepthStencilStencilWriteMask;
		static String	k_DepthStencilDepthFunc;
		static String	k_DepthStencilFrontStencilFail;
		static String	k_DepthStencilFrontStencilDepthFail;
		static String	k_DepthStencilFrontStencilPass;
		static String	k_DepthStencilFrontStencilFunc;
		static String	k_DepthStencilBackStencilFail;
		static String	k_DepthStencilBackStencilDepthFail;
		static String	k_DepthStencilBackStencilPass;
		static String	k_DepthStencilBackStencilFunc;

		static String	k_Name;
		static String	k_Count;
		static String	k_DisplayName;
		static String	k_Value;
		static String	k_Visible;
	};
}