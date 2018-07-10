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
		static String	k_ShaderEffectRasterizer;
		static String	k_ShaderEffectBlend;
		static String	k_ShaderEffectDepthStencil;

		static String	k_Name;
		static String	k_Count;
		static String	k_DisplayName;
		static String	k_Value;
		static String	k_Visible;
	};
}