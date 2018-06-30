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
	typedef void					(*_RHISetViewport)(const RHIViewportDesc& a_desc);
	typedef void					(*_RHIClear)(bool a_bCleanColor, const ColorByte4& a_col, bool a_bCleanDepth, float a_fDepth, bool a_bCleanStencil, uint32 a_uStencil);

	typedef RHIVertexInputRef		(*_RHICreateVertexInput)(const RHIVertexInputDesc& a_desc);
	typedef void					(*_RHISetVertexInput)(const RHIVertexInputRef& a_ref);

	typedef RHIVertexBufferRef		(*_RHICreateVertexBuffer)(int32 a_nStride, int32 a_nVertexCount, void* a_pSrc, ERHIResourceUsage a_eUsage);
	typedef void					(*_RHISetVertexBuffer)(const RHIVertexBufferRef& a_refBuffer, int32 a_nSlot);
	typedef void*					(*_RHILockVertexBuffer)(RHIVertexBufferRef& a_refBuffer, int32 a_nOffset, int32 a_nSize, bool a_bReadOnly);
	typedef void					(*_RHIUnlockVertexBuffer)(RHIVertexBufferRef& a_refBuffer);

	typedef RHIIndexBufferRef		(*_RHICreateIndexBuffer)(int32 a_nCount, void* a_pData, ERHIResourceUsage a_eUsage);
	typedef void					(*_RHISetIndexBuffer)( const RHIIndexBufferRef& a_ref );
	typedef void*					(*_RHILockIndexBuffer)(RHIIndexBufferRef& a_ref, int32 a_nOffset, int32 a_nSize, bool a_bReadonly);
	typedef void					(*_RHIUnlockIndexBuffer)(RHIIndexBufferRef& a_ref);

	extern _RHISetViewport				RHISetViewport;
	extern _RHIClear					RHIClear;

	extern _RHICreateVertexInput		RHICreateVertexInput;
	extern _RHISetVertexInput			RHISetVertexInput;

	extern _RHICreateVertexBuffer		RHICreateVertexBuffer;
	extern _RHISetVertexBuffer			RHISetVertexBuffer;
	extern _RHILockVertexBuffer			RHILockVertexBuffer;
	extern _RHIUnlockVertexBuffer		RHIUnlockVertexBuffer;

	extern _RHICreateIndexBuffer		RHICreateIndexBuffer;
	extern _RHISetIndexBuffer			RHISetIndexBuffer;
	extern _RHILockIndexBuffer			RHILockIndexBuffer;
	extern _RHIUnlockIndexBuffer		RHIUnlockIndexBuffer;
	
}