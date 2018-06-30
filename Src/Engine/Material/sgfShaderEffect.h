#pragma once
/********************************************************************
	created:	2018/06/30
	created:	30:6:2018   15:55
	filename: 	E:\SimpleGameFramework\Src\Engine\Material\sgfShaderEffect.h
	file path:	E:\SimpleGameFramework\Src\Engine\Material
	file base:	sgfShaderEffect
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/
namespace sgf
{
	class ShaderEffectPropDecl
	{
		friend class ShaderEffect;
	public:
		int32						m_nIndex;
		String						m_szName;
		String						m_szDisplay;
		ERHIShaderConstantType		m_eType;
		int32						m_nStride;
		int32						m_nCount;
		void*						m_pDefaultValue;
	private:
		ShaderEffectPropDecl();
		~ShaderEffectPropDecl();
	};

	class ShaderEffectTexDecl
	{
		friend class ShaderEffect;
	public:
		String						m_szName;
		String						m_szDisplay;
		ERHIShaderConstantType		m_eType;
		ERHISamplerFilter			m_eFilter;
		ERHIClampMode				m_eClampU;
		ERHIClampMode				m_eClampV;
		ERHIClampMode				m_eClampW;

	private:
		ShaderEffectTexDecl();
		~ShaderEffectTexDecl();
	};

	class ShaderPass;
	class ShaderEffect
	{
	public:
		const String&				GetFileName() const;
		const String&				GetDisplayName() const;
		bool						GetVisible() const;

		int32						GetPropertyDeclCount() const;
		const ShaderEffectPropDecl*	GetPropertyDecl(int32 a_nIdx) const;
		const ShaderEffectPropDecl*	GetPropertyDecl(const String& a_szName) const;

		int32						GetTextureDeclCount() const;
		const ShaderEffectTexDecl*	GetTextureDecl(int32 a_nIdx) const;
		const ShaderEffectTexDecl*	GetTextureDecl(const String& a_szName) const;

		int32						GetPassCount() const;
		ShaderPass*					GetPass(int32 a_nIdx);
	public:
		static ShaderEffect*		LoadFromFile(const String& a_szName);
		static void					Cleanup();
	protected:
		ShaderEffect();
		~ShaderEffect();

		bool						_Load(const String& a_szName);
		void						_LoadPropDecl(rapidxml::xml_node<char>* a_pNode);
		void						_LoadTexDecl(rapidxml::xml_node<char>* a_pNode);
		void						_LoadPass(rapidxml::xml_node<char>* a_pNode);
		void						_LoadEffectInfo(rapidxml::xml_node<char>* a_pNode);

		static bool					_LoadPropData(ShaderEffectPropDecl* a_pDecl, const char* a_szData);

	private:
		String						m_szFileName;
		String						m_szDisplayName;
		bool						m_bVisible;

		TArray<ShaderEffectPropDecl*>	m_arrShaderPropDecl;
		TArray<ShaderEffectTexDecl*>	m_arrShaderTexDecl;
		TArray<ShaderPass*>				m_arrShaderPass;
	};
}