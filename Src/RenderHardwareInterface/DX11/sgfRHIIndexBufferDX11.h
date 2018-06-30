#pragma once
/********************************************************************
	created:	2018/06/30
	created:	30:6:2018   8:48
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11\sgfRHIIndexBufferDX11.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11
	file base:	sgfRHIIndexBufferDX11
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	class RHIIndexBufferDX11 : public RHIIndexBuffer
	{
	public:
		RHIIndexBufferDX11();
		virtual ~RHIIndexBufferDX11();

		static void			Init();
		static void			Exit();
		static void			Tick();
	};

	extern ID3D11Buffer*	DX11_pHardwareIndexBuffer;
}