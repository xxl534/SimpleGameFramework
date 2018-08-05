#pragma once
/*************************************
	created: 2018/08/05 11:23 
	filename:	G:\Visual Studio 2015\SimpleGameFrame\Src\RenderHardwareInterface\DX11\sgfShaderDX11.h
	file path:	G:\Visual Studio 2015\SimpleGameFrame\Src\RenderHardwareInterface\DX11
	file base:	sgfRHIShaderDX11
	file ext:	h	
	author: 	Xiexuelong
	
	purpose:
*************************************/

namespace sgf
{
	class ShaderDX11 : public HardwareResource
	{
	protected:
		struct AttributeDecl
		{
			String						m_szSemanticName;
			UINT						m_nSemanticIndex;
			ERHIShaderConstantType		m_eType;
		};
	public:
		ShaderDX11();
		virtual ~ShaderDX11();
	public:
		static String GetUniqueName(const String& a_szFile, const TArray<RHIEffect::Macro>& a_arrMacro);
	protected:
		void	_InitAttribute(ID3D11ShaderReflection* a_pReflection);
		void	_InitUniform(ID3D11ShaderReflection* a_pReflection);
	protected:
		static TArray<D3D_SHADER_MACRO, false, false> _ToDx11Marco(const TArray<RHIEffect::Macro>& a_arrMacro);
	protected:
		TArray<AttributeDecl>	m_arrAttrDecl;
	};

	typedef TRefCountPtr<ShaderDX11> ShaderDx11Ref;
}