#pragma once
/*************************************
	created: 2018/08/05 11:36 
	filename:	G:\Visual Studio 2015\SimpleGameFrame\Src\RenderHardwareInterface\DX11\sgfPixelShaderDX11.h
	file path:	G:\Visual Studio 2015\SimpleGameFrame\Src\RenderHardwareInterface\DX11
	file base:	sgfPixelShaderDX11
	file ext:	h	
	author: 	Xiexuelong
	
	purpose:
*************************************/

#include "sgfShaderDX11.h"
namespace sgf
{
	class PixelShaderDX11 : public ShaderDX11
	{
	public:
		PixelShaderDX11(const String& a_szFile, const TArray<RHIEffect::Macro>& a_arrMacro);
		virtual ~PixelShaderDX11();

		virtual void Setup(const RHIShaderConstantsRef& a_refCons, const RHIShaderTexturesRef& a_refTexs);
	public:
		static void	Exit();
	private:
		void	_Initialize(const String& a_szFile, const TArray<RHIEffect::Macro>& a_arrMacro);
	private:
		ID3D11PixelShader* m_pShader;
	};

	extern ShaderDx11Ref CreatePixelShaderDX11(const String& a_szPS, const TArray<RHIEffect::Macro>& a_arrMacro);
}