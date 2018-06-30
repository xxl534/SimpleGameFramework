#pragma once
/********************************************************************
	created:	2018/06/29
	created:	29:6:2018   7:20
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11\sgfRHIVertexInputDX11.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11
	file base:	sgfRHIVertexInputDX11
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	class RHIVertexInputDX11 : public RHIVertexInput
	{
	public:
		RHIVertexInputDX11(const RHIVertexInputDesc& a_desc);

		virtual void		OnLostDevice();
		virtual void		OnResetDevice();

		static void			Init();
		static void			Exit();
		static void			Tick();
	};
	extern RHIVertexInputDX11* DX11_gVertexInput;
}