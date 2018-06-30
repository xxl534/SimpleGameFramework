#pragma once
/********************************************************************
	created:	2018/06/30
	created:	30:6:2018   7:36
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11\sgfRHIVertexBufferDX11.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11
	file base:	sgfRHIVertexBufferDX11
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	class RHIVertexBufferDX11 : public RHIVertexBuffer
	{
	public:
		RHIVertexBufferDX11();
		virtual ~RHIVertexBufferDX11();

		static void			Init();
		static void			Exit();
		static void			Tick();
	};

	extern ID3D11Buffer*	DX11_arrHardwareVertexBuffer[];
}