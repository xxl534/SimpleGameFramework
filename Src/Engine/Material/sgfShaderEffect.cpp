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
	{

	}

	ShaderEffectPropDecl::~ShaderEffectPropDecl()
	{

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
	ShaderEffect::ShaderEffect()
	{

	}

	ShaderEffect::~ShaderEffect()
	{

	}

	const String& ShaderEffect::GetFileName() const
	{

	}

	const String& ShaderEffect::GetDisplayName() const
	{

	}

	bool ShaderEffect::GetVisible() const
	{

	}

	int32 ShaderEffect::GetPropertyDeclCount() const
	{

	}

	const ShaderEffectPropDecl* ShaderEffect::GetPropertyDecl(int32 a_nIdx) const
	{

	}

	const ShaderEffectPropDecl* ShaderEffect::GetPropertyDecl(const String& a_szName) const
	{

	}

	int32 ShaderEffect::GetTextureDeclCount() const
	{

	}

	const ShaderEffectTexDecl* ShaderEffect::GetTextureDecl(int32 a_nIdx) const
	{

	}

	const ShaderEffectTexDecl* ShaderEffect::GetTextureDecl(const String& a_szName) const
	{

	}

	int32 ShaderEffect::GetPassCount() const
	{

	}

	ShaderPass* ShaderEffect::GetPass(int32 a_nIdx)
	{

	}

	ShaderEffect* ShaderEffect::LoadFromFile(const String& a_szName)
	{

	}

	void ShaderEffect::Cleanup()
	{

	}

	bool ShaderEffect::_Load(const String& a_szName)
	{

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

	}

}