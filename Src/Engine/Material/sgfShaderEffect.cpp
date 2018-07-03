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
			SAFE_FREE(m_arrShaderPropDecl[i]);
		}
		m_arrShaderPropDecl.clear();
		for (int32 i = 0; i < m_arrShaderPass.size(); ++i)
		{
			SAFE_FREE(m_arrShaderPropDecl[i]);
		}
		m_arrShaderPropDecl.clear();
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
		//todo fileReader
	}

	void ShaderEffect::_LoadPropDecl(rapidxml::xml_node<char>* a_pNode)
	{

	}

	void ShaderEffect::_LoadTexDecl(rapidxml::xml_node<char>* a_pNode)
	{

	}

	void ShaderEffect::_LoadPass(rapidxml::xml_node<char>* a_pNode)
	{

	}

	void ShaderEffect::_LoadEffectInfo(rapidxml::xml_node<char>* a_pNode)
	{

	}

	bool ShaderEffect::_LoadPropData(ShaderEffectPropDecl* a_pDecl, const char* a_szData)
	{
		//todo serializable 
	}

}