#include "sgfEnginePCH.h"
#include "sgfShaderPass.h"

namespace sgf
{
	ShaderPass::ShaderPass()
	{

	}

	//-------------------------------------------------------------------------
	ShaderPass::~ShaderPass()
	{

	}

	//-------------------------------------------------------------------------
	void 
		ShaderPass::_LoadFromXml(rapidxml::xml_node<char>* a_pNode)
	{
		GetXmlAttribute(a_pNode, Serialization::k_ShaderEffectQueue.c_str(), m_nRenderQueue);

		_LoadRasterizerState(a_pNode->first_node(Serialization::k_Rasterizer.c_str()));
		_LoadBlendState(a_pNode->first_node(Serialization::k_Blend.c_str()));
		_LoadDepthStencilState(a_pNode->first_node(Serialization::k_DepthStencil.c_str()));

		String szDeviceName = RHIDevice::Get()->GetName();
		_LoadTechs(a_pNode->first_node( szDeviceName.c_str()));
	}

	//-------------------------------------------------------------------------
	TArray<RHIShader::Macro> 
		ShaderPass::_LoadTechMacros(rapidxml::xml_node<char>* a_pNode, const String& a_szTech)
	{
		TArray<RHIShader::Macro> arrMacro;
		rapidxml::xml_node<char>* pTechNode = a_pNode->first_node(a_szTech.c_str());
		if (pTechNode)
		{
			rapidxml::xml_attribute<char>* pAttr = pTechNode->first_attribute();
			while (pAttr)
			{
				RHIShader::Macro macro = { pAttr->name(), pAttr->value() };
				arrMacro.push_back(macro);
				pAttr = pAttr->next_attribute();
			}
		}
		return arrMacro;
	}

	//-------------------------------------------------------------------------
	void 
		ShaderPass::_LoadRasterizerState(rapidxml::xml_node<char>* a_pNode)
	{
		if (a_pNode)
		{
			RHIRasterizerStateDesc sDesc;
			sDesc.m_eFillMode = RHIStringToFillMode(GetXmlAttributeValue(a_pNode, Serialization::k_RasterizerFillMode.c_str()), sDesc.m_eFillMode);
			sDesc.m_eCullMode = RHIStringToCullMode(GetXmlAttributeValue(a_pNode, Serialization::k_RasterizerCullMode.c_str()), sDesc.m_eCullMode);
			GetXmlAttribute(a_pNode, Serialization::k_RasterizerFront.c_str(), sDesc.m_nFrontCounterClockwise);
			GetXmlAttribute(a_pNode, Serialization::k_RasterizerDepthBias.c_str(), sDesc.m_nDepthBias);
			GetXmlAttribute(a_pNode, Serialization::k_RasterizerDepthBiasClamp.c_str(), sDesc.m_fDepthBiasClamp);
			GetXmlAttribute(a_pNode, Serialization::k_RasterizerSlopeScaleDepthBias.c_str(), sDesc.m_fSlopeScaleDepthBias);
			GetXmlAttribute(a_pNode, Serialization::k_RasterizerDepthClipEnable.c_str(), sDesc.m_nDepthClipEnable);
			GetXmlAttribute(a_pNode, Serialization::k_RasterizerScissor.c_str(), sDesc.m_nScissorEnable);
			GetXmlAttribute(a_pNode, Serialization::k_RasterizerMultiSample.c_str(), sDesc.m_nMultisampleEnable);
			GetXmlAttribute(a_pNode, Serialization::k_RasterizerAntialiasedLine.c_str(), sDesc.m_nAntialiasedLineEnable);
			m_refRasterizerState = RHICreateRasterizerState(sDesc);
		}
	}

	//-------------------------------------------------------------------------
	void 
		ShaderPass::_LoadBlendState(rapidxml::xml_node<char>* a_pNode)
	{
		if (a_pNode)
		{
			RHIBlendStateDesc sDesc;
			GetXmlAttribute(a_pNode, Serialization::k_BlendAlphaToCoverage.c_str(), sDesc.m_nAlphaToCoverageEnable);
			GetXmlAttribute(a_pNode, Serialization::k_BlendIndependent.c_str(), sDesc.m_nIndependentBlendEnable);
			if (sDesc.m_nIndependentBlendEnable)
			{
				_LoadBlendTarget(a_pNode, sDesc.m_arrRenderTarget[0]);
			}
			else
			{
				int32 i = 0;
				rapidxml::xml_node<char>* pTargetNode = a_pNode->first_node(Serialization::k_BlendTarget.c_str());
				while (pTargetNode && i < RHI_BLEND_TARGET_COUNT_MAX)
				{
					_LoadBlendTarget(pTargetNode, sDesc.m_arrRenderTarget[i]);
					++i;
					pTargetNode = pTargetNode->next_sibling(Serialization::k_BlendTarget.c_str());
				}
			}
			m_refBlendState = RHICreateBlendState(sDesc);
		}
	}

	//-------------------------------------------------------------------------
	void 
		ShaderPass::_LoadBlendTarget(rapidxml::xml_node<char>* a_pNode, RHIRenderTargetBlendDesc& a_sDesc)
	{
		GetXmlAttribute(a_pNode, Serialization::k_BlendEnable.c_str(), a_sDesc.m_nBlendEnable);
		a_sDesc.m_eSrcBlend = RHIStringToBlend(GetXmlAttributeValue(a_pNode, Serialization::k_BlendSrcColor.c_str()), a_sDesc.m_eSrcBlend);
		a_sDesc.m_eDstBlend = RHIStringToBlend(GetXmlAttributeValue(a_pNode, Serialization::k_BlendDstColor.c_str()), a_sDesc.m_eDstBlend);
		a_sDesc.m_eBlendOper = RHIStringToBlendFunc(GetXmlAttributeValue(a_pNode, Serialization::k_BlendColorFunc.c_str()), a_sDesc.m_eBlendOper);
		a_sDesc.m_eSrcAlphaBlend = RHIStringToBlend(GetXmlAttributeValue(a_pNode, Serialization::k_BlendSrcAlpha.c_str()), a_sDesc.m_eSrcAlphaBlend);
		a_sDesc.m_eDstAlphaBlend = RHIStringToBlend(GetXmlAttributeValue(a_pNode, Serialization::k_BlendDstAlpha.c_str()), a_sDesc.m_eDstAlphaBlend);
		a_sDesc.m_eAlphaBlendOper = RHIStringToBlendFunc(GetXmlAttributeValue(a_pNode, Serialization::k_BlendAlphaFunc.c_str()), a_sDesc.m_eAlphaBlendOper);

		int32 wr, wg, wb, wa;
		wr = wg = wb = wa = 1;
		GetXmlAttribute(a_pNode, Serialization::k_BlendWriteR.c_str(), wr);
		GetXmlAttribute(a_pNode, Serialization::k_BlendWriteG.c_str(), wg);
		GetXmlAttribute(a_pNode, Serialization::k_BlendWriteB.c_str(), wb);
		GetXmlAttribute(a_pNode, Serialization::k_BlendWriteA.c_str(), wa);

		a_sDesc.m_nRenderTargetWriteMask = wr * ERHIColorWriteEnable_Red + wg * ERHIColorWriteEnable_Green + wb * ERHIColorWriteEnable_Blue + wa * ERHIColorWriteEnable_Alpha;
	}

	//-------------------------------------------------------------------------
	void 
		ShaderPass::_LoadDepthStencilState(rapidxml::xml_node<char>* a_pNode)
	{
		if( a_pNode )
		{
			RHIDepthStencilStateDesc sDesc;
			GetXmlAttribute(a_pNode, Serialization::k_DepthStencilDepthEnable.c_str(), sDesc.m_nDepthEnable);
			GetXmlAttribute(a_pNode, Serialization::k_DepthStencilDepthWriteMask.c_str(), sDesc.m_nDepthWriteMask);
			GetXmlAttribute(a_pNode, Serialization::k_DepthStencilStencilEnable.c_str(), sDesc.m_nStencilEnable);
			GetXmlAttribute(a_pNode, Serialization::k_DepthStencilStencilReadMask.c_str(), sDesc.m_nStencilReadMask);
			GetXmlAttribute(a_pNode, Serialization::k_DepthStencilStencilWriteMask.c_str(), sDesc.m_nStencilWriteMask);
			sDesc.m_eDepthFunc = RHIStringToComparisonFunc(GetXmlAttributeValue(a_pNode, Serialization::k_DepthStencilDepthFunc.c_str()), sDesc.m_eDepthFunc);

			sDesc.m_sFrontFaceFuncDesc.m_eStendcilFailOper = RHIStringToStencilFunc(GetXmlAttributeValue(a_pNode, Serialization::k_DepthStencilFrontStencilFail.c_str()), sDesc.m_sFrontFaceFuncDesc.m_eStendcilFailOper);
			sDesc.m_sFrontFaceFuncDesc.m_eStendcilDepthFailOper = RHIStringToStencilFunc(GetXmlAttributeValue(a_pNode, Serialization::k_DepthStencilFrontStencilDepthFail.c_str()), sDesc.m_sFrontFaceFuncDesc.m_eStendcilDepthFailOper);
			sDesc.m_sFrontFaceFuncDesc.m_eStendcilPassOper = RHIStringToStencilFunc(GetXmlAttributeValue(a_pNode, Serialization::k_DepthStencilFrontStencilPass.c_str()), sDesc.m_sFrontFaceFuncDesc.m_eStendcilPassOper);
			sDesc.m_sFrontFaceFuncDesc.m_eStencilFunc = RHIStringToComparisonFunc(GetXmlAttributeValue(a_pNode, Serialization::k_DepthStencilFrontStencilFunc.c_str()), sDesc.m_sFrontFaceFuncDesc.m_eStencilFunc);

			sDesc.m_sBackFaceFuncDesc.m_eStendcilFailOper = RHIStringToStencilFunc(GetXmlAttributeValue(a_pNode, Serialization::k_DepthStencilBackStencilFail.c_str()), sDesc.m_sBackFaceFuncDesc.m_eStendcilFailOper);
			sDesc.m_sBackFaceFuncDesc.m_eStendcilDepthFailOper = RHIStringToStencilFunc(GetXmlAttributeValue(a_pNode, Serialization::k_DepthStencilBackStencilDepthFail.c_str()), sDesc.m_sBackFaceFuncDesc.m_eStendcilDepthFailOper);
			sDesc.m_sBackFaceFuncDesc.m_eStendcilPassOper = RHIStringToStencilFunc(GetXmlAttributeValue(a_pNode, Serialization::k_DepthStencilBackStencilPass.c_str()), sDesc.m_sBackFaceFuncDesc.m_eStendcilPassOper);
			sDesc.m_sBackFaceFuncDesc.m_eStencilFunc = RHIStringToComparisonFunc(GetXmlAttributeValue(a_pNode, Serialization::k_DepthStencilBackStencilFunc.c_str()), sDesc.m_sBackFaceFuncDesc.m_eStencilFunc);

			m_refIDepthStencilState = RHICreateDepthStencilState(sDesc);
		}
	}

	//-------------------------------------------------------------------------
	void 
		ShaderPass::_LoadTechs(rapidxml::xml_node<char>* a_pNode)
	{
		if (a_pNode)
		{
			TArray<RHIShader::Macro> arrDefaultMacro = _LoadTechMacros(a_pNode, Serialization::k_ShaderEffectTechDefault);
			TArray<RHIShader::Macro> arrFogMacro = _LoadTechMacros(a_pNode, Serialization::k_ShaderEffectTechFog);
			TArray<RHIShader::Macro> arrSkinningMacro = _LoadTechMacros(a_pNode, Serialization::k_ShaderEffectTechSkinning);
			TArray<RHIShader::Macro> arrLightmapMacro = _LoadTechMacros(a_pNode, Serialization::k_ShaderEffectTechLightmap);

			m_arrShaderTech.clear();
			m_arrShaderTech.resize(ETech_Count);
			rapidxml::xml_node<char>* pShaderNode = a_pNode->first_node(Serialization::k_ShaderEffectShader.c_str());
			if (pShaderNode)
			{
				for (int32 i = 0; i < ETech_Count; ++i)
				{
					TArray<RHIShader::Macro>	arrMacro = arrDefaultMacro;
					if (i & ETech_Skinning) { arrMacro.insert(arrMacro.end(), arrSkinningMacro); }
					if (i & ETech_Fog) { arrMacro.insert(arrMacro.end(), arrFogMacro); }
					if (i & ETech_LightMap) { arrMacro.insert(arrMacro.end(), arrLightmapMacro); }

					RHIShaderRef refShader = RHICreateShader(
						GetXmlAttributeValue(pShaderNode, Serialization::k_ShaderEffectVS.c_str()),
						GetXmlAttributeValue(pShaderNode, Serialization::k_ShaderEffectPS.c_str()),
						arrMacro);
					m_arrShaderTech[i] = refShader;
				}
			}
		}
	}

}