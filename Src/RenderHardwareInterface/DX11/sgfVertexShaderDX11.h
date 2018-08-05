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
#include "sgfShaderDX11.h"

namespace sgf
{
	class VertexShaderDX11 : public ShaderDX11
	{
	public:
		VertexShaderDX11(const String& a_szVS, const TArray<RHIEffect::Macro>& a_arrMacro);
		virtual ~VertexShaderDX11();

		virtual void Setup(const RHIShaderConstantsRef& a_refCons, const RHIShaderTexturesRef& a_refTexs);
	public:
		static void	Exit();
	private:
		void	_Initialize(const String& a_szFile, const TArray<RHIEffect::Macro>& a_arrMacro);
	private:
		ID3D11VertexShader*		m_pShader;
	};

	extern ShaderDx11Ref CreateVertexShaderDX11(const String& a_szVS, const TArray<RHIEffect::Macro>& a_arrMacro);
}