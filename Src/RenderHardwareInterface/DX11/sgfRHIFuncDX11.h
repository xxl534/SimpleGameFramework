#pragma once
/********************************************************************
	created:	2018/06/21
	created:	21:6:2018   7:15
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11\sgfRHIFuncDX11.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11
	file base:	sgfRHIFuncDX11
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	extern void						InitializeRHIFunc();
	extern void						RHISetViewportDX11(const RHIViewportDesc& a_desc);
}