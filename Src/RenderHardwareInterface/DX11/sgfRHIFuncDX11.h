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
	extern void						RHIClearDX11(bool a_bCleanColor, const ColorByte4& a_col, bool a_bCleanDepth, float a_fDepth, bool a_bCleanStencil, uint32 a_uStencil);

	extern RHIVertexInputRef		RHICreateVertexInputDX11(const RHIVertexInputDesc& a_desc);
	extern void						RHISetVertexInputDX11(const RHIVertexInputRef& a_refInput);

	extern RHIVertexBufferRef		RHICreateVertexBufferDX11(int32 a_nStride, int32 a_nVertexCount, void* a_pSrc, ERHIResourceUsage a_eUsage);
	extern void						RHISetVertexBufferDX11(const RHIVertexBufferRef& a_refBuffer, int32 a_nSlot);
	extern void*					RHILockVertexBufferDX11(RHIVertexBufferRef& a_refBuffer, int32 a_nOffset, int32 a_nSize, bool a_bReadOnly);
	extern void						RHIUnlockVertexBufferDX11(RHIVertexBufferRef& a_refBuffer);

	extern RHIIndexBufferRef		RHICreateIndexBufferDX11(int32 a_nCount, void* a_pData, ERHIResourceUsage a_eUsage);
	extern void						RHISetIndexBufferDX11(const RHIIndexBufferRef& a_ref);
	extern void*					RHILockIndexBufferDX11(RHIIndexBufferRef& a_ref, int32 a_nOffset, int32 a_nSize, bool a_bReadonly);
	extern void						RHIUnlockIndexBufferDX11(RHIIndexBufferRef& a_ref);

	extern RHITextureRef			RHICreateTextureFromFileDX11(const String& a_szFile, ERHIResourceUsage a_eUsage, ERHIPixelFormat a_eFormat, int32 a_nMipMap);

	//rasterizer state 
	extern RHIRasterizerStateRef	RHICreateRasterizerStateDX11(const RHIRasterizerStateDesc& a_sDesc);
	extern RHIRasterizerStateRef	RHIGetRasterizerStateDX11();
	extern void						RHISetRasterizerStateDX11(const RHIRasterizerStateRef& a_refState);

	//blend state
	extern RHIBlendStateRef			RHICreateBlendStateDX11(const RHIBlendStateDesc& a_sDesc);
	extern RHIBlendStateRef			RHIGetBlendStateDX11();
	extern void						RHISetBlendStateDX11(const RHIBlendStateRef& a_refBlend);

	//depth stencil state
	extern RHIDepthStencilStateRef	RHICreateDepthStencilStateDX11(const RHIDepthStencilStateDesc& a_sDesc);

	//shader
	extern RHIShaderRef				RHICreateShaderDX11(const String& a_szVS, const String& a_szPS, const TArray<RHIShader::Macro>& a_arrMacro);
}