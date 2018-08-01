#include "sgfEnginePCH.h"
#include "sgfShaderEffect.h"
#include "sgfShaderPass.h"

namespace sgf
{
	//-------------------------------------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//ShaderEffectPropDecl
	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------
	ShaderEffectPropDecl::ShaderEffectPropDecl()
		:m_eType(ERHIShaderConstantType_Invalid)
		, m_nStride(0)
		, m_nCount(1)
		, m_pDefaultValue(NULL)
	{

	}

	//-------------------------------------------------------------------------
	ShaderEffectPropDecl::~ShaderEffectPropDecl()
	{
		SAFE_FREE(m_pDefaultValue);
	}

	//-------------------------------------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//ShaderEffectTexDecl
	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------
	ShaderEffectTexDecl::ShaderEffectTexDecl()
	{

	}

	ShaderEffectTexDecl::~ShaderEffectTexDecl()
	{

	}

	//-------------------------------------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//ShaderEffect
	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------
	THashMap<String, ShaderEffect*>	fs_mapShaderEffect;
	//-------------------------------------------------------------------------
	ShaderEffect::ShaderEffect()
	{

	}

	//-------------------------------------------------------------------------
	ShaderEffect::~ShaderEffect()
	{
		for (int32 i = 0; i < m_arrShaderPropDecl.size(); ++i)
		{
			SAFE_FREE(m_arrShaderPropDecl[i]);
		}
		m_arrShaderPropDecl.clear();
		for (int32 i = 0; i < m_arrShaderTexDecl.size(); ++i)
		{
			SAFE_FREE(m_arrShaderTexDecl[i]);
		}
		m_arrShaderTexDecl.clear();
		for (int32 i = 0; i < m_arrShaderPass.size(); ++i)
		{
			SAFE_FREE(m_arrShaderPass[i]);
		}
		m_arrShaderPass.clear();
	}

	//-------------------------------------------------------------------------
	const String& 
		ShaderEffect::GetFileName() const
	{
		return m_szFileName;
	}

	//-------------------------------------------------------------------------
	const String& 
		ShaderEffect::GetDisplayName() const
	{
		return m_szDisplayName;
	}

	//-------------------------------------------------------------------------
	bool 
		ShaderEffect::GetVisible() const
	{
		return m_bVisible;
	}

	//-------------------------------------------------------------------------
	int32 
		ShaderEffect::GetPropertyDeclCount() const
	{
		return m_arrShaderPropDecl.size();
	}

	//-------------------------------------------------------------------------
	const ShaderEffectPropDecl* 
		ShaderEffect::GetPropertyDecl(int32 a_nIdx) const
	{
		return m_arrShaderPropDecl[a_nIdx];
	}

	//-------------------------------------------------------------------------
	const ShaderEffectPropDecl* 
		ShaderEffect::GetPropertyDecl(const String& a_szName) const
	{
		for (int32 i = 0; i < m_arrShaderPropDecl.size(); ++i)
		{
			if (m_arrShaderPropDecl[i]->m_szName == a_szName)
			{
				return m_arrShaderPropDecl[i];
			}
		}
		return NULL;
	}

	//-------------------------------------------------------------------------
	int32 
		ShaderEffect::GetTextureDeclCount() const
	{
		return m_arrShaderTexDecl.size();
	}

	//-------------------------------------------------------------------------
	const ShaderEffectTexDecl* 
		ShaderEffect::GetTextureDecl(int32 a_nIdx) const
	{
		return m_arrShaderTexDecl[a_nIdx];
	}

	//-------------------------------------------------------------------------
	const ShaderEffectTexDecl* 
		ShaderEffect::GetTextureDecl(const String& a_szName) const
	{
		for (int32 i = 0; i < m_arrShaderTexDecl.size(); ++i)
		{
			if (m_arrShaderTexDecl[i]->m_szName == a_szName)
			{
				return m_arrShaderTexDecl[i];
			}
		}
		return NULL;
	}

	//-------------------------------------------------------------------------
	int32 
		ShaderEffect::GetPassCount() const
	{
		return m_arrShaderPass.size();
	}

	//-------------------------------------------------------------------------
	ShaderPass* 
		ShaderEffect::GetPass(int32 a_nIdx)
	{
		return m_arrShaderPass[a_nIdx];
	}

	//-------------------------------------------------------------------------
	ShaderEffect* ShaderEffect::LoadFromFile(const String& a_szName)
	{
		THashMap<String, ShaderEffect*>::iterator it = fs_mapShaderEffect.find(a_szName);
		if (it != fs_mapShaderEffect.end())
		{
			return it->second;
		}

		ShaderEffect* pEffect = new ShaderEffect();
		if (pEffect->_Load(a_szName))
		{
			fs_mapShaderEffect[a_szName] = pEffect;
		}
		else
		{
			SAFE_DELETE(pEffect);
		}
		return pEffect;
	}

	//-------------------------------------------------------------------------
	void 
		ShaderEffect::Cleanup()
	{
		for (THashMap<String, ShaderEffect*>::iterator it = fs_mapShaderEffect.begin(); it != fs_mapShaderEffect.end(); ++it)
		{
			SAFE_DELETE(it->second);
		}
		fs_mapShaderEffect.clear();
	}

	//-------------------------------------------------------------------------
	bool ShaderEffect::_Load(const String& a_szName)
	{
		DataReader* pReader = FileReader::OpenReadFile(a_szName);
		bool bRet = false;
		if (pReader)
		{
			rapidxml::xml_document<char> doc;
			doc.parse<0>((char*)pReader->Data());
			rapidxml::xml_node<char>* pEffectNode = doc.first_node( Serialization::k_ShaderEffect.c_str() );
			if (pEffectNode)
			{
				GetXmlAttribute(pEffectNode, Serialization::k_DisplayName.c_str(), m_szDisplayName);

				_LoadPropDecl(pEffectNode);
				_LoadTexDecl(pEffectNode);
				_LoadPass(pEffectNode);
				_LoadEffectInfo(pEffectNode);
				bRet = true;
			}
			else
			{
				bRet = false;
			}
		}
		SAFE_DELETE(pReader);
		return bRet;
	}

	//-------------------------------------------------------------------------
	void 
		ShaderEffect::_LoadPropDecl(rapidxml::xml_node<char>* a_pNode)
	{
		rapidxml::xml_node<char>* pPropNode = a_pNode->first_node(Serialization::k_ShaderEffectProp.c_str());
		while (pPropNode)
		{
			ShaderEffectPropDecl* pPropDecl = new ShaderEffectPropDecl();
			GetXmlAttribute(pPropNode, Serialization::k_Name.c_str(), pPropDecl->m_szName);
			GetXmlAttribute(pPropNode, Serialization::k_DisplayName.c_str(), pPropDecl->m_szDisplay);
			GetXmlAttribute(pPropNode, Serialization::k_Count.c_str(), pPropDecl->m_nCount);
			pPropDecl->m_eType = RHIStringToShaderConstantType(GetXmlAttributeValue(pPropNode, Serialization::k_ShaderEffectType.c_str()));

			if (!pPropDecl->m_szName.empty() &&
				pPropDecl->m_eType != ERHIShaderConstantType_Invalid &&
				pPropDecl->m_nCount > 0 &&
				_LoadPropData(pPropDecl, GetXmlAttributeValue(pPropNode, Serialization::k_Value.c_str()))
				)
			{
				if (pPropDecl->m_szDisplay.empty())
				{
					pPropDecl->m_szDisplay = pPropDecl->m_szName;
				}
				pPropDecl->m_nIndex = m_arrShaderPropDecl.size();
				m_arrShaderPropDecl.push_back(pPropDecl);
			}
			else
			{
				SAFE_DELETE(pPropDecl);
			}
			pPropNode = pPropNode->next_sibling(Serialization::k_ShaderEffectProp.c_str());
		}
	}

	//-------------------------------------------------------------------------
	void 
		ShaderEffect::_LoadTexDecl(rapidxml::xml_node<char>* a_pNode)
	{
		rapidxml::xml_node<char>* pTexNode = a_pNode->first_node(Serialization::k_ShaderEffectTexture.c_str());
		while (pTexNode)
		{
			ShaderEffectTexDecl* pDecl = new ShaderEffectTexDecl();
			GetXmlAttribute(pTexNode, Serialization::k_Name.c_str(), pDecl->m_szName);
			GetXmlAttribute(pTexNode, Serialization::k_DisplayName.c_str(), pDecl->m_szDisplay);
			pDecl->m_eType = RHIStringToShaderConstantType(GetXmlAttributeValue(pTexNode, Serialization::k_ShaderEffectType.c_str()));
			if (!pDecl->m_szName.empty() &&
				(	pDecl->m_eType == ERHIShaderConstantType_Sampler2D ||
					pDecl->m_eType == ERHIShaderConstantType_Sampler3D ||
					pDecl->m_eType == ERHIShaderConstantType_SamplerCube )
				)
			{
				pDecl->m_eClampU = RHIStringToClampMode(GetXmlAttributeValue(pTexNode, Serialization::k_ShaderEffectClampU.c_str()), ERHIClampMode_Clamp);
				pDecl->m_eClampV = RHIStringToClampMode(GetXmlAttributeValue(pTexNode, Serialization::k_ShaderEffectClampV.c_str()), ERHIClampMode_Clamp);
				pDecl->m_eClampW = RHIStringToClampMode(GetXmlAttributeValue(pTexNode, Serialization::k_ShaderEffectClampW.c_str()), ERHIClampMode_Clamp);

				pDecl->m_eFilter = RHIStringToSamplerFilter(GetXmlAttributeValue(pTexNode, Serialization::k_ShaderEffectFilter.c_str()), ERHISamplerFilter_Min_Mag_Mip_Linear);
				if (pDecl->m_szDisplay.empty())
				{
					pDecl->m_szDisplay = pDecl->m_szName;
				}
				m_arrShaderTexDecl.push_back(pDecl);
			}
			else
			{
				SAFE_DELETE(pDecl);
			}
			pTexNode = pTexNode->next_sibling(Serialization::k_ShaderEffectTexture.c_str());
		}
	}

	//-------------------------------------------------------------------------
	void 
		ShaderEffect::_LoadPass(rapidxml::xml_node<char>* a_pNode)
	{
		rapidxml::xml_node<char>* pDeviceNode = NULL;
		rapidxml::xml_node<char>* pPassNode = a_pNode->first_node(Serialization::k_ShaderEffectPass.c_str());
		while (pPassNode)
		{
			ShaderPass* pPass = new ShaderPass();
			pPass->_LoadFromXml(pPassNode);
			m_arrShaderPass.push_back(pPass);

			pPassNode = pPassNode->next_sibling(Serialization::k_ShaderEffectPass.c_str());
		}
	}

	//-------------------------------------------------------------------------
	void 
		ShaderEffect::_LoadEffectInfo(rapidxml::xml_node<char>* a_pNode)
	{
		bool bSucc = false;
		bSucc = GetXmlAttribute(a_pNode, Serialization::k_Visible.c_str(), m_bVisible);
		ASSERT(bSucc);
	}

	//-------------------------------------------------------------------------
	bool 
		ShaderEffect::_LoadPropData(ShaderEffectPropDecl* a_pDecl, const char* a_szData)
	{
		a_pDecl->m_nStride = RHIGetShaderConstantTypeSize(a_pDecl->m_eType);
		if (a_pDecl->m_nStride > 0)
		{
			SAFE_FREE(a_pDecl->m_pDefaultValue);
			a_pDecl->m_pDefaultValue = malloc(a_pDecl->m_nStride * a_pDecl->m_nCount);
			switch ( a_pDecl->m_eType )
			{
			case ERHIShaderConstantType_1f:		return Serialization::ReadFloatArray(a_szData, (float*)a_pDecl->m_pDefaultValue, a_pDecl->m_nCount);
			case ERHIShaderConstantType_2f:		return Serialization::ReadFloat2Array(a_szData, (float*)a_pDecl->m_pDefaultValue, a_pDecl->m_nCount);
			case ERHIShaderConstantType_3f:		return Serialization::ReadFloat3Array(a_szData, (float*)a_pDecl->m_pDefaultValue, a_pDecl->m_nCount);
			case ERHIShaderConstantType_4f:		return Serialization::ReadFloat4Array(a_szData, (float*)a_pDecl->m_pDefaultValue, a_pDecl->m_nCount);
			case ERHIShaderConstantType_1i:		return Serialization::ReadIntArray(a_szData, (int32*)a_pDecl->m_pDefaultValue, a_pDecl->m_nCount);
			case ERHIShaderConstantType_2i:		return Serialization::ReadIntArray(a_szData, (int32*)a_pDecl->m_pDefaultValue, a_pDecl->m_nCount);
			case ERHIShaderConstantType_3i:		return Serialization::ReadIntArray(a_szData, (int32*)a_pDecl->m_pDefaultValue, a_pDecl->m_nCount);
			case ERHIShaderConstantType_4i:		return Serialization::ReadIntArray(a_szData, (int32*)a_pDecl->m_pDefaultValue, a_pDecl->m_nCount);
			case ERHIShaderConstantType_1b:		return Serialization::ReadIntArray(a_szData, (int32*)a_pDecl->m_pDefaultValue, a_pDecl->m_nCount);
			case ERHIShaderConstantType_2b:		return Serialization::ReadIntArray(a_szData, (int32*)a_pDecl->m_pDefaultValue, a_pDecl->m_nCount);
			case ERHIShaderConstantType_3b:		return Serialization::ReadIntArray(a_szData, (int32*)a_pDecl->m_pDefaultValue, a_pDecl->m_nCount);
			case ERHIShaderConstantType_4b:		return Serialization::ReadIntArray(a_szData, (int32*)a_pDecl->m_pDefaultValue, a_pDecl->m_nCount);
			case ERHIShaderConstantType_Matrix2:		return Serialization::ReadMatrix2Array(a_szData, (float*)a_pDecl->m_pDefaultValue, a_pDecl->m_nCount);
			case ERHIShaderConstantType_Matrix3:		return Serialization::ReadMatrix3Array(a_szData, (float*)a_pDecl->m_pDefaultValue, a_pDecl->m_nCount);
			case ERHIShaderConstantType_Matrix4:		return Serialization::ReadMatrix4Array(a_szData, (float*)a_pDecl->m_pDefaultValue, a_pDecl->m_nCount);
			}
		}
		return false;
	}

}