#pragma once
/********************************************************************
	created:	2018/07/30
	created:	30:7:2018   8:40
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11\sgfRHIDepthStencilStateDX11.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11
	file base:	sgfRHIDepthStencilStateDX11
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	class RHIDepthStencilStateDX11 :public RHIDepthStencilState
	{
	public:
		RHIDepthStencilStateDX11(const RHIDepthStencilStateDesc& a_sDesc);
		virtual ~RHIDepthStencilStateDX11();

		void Setup();

		static void			Init();
		static void			Exit();
		static void			Tick();
	private:
		ID3D11DepthStencilState* m_pState;
	};
}