#pragma once
/********************************************************************
	created:	2018/07/12
	created:	12:7:2018   7:56
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11\sgfRHIShaderDX11.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11
	file base:	sgfRHIShaderDX11
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	class RHIShaderDX11 : public RHIShader
	{
	public:
		RHIShaderDX11(const String& a_szVS, const String& a_szPS, const TArray<RHIShader::Macro>& a_arrMacro);
		virtual ~RHIShaderDX11();

		virtual void Setup(const RHIShaderConstantsRef& a_refCons, const RHIShaderTexturesRef& a_refTexs) override;

		virtual RHIShaderConstantsRef CreateShaderConstants() override;
		virtual RHIShaderTexturesRef CreateShaderTextures() override;

		virtual void OnLostDevice() override;
		virtual void OnResetDevice() override;
	private:
		void	_Initialize(const String& a_szVS, const String& a_szPS, const TArray<RHIShader::Macro>& a_arrMacro);
	};
}