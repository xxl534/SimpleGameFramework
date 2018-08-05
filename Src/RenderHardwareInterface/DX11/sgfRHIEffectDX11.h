#pragma once
/********************************************************************
	created:	2018/07/12
	created:	12:7:2018   7:56
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11\sgfRHIEffectDX11.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11
	file base:	sgfRHIShaderDX11
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/
#include "sgfShaderDX11.h"

namespace sgf
{
	class RHIEffectDX11 : public RHIEffect
	{
		struct AttributeDecl
		{
			String						m_szSemanticName;
			UINT						m_nSemanticIndex;
			ERHIShaderConstantType		m_eType;
		};
	public:
		RHIEffectDX11(const String& a_szVS, const String& a_szPS, const TArray<RHIEffect::Macro>& a_arrMacro);
		virtual ~RHIEffectDX11();

		virtual void Setup(const RHIShaderConstantsRef& a_refCons, const RHIShaderTexturesRef& a_refTexs) override;

		virtual RHIShaderConstantsRef CreateShaderConstants() override;
		virtual RHIShaderTexturesRef CreateShaderTextures() override;
	public:
		static void			Init();
		static void			Tick();
		static void			Exit();
	private:
		void	_Initialize(const String& a_szVS, const String& a_szPS, const TArray<RHIEffect::Macro>& a_arrMacro);
		void	_InitAttribute();
		void	_InitUniform();
		void	_InitShaderUniform(void* a_pShader);
	private:
		ID3D11VertexShader*		m_pVertexShader;
		ID3D11PixelShader*		m_pPixelShader;

		TArray<AttributeDecl>	m_arrAttrDecl;
		TArray<RHIShaderConstantDecl>	m_arrBuildinConstantDecl;
		TArray<RHIShaderConstantDecl>	m_arrBuildinTextureDecl;
		TArray<RHIShaderConstantDecl>	m_arrCustomConstantDecl;
		TArray<RHIShaderConstantDecl>	m_arrCustomTextureDecl;

		ShaderDx11Ref m_refVertexShader;
		ShaderDx11Ref m_refPixelShader;
	};
}