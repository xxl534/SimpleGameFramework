#pragma once
/********************************************************************
	created:	2018/07/27
	created:	27:7:2018   8:43
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11\sgfRHIBlendStateDX11.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11
	file base:	sgfRHIBlendStateDX11
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	class RHIBlendStateDX11 : public RHIBlendState
	{
	public:
		RHIBlendStateDX11(const RHIBlendStateDesc& a_sDesc);
		virtual ~RHIBlendStateDX11();

		void			Setup();

		static void		Init();
		static void		Exit();
		static void		Tick();
	private:
		ID3D11BlendState*	m_pBlendState;
	};
}