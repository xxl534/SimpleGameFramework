#pragma once
/********************************************************************
	created:	2018/07/11
	created:	11:7:2018   19:36
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11\sgfRHIRasterizerStateDX11.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11
	file base:	sgfRHIRasterizerStateDX11
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	class RHIRasterizerStateDX11 : public RHIRasterizerState
	{
	public:
		RHIRasterizerStateDX11(const RHIRasterizerStateDesc& a_sDesc);
		virtual	~RHIRasterizerStateDX11();

		void Setup();

		static void			Init();
		static void			Exit();
		static void			Tick();
	private:
		ID3D11RasterizerState* m_pDX11State;
	};
}