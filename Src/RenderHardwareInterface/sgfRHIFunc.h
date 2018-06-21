#pragma once
/********************************************************************
	created:	2018/06/21
	created:	21:6:2018   7:10
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\sgfRHIFunc.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface
	file base:	sgfRHIFunc
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	typedef void(*_RHISetViewport)(const RHIViewportDesc& a_desc);
	typedef void(*_RHIClear)(bool a_bCleanColor, const ColorByte4& a_col, bool a_bCleanDepth, float a_fDepth, bool a_bCleanStencil, uint32 a_uStencil);

	extern _RHISetViewport			RHISetViewport;
	extern _RHIClear				RHIClear;
}