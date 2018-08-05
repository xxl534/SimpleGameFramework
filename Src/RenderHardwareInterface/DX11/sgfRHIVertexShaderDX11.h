#pragma once
/*************************************
	created: 2018/08/05 10:52 
	filename:	G:\Visual Studio 2015\SimpleGameFrame\Src\RenderHardwareInterface\DX11\sgfRHIVertexShaderDX11.h
	file path:	G:\Visual Studio 2015\SimpleGameFrame\Src\RenderHardwareInterface\DX11
	file base:	sgfRHIVertexShaderDX11
	file ext:	h	
	author: 	Xiexuelong
	
	purpose:
*************************************/

namespace sgf
{
	class RHIVertexShaderDX11
	{
		struct AttributeDecl
		{
			String						m_szSemanticName;
			UINT						m_nSemanticIndex;
			ERHIShaderConstantType		m_eType;
		};
	public:
		RHIVertexShaderDX11(const String& a_szVS, const TArray<RHIEffect::Macro>& a_arrMacro);
		virtual ~RHIVertexShaderDX11();

		virtual void Setup(const RHIShaderConstantsRef& a_refCons, const RHIShaderTexturesRef& a_refTexs);

	private:
		void	_Initialize(const String& a_szFile, const TArray<RHIEffect::Macro>& a_arrMacro);
		void	_InitAttribute(ID3D11ShaderReflection* a_pReflection);
		void	_InitUniform(ID3D11ShaderReflection* a_pReflection);

		TArray<D3D_SHADER_MACRO, false, false> _ToDx11Marco(const TArray<RHIEffect::Macro>& a_arrMacro);
	private:
		ID3D11VertexShader*		m_pShader;
		TArray<AttributeDecl>	m_arrAttrDecl;
	};
}