#include "sgfEnginePCH.h"
#include "sgfSerialization.h"

namespace sgf
{
	
	//----------------------------------------
	bool 
		Serialization::ReadFloatArray(const char* a_szSrc, float* a_pData, int32 a_nCount)
	{
		if (a_nCount == 1)
		{
			return sscanf(a_szSrc, "%f", a_pData) == 1;
		}
		int32 nStart = 0;
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			if (sscanf(a_szSrc + nStart, "[%f]", a_pData + nIdx * 1) != 1)
			{
				return false;
			}
			++nStart;
			while (a_szSrc[nStart] != '['&& a_szSrc[nStart] != 0)
			{
				++nStart;
			}
			if (a_szSrc[nStart] == 0 && nIdx != a_nCount - 1)
			{
				return false;
			}
		}
		return true;
	}

	//----------------------------------------
	bool 
		Serialization::ReadFloat2Array(const char* a_szSrc, float* a_pData, int32 a_nCount)
	{
		if (a_nCount == 1)
		{
			return sscanf(a_szSrc, "%f,%f", a_pData, a_pData + 1) == 2;
		}
		int32 nStart = 0;
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			if (sscanf(a_szSrc + nStart, "[%f,%f]", a_pData + nIdx * 2, a_pData + nIdx * 2 + 1) != 2)
			{
				return false;
			}
			++nStart;
			while (a_szSrc[nStart] != '['&& a_szSrc[nStart] != 0)
			{
				++nStart;
			}
			if (a_szSrc[nStart] == 0 && nIdx != a_nCount - 1)
			{
				return false;
			}
		}
		return true;
	}

	//----------------------------------------
	bool 
		Serialization::ReadFloat3Array(const char* a_szSrc, float* a_pData, int32 a_nCount)
	{
		if (a_nCount == 1)
		{
			return sscanf(a_szSrc, "%f,%f,%f", a_pData, a_pData + 1, a_pData + 2) == 3;
		}
		int32 nStart = 0;
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			if (sscanf(a_szSrc + nStart, "[%f,%f,%f]", a_pData + nIdx * 3, a_pData + nIdx * 3 + 1, a_pData + nIdx * 3 + 2) != 3)
			{
				return false;
			}
			++nStart;
			while (a_szSrc[nStart] != '['&& a_szSrc[nStart] != 0)
			{
				++nStart;
			}
			if (a_szSrc[nStart] == 0 && nIdx != a_nCount - 1)
			{
				return false;
			}
		}
		return true;
	}

	//----------------------------------------
	bool 
		Serialization::ReadFloat4Array(const char* a_szSrc, float* a_pData, int32 a_nCount)
	{
		if (a_nCount == 1)
		{
			return sscanf(a_szSrc, "%f,%f,%f,%f", a_pData, a_pData + 1, a_pData + 2, a_pData + 3) == 4;
		}
		int32 nStart = 0;
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			if (sscanf(a_szSrc + nStart, "[%f,%f,%f,%f]", a_pData + nIdx * 4, a_pData + nIdx * 4 + 1, a_pData + nIdx * 4 + 2, a_pData + nIdx * 4 + 3) != 4)
			{
				return false;
			}
			++nStart;
			while (a_szSrc[nStart] != '['&& a_szSrc[nStart] != 0)
			{
				++nStart;
			}
			if (a_szSrc[nStart] == 0 && nIdx != a_nCount - 1)
			{
				return false;
			}
		}
		return true;
	}

	//----------------------------------------
	bool
		Serialization::ReadIntArray(const char* a_szSrc, int32* a_pData, int32 a_nCount)
	{
		if (a_nCount == 1)
		{
			return sscanf(a_szSrc, "%d", a_pData) == 1;
		}
		int32 nStart = 0;
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			if (sscanf(a_szSrc + nStart, "[%d]", a_pData + nIdx * 1) != 1)
			{
				return false;
			}
			++nStart;
			while (a_szSrc[nStart] != '['&& a_szSrc[nStart] != 0)
			{
				++nStart;
			}
			if (a_szSrc[nStart] == 0 && nIdx != a_nCount - 1)
			{
				return false;
			}
		}
		return true;
	}

	//----------------------------------------
	bool
		Serialization::ReadInt2Array(const char* a_szSrc, int32* a_pData, int32 a_nCount)
	{
		if (a_nCount == 1)
		{
			return sscanf(a_szSrc, "%d,%d", a_pData, a_pData + 1) == 2;
		}
		int32 nStart = 0;
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			if (sscanf(a_szSrc + nStart, "[%d,%d]", a_pData + nIdx * 2, a_pData + nIdx * 2 + 1) != 2)
			{
				return false;
			}
			++nStart;
			while (a_szSrc[nStart] != '['&& a_szSrc[nStart] != 0)
			{
				++nStart;
			}
			if (a_szSrc[nStart] == 0 && nIdx != a_nCount - 1)
			{
				return false;
			}
		}
		return true;
	}

	//----------------------------------------
	bool
		Serialization::ReadInt3Array(const char* a_szSrc, int32* a_pData, int32 a_nCount)
	{
		if (a_nCount == 1)
		{
			return sscanf(a_szSrc, "%d,%d,%d", a_pData, a_pData + 1, a_pData + 2) == 3;
		}
		int32 nStart = 0;
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			if (sscanf(a_szSrc + nStart, "[%d,%d,%d]", a_pData + nIdx * 3, a_pData + nIdx * 3 + 1, a_pData + nIdx * 3 + 2) != 3)
			{
				return false;
			}
			++nStart;
			while (a_szSrc[nStart] != '['&& a_szSrc[nStart] != 0)
			{
				++nStart;
			}
			if (a_szSrc[nStart] == 0 && nIdx != a_nCount - 1)
			{
				return false;
			}
		}
		return true;
	}

	//----------------------------------------
	bool
		Serialization::ReadInt4Array(const char* a_szSrc, int32* a_pData, int32 a_nCount)
	{
		if (a_nCount == 1)
		{
			return sscanf(a_szSrc, "%d,%d,%d,%d", a_pData, a_pData + 1, a_pData + 2, a_pData + 3) == 4;
		}
		int32 nStart = 0;
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			if (sscanf(a_szSrc + nStart, "[%d,%d,%d,%d]", a_pData + nIdx * 4, a_pData + nIdx * 4 + 1, a_pData + nIdx * 4 + 2, a_pData + nIdx * 4 + 3) != 4)
			{
				return false;
			}
			++nStart;
			while (a_szSrc[nStart] != '['&& a_szSrc[nStart] != 0)
			{
				++nStart;
			}
			if (a_szSrc[nStart] == 0 && nIdx != a_nCount - 1)
			{
				return false;
			}
		}
		return true;
	}

	//----------------------------------------
	bool
		Serialization::ReadMatrix2Array(const char* a_szSrc, float* a_pData, int32 a_nCount)
	{
		if (a_nCount == 1)
		{
			return sscanf(a_szSrc, "%f,%f,%f,%f", a_pData, a_pData + 1, a_pData + 2, a_pData + 3) == 4;
		}
		int32 nStart = 0;
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			if (sscanf(a_szSrc + nStart, "[%f,%f,%f,%f]", a_pData + nIdx * 4, a_pData + nIdx * 4 + 1, a_pData + nIdx * 4 + 2, a_pData + nIdx * 4 + 3) != 4)
			{
				return false;
			}
			++nStart;
			while (a_szSrc[nStart] != '['&& a_szSrc[nStart] != 0)
			{
				++nStart;
			}
			if (a_szSrc[nStart] == 0 && nIdx != a_nCount - 1)
			{
				return false;
			}
		}
		return true;
	}

	//----------------------------------------
	bool
		Serialization::ReadMatrix3Array(const char* a_szSrc, float* a_pData, int32 a_nCount)
	{
		if (a_nCount == 1)
		{
			return sscanf(a_szSrc, "%f,%f,%f,%f,%f,%f,%f,%f,%f",
				a_pData, a_pData + 1, a_pData + 2,
				a_pData + 3, a_pData + 4, a_pData + 5,
				a_pData + 6, a_pData + 7, a_pData + 8) == 9;
		}
		int32 nStart = 0;
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			if (sscanf(a_szSrc + nStart, "[%f,%f,%f,%f,%f,%f,%f,%f,%f]",
				a_pData, a_pData + 1, a_pData + 2,
				a_pData + 3, a_pData + 4, a_pData + 5,
				a_pData + 6, a_pData + 7, a_pData + 8) != 9)
			{
				return false;
			}
			a_pData += 9;
			++nStart;
			while (a_szSrc[nStart] != '['&& a_szSrc[nStart] != 0)
			{
				++nStart;
			}
			if (a_szSrc[nStart] == 0 && nIdx != a_nCount - 1)
			{
				return false;
			}
		}
		return true;
	}

	//----------------------------------------
	bool
		Serialization::ReadMatrix4Array(const char* a_szSrc, float* a_pData, int32 a_nCount)
	{
		if (a_nCount == 1)
		{
			return sscanf(a_szSrc, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", 
				a_pData, a_pData + 1, a_pData + 2, a_pData + 3, 
				a_pData + 4, a_pData + 5, a_pData + 6, a_pData + 7, 
				a_pData + 8, a_pData + 9, a_pData + 10, a_pData + 11,
				a_pData + 12, a_pData + 13, a_pData + 14, a_pData + 15) == 16;
		}
		int32 nStart = 0;
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			if (sscanf(a_szSrc + nStart, "[%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f]",
				a_pData, a_pData + 1, a_pData + 2, a_pData + 3,
				a_pData + 4, a_pData + 5, a_pData + 6, a_pData + 7,
				a_pData + 8, a_pData + 9, a_pData + 10, a_pData + 11,
				a_pData + 12, a_pData + 13, a_pData + 14, a_pData + 15) == 16)
			{
				return false;
			}
			a_pData += 16;
			++nStart;
			while (a_szSrc[nStart] != '['&& a_szSrc[nStart] != 0)
			{
				++nStart;
			}
			if (a_szSrc[nStart] == 0 && nIdx != a_nCount - 1)
			{
				return false;
			}
		}
		return true;
	}

	//----------------------------------------
	void
		Serialization::WriteFloatArray(String& a_szBuffer, const float* a_pData, int32 a_nCount)
	{
		a_szBuffer.clear();
		if (a_nCount == 1)
		{
			a_szBuffer = String::Format("%f", a_pData);
			return;
		}
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			a_szBuffer += String::Format("[%f]", a_pData + nIdx);
		}
	}

	//----------------------------------------
	void
		Serialization::WriteFloat2Array(String& a_szBuffer, const float* a_pData, int32 a_nCount)
	{
		a_szBuffer.clear();
		if (a_nCount == 1)
		{
			a_szBuffer = String::Format("%f,%f", a_pData, a_pData + 1);
			return;
		}
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			a_szBuffer += String::Format("[%f,%f]", a_pData + nIdx * 2, a_pData + nIdx * 2 + 1);
		};
	}

	//----------------------------------------
	void
		Serialization::WriteFloat3Array(String& a_szBuffer, const float* a_pData, int32 a_nCount)
	{
		a_szBuffer.clear();
		if (a_nCount == 1)
		{
			a_szBuffer = String::Format("%f,%f,%f", a_pData, a_pData + 1, a_pData + 2);
			return;
		}
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			a_szBuffer += String::Format("[%f,%f,%f]", a_pData + nIdx * 3, a_pData + nIdx * 3 + 1, a_pData + nIdx * 3 + 2);
		};
	}

	//----------------------------------------
	void
		Serialization::WriteFloat4Array(String& a_szBuffer, const float* a_pData, int32 a_nCount)
	{
		a_szBuffer.clear();
		if (a_nCount == 1)
		{
			a_szBuffer = String::Format("%f,%f,%f,%f", a_pData, a_pData + 1, a_pData + 2, a_pData + 3);
			return;
		}
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			a_szBuffer += String::Format("[%f,%f,%f,%f]", a_pData + nIdx * 4, a_pData + nIdx * 4 + 1, a_pData + nIdx * 4 + 2, a_pData + nIdx * 4 + 3);
		};
	}

	//----------------------------------------
	void
		Serialization::WriteIntArray(String& a_szBuffer, const int32* a_pData, int32 a_nCount)
	{
		a_szBuffer.clear();
		if (a_nCount == 1)
		{
			a_szBuffer = String::Format("%d", a_pData);
			return;
		}
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			a_szBuffer += String::Format("[%d]", a_pData + nIdx * 1);
		};
	}

	//----------------------------------------
	void
		Serialization::WriteInt2Array(String& a_szBuffer, const int32* a_pData, int32 a_nCount)
	{
		a_szBuffer.clear();
		if (a_nCount == 1)
		{
			a_szBuffer = String::Format("%d,%d", a_pData, a_pData + 1);
			return;
		}
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			a_szBuffer += String::Format("[%d,%d]", a_pData + nIdx * 2, a_pData + nIdx * 2 + 1);
		};
	}

	//----------------------------------------
	void
		Serialization::WriteInt3Array(String& a_szBuffer, const int32* a_pData, int32 a_nCount)
	{
		a_szBuffer.clear();
		if (a_nCount == 1)
		{
			a_szBuffer = String::Format("%d,%d,%d", a_pData, a_pData + 1, a_pData + 2);
			return;
		}
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			a_szBuffer += String::Format("[%d,%d,%d]", a_pData + nIdx * 3, a_pData + nIdx * 3 + 1, a_pData + nIdx * 3 + 2);
		};
	}

	//----------------------------------------
	void
		Serialization::WriteInt4Array(String& a_szBuffer, const int32* a_pData, int32 a_nCount)
	{
		a_szBuffer.clear();
		if (a_nCount == 1)
		{
			a_szBuffer = String::Format("%d,%d,%d,%d", a_pData, a_pData + 1, a_pData + 2, a_pData + 3);
			return;
		}
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			a_szBuffer += String::Format("[%d,%d,%d,%d]", a_pData + nIdx * 4, a_pData + nIdx * 4 + 1, a_pData + nIdx * 4 + 2, a_pData + nIdx * 4 + 3);
		};
	}

	//----------------------------------------
	void
		Serialization::WriteMatrix2Array(String& a_szBuffer, const float* a_pData, int32 a_nCount)
	{
		a_szBuffer.clear();
		if (a_nCount == 1)
		{
			a_szBuffer = String::Format("%f,%f,%f,%f", a_pData, a_pData + 1, a_pData + 2, a_pData + 3);
			return;
		}
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			a_szBuffer += String::Format("[%f,%f,%f,%f]", a_pData, a_pData + 1, a_pData + 2, a_pData + 3);
			a_pData += 4;
		};
	}

	//----------------------------------------
	void
		Serialization::WriteMatrix3Array(String& a_szBuffer, const float* a_pData, int32 a_nCount)
	{
		a_szBuffer.clear();
		if (a_nCount == 1)
		{
			a_szBuffer = String::Format("%f,%f,%f,%f,%f,%f,%f,%f,%f", a_pData, a_pData + 1, a_pData + 2,
				a_pData + 3, a_pData + 4, a_pData + 5,
				a_pData + 6, a_pData + 7, a_pData + 8);
			return;
		}
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			a_szBuffer += String::Format("[%f,%f,%f,%f,%f,%f,%f,%f,%f]", a_pData, a_pData + 1, a_pData + 2,
				a_pData + 3, a_pData + 4, a_pData + 5,
				a_pData + 6, a_pData + 7, a_pData + 8);
			a_pData += 9;
		};
	}

	//----------------------------------------
	void
		Serialization::WriteMatrix4Array(String& a_szBuffer, const float* a_pData, int32 a_nCount)
	{
		a_szBuffer.clear();
		if (a_nCount == 1)
		{
			a_szBuffer = String::Format("%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", a_pData, a_pData + 1, a_pData + 2, a_pData + 3,
				a_pData + 4, a_pData + 5, a_pData + 6, a_pData + 7,
				a_pData + 8, a_pData + 9, a_pData + 10, a_pData + 11,
				a_pData + 12, a_pData + 13, a_pData + 14, a_pData + 15);
			return;
		}
		for (int32 nIdx = 0; nIdx < a_nCount; ++nIdx)
		{
			a_szBuffer += String::Format("[%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f]", a_pData, a_pData + 1, a_pData + 2, a_pData + 3,
				a_pData + 4, a_pData + 5, a_pData + 6, a_pData + 7,
				a_pData + 8, a_pData + 9, a_pData + 10, a_pData + 11,
				a_pData + 12, a_pData + 13, a_pData + 14, a_pData + 15);
			a_pData += 16;
		};
	}

	//----------------------------------------
	int32 
		Serialization::GetTypeAlignSize(int32 a_nSize, int32 a_nAlignment /*= 4*/)
	{
		return ((a_nSize + a_nAlignment - 1) / a_nAlignment) * a_nAlignment;
	}

	//----------------------------------------
	int32 
		Serialization::GetStringAlignSize(const String& a_szStr, int32 a_nAlignment /*= 4*/)
	{
		return (a_szStr.length() / a_nAlignment + 1) * a_nAlignment + a_nAlignment;
	}

	//----------------------------------------
	String Serialization::k_ShaderEffect = "effect";
	String Serialization::k_ShaderEffectTexture = "tex";
	String Serialization::k_ShaderEffectProp = "prop";
	String Serialization::k_ShaderEffectType = "type";
	String Serialization::k_ShaderEffectClampU = "clamp_u";
	String Serialization::k_ShaderEffectClampV = "clamp_v";
	String Serialization::k_ShaderEffectClampW = "clamp_w";
	String Serialization::k_ShaderEffectFilter = "filter";
	String Serialization::k_ShaderEffectPass = "pass";
	String Serialization::k_ShaderEffectQueue = "queue";
	String Serialization::k_ShaderEffectTechDefault = "default";
	String Serialization::k_ShaderEffectTechFog = "fog";
	String Serialization::k_ShaderEffectTechSkinning = "skinning";
	String Serialization::k_ShaderEffectTechLightmap = "lightmap";
	String Serialization::k_ShaderEffectShader = "shader";
	String Serialization::k_ShaderEffectVS = "vs";
	String Serialization::k_ShaderEffectPS = "ps";

	String Serialization::k_Rasterizer = "rasterizer";
	String Serialization::k_RasterizerFillMode = "fill";
	String Serialization::k_RasterizerCullMode = "cull";
	String Serialization::k_RasterizerFront = "front";
	String Serialization::k_RasterizerDepthBias = "depth_bias";
	String Serialization::k_RasterizerDepthBiasClamp = "depth_bias_clamp";
	String Serialization::k_RasterizerSlopeScaleDepthBias = "slope_scaled_depth_bias";
	String Serialization::k_RasterizerDepthClipEnable = "depth_clip";
	String Serialization::k_RasterizerScissor = "scissor";
	String Serialization::k_RasterizerMultiSample = "multi_sample";
	String Serialization::k_RasterizerAntialiasedLine = "antialiased_line";

	String Serialization::k_Blend = "blend";
	String Serialization::k_BlendAlphaToCoverage = "alpha_to_coverage";
	String Serialization::k_BlendIndependent = "independent_blend";
	String Serialization::k_BlendTarget = "target";
	String Serialization::k_BlendEnable = "enable";
	String Serialization::k_BlendSrcColor = "src";
	String Serialization::k_BlendDstColor = "dst";
	String Serialization::k_BlendColorFunc = "func";
	String Serialization::k_BlendSrcAlpha = "src_a";
	String Serialization::k_BlendDstAlpha = "dst_a";
	String Serialization::k_BlendAlphaFunc = "func_a";
	String Serialization::k_BlendWriteR = "write_r";
	String Serialization::k_BlendWriteG = "write_g";
	String Serialization::k_BlendWriteB = "write_b";
	String Serialization::k_BlendWriteA = "write_a";

	String Serialization::k_DepthStencil = "depth_stencil";
	String Serialization::k_DepthStencilDepthEnable = "depth_enable";
	String Serialization::k_DepthStencilDepthWriteMask = "depth_write";
	String Serialization::k_DepthStencilStencilEnable = "stencil_enable";
	String Serialization::k_DepthStencilStencilReadMask = "stencil_read";
	String Serialization::k_DepthStencilStencilWriteMask = "stencil_write";
	String Serialization::k_DepthStencilDepthFunc = "depth_func";
	String Serialization::k_DepthStencilFrontStencilFail = "front_stencil_fail";
	String Serialization::k_DepthStencilFrontStencilDepthFail = "front_stencil_depth_fail";
	String Serialization::k_DepthStencilFrontStencilPass = "front_stencil_pass";
	String Serialization::k_DepthStencilFrontStencilFunc = "front_stencil_func";
	String Serialization::k_DepthStencilBackStencilFail = "back_stencil_fail";
	String Serialization::k_DepthStencilBackStencilDepthFail = "back_stencil_depth_fail";
	String Serialization::k_DepthStencilBackStencilPass = "back_stencil_pass";
	String Serialization::k_DepthStencilBackStencilFunc = "back_stencil_func";

	String Serialization::k_Name = "name";
	String Serialization::k_Count = "count";
	String Serialization::k_DisplayName = "display";
	String Serialization::k_Value = "value";
	String Serialization::k_Visible = "visible";

}