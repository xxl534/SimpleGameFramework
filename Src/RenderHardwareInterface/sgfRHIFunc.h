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

	//vertex input
	typedef RHIVertexInputRef		(*_RHICreateVertexInput)(const RHIVertexInputDesc& a_desc);
	typedef void					(*_RHISetVertexInput)(const RHIVertexInputRef& a_ref);

	//vertex buffer
	typedef RHIVertexBufferRef		(*_RHICreateVertexBuffer)(int32 a_nStride, int32 a_nVertexCount, void* a_pSrc, ERHIResourceUsage a_eUsage);
	typedef void					(*_RHISetVertexBuffer)(const RHIVertexBufferRef& a_refBuffer, int32 a_nSlot);
	typedef void*					(*_RHILockVertexBuffer)(RHIVertexBufferRef& a_refBuffer, int32 a_nOffset, int32 a_nSize, bool a_bReadOnly);
	typedef void					(*_RHIUnlockVertexBuffer)(RHIVertexBufferRef& a_refBuffer);

	//index buffer
	typedef RHIIndexBufferRef		(*_RHICreateIndexBuffer)(int32 a_nCount, void* a_pData, ERHIResourceUsage a_eUsage);
	typedef void					(*_RHISetIndexBuffer)( const RHIIndexBufferRef& a_ref );
	typedef void*					(*_RHILockIndexBuffer)(RHIIndexBufferRef& a_ref, int32 a_nOffset, int32 a_nSize, bool a_bReadonly);
	typedef void					(*_RHIUnlockIndexBuffer)(RHIIndexBufferRef& a_ref);

	//texture
	typedef RHITextureRef			(*_RHICreateTextureFromFile)(const String& a_szFile, ERHIResourceUsage a_eUsage, ERHIPixelFormat a_eFormat, int32 a_nMipMap );

	//rasterizer state 
	typedef RHIRasterizerStateRef	(*_RHICreateRasterizerState)(const RHIRasterizerStateDesc& a_sDesc);
	typedef RHIRasterizerStateRef	(*_RHIGetRasterizerState)();
	typedef void					(*_RHISetRasterizerState)(const RHIRasterizerStateRef& a_refState);

	//blend state
	typedef RHIBlendStateRef		(*_RHICreateBlendState)(const RHIBlendStateDesc& a_sDesc);
	typedef RHIBlendStateRef		(*_RHIGetBlendState)();
	typedef void					(*_RHISetBlendState)(const RHIBlendStateRef& a_refBlend);

	//depth stencil state
	typedef RHIDepthStencilStateRef	(*_RHICreateDepthStencilState)(const RHIDepthStencilStateDesc& a_sDesc);
	typedef RHIDepthStencilStateRef	(*_RHIGetDepthStencilState)();
	typedef void					(*_RHISetDepthStencilState)(const RHIDepthStencilStateRef& a_refState);

	//shader
	typedef RHIShaderRef			(*_RHICreateShader)(const String& a_szVS, const String& a_szPS, const TArray<RHIShader::Macro>& a_arrMacro);

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

	extern _RHICreateTextureFromFile	RHICreateTextureFromFile;

	extern _RHICreateRasterizerState	RHICreateRasterizerState;
	extern _RHIGetRasterizerState		RHIGetRasterizerState;
	extern _RHISetRasterizerState		RHISetRasterizerState;

	extern _RHICreateBlendState			RHICreateBlendState;
	extern _RHIGetBlendState			RHIGetBlendState;
	extern _RHISetBlendState			RHISetBlendState;

	extern _RHICreateDepthStencilState	RHICreateDepthStencilState;
	extern _RHIGetDepthStencilState		RHIGetDepthStencilState;
	extern _RHISetDepthStencilState		RHISetDepthStencilState;

	extern _RHICreateShader				RHICreateShader;
}