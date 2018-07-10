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

		_LoadRasterizerState(a_pNode->first_node( Serialization::k_Rasterizer.c_str() );
		_LoadBlendState(a_pNode->first_node( Serialization::k_Blend.c_str());
		_LoadDepthStencilState(a_pNode->first_node( Serialization::k_DepthStencil.c_str());

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

	}

	//-------------------------------------------------------------------------
	void 
		ShaderPass::_LoadDepthStencilState(rapidxml::xml_node<char>* a_pNode)
	{

	}

	//-------------------------------------------------------------------------
	void 
		ShaderPass::_LoadTechs(rapidxml::xml_node<char>* a_pNode)
	{

	}

}