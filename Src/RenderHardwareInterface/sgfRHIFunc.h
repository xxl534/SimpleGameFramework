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

	//variable
	typedef const float*					(*_RHIGetShaderFloat4)(ERHIShaderFloat4);
	typedef void(*_RHISetShaderFloat4)		(ERHIShaderFloat4, const float*);
	typedef void(*_RHISetShaderFloat4Array)	(ERHIShaderFloat4, const float*, int32);
	typedef const float*					(*_RHIGetShaderFloat3)(ERHIShaderFloat3);
	typedef void(*_RHISetShaderFloat3)		(ERHIShaderFloat3, const float*);
	typedef void(*_RHISetShaderFloat3Array)	(ERHIShaderFloat3, const float*, int32);
	typedef const float*					(*_RHIGetShaderFloat2)(ERHIShaderFloat2);
	typedef void(*_RHISetShaderFloat2)		(ERHIShaderFloat2, const float*);
	typedef void(*_RHISetShaderFloat2Array)	(ERHIShaderFloat2, const float*, int32);
	typedef const float*					(*_RHIGetShaderFloat)(ERHIShaderFloat);
	typedef void(*_RHISetShaderFloat)		(ERHIShaderFloat, const float);
	typedef void(*_RHISetShaderFloatArray)	(ERHIShaderFloat, const float*, int32);

	typedef const int32*					(*_RHIGetShaderInt4)(ERHIShaderInt4);
	typedef void(*_RHISetShaderInt4)		(ERHIShaderInt4, const int32*);
	typedef const int32*					(*_RHIGetShaderInt3)(ERHIShaderInt3);
	typedef void(*_RHISetShaderInt3)		(ERHIShaderInt3, const int32*);
	typedef const int32*					(*_RHIGetShaderInt2)(ERHIShaderInt2);
	typedef void(*_RHISetShaderInt2)		(ERHIShaderInt2, const int32*);
	typedef const int32*					(*_RHIGetShaderInt)(ERHIShaderInt);
	typedef void(*_RHISetShaderInt)			(ERHIShaderInt, const int32);

	typedef const int32*					(*_RHIGetShaderBool4)(ERHIShaderBool4);
	typedef void(*_RHISetShaderBool4)		(ERHIShaderBool4, const int32*);
	typedef const int32*					(*_RHIGetShaderBool3)(ERHIShaderBool3);
	typedef void(*_RHISetShaderBool3)		(ERHIShaderBool3, const int32*);
	typedef const int32*					(*_RHIGetShaderBool2)(ERHIShaderBool2);
	typedef void(*_RHISetShaderBool2)		(ERHIShaderBool2, const int32*);
	typedef const int32*					(*_RHIGetShaderBool)(ERHIShaderBool);
	typedef void(*_RHISetShaderBool)		(ERHIShaderBool, const int32);

	typedef const Matrix&					(*_RHIGetShaderMatrix)(ERHIShaderMatrix);
	typedef void(*_RHISetShaderMatrix)		(ERHIShaderMatrix, const Matrix&);
	typedef const Matrix*					(*_RHIGetShaderMatrixArray)(ERHIShaderMatrix, int32*);
	typedef void(*_RHISetShaderMatrixArray)	(ERHIShaderMatrix, const Matrix*, int32);

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
	typedef RHIEffectRef			(*_RHICreateEffect)(const String& a_szVS, const String& a_szPS, const TArray<RHIEffect::Macro>& a_arrMacro);

	extern _RHISetViewport				RHISetViewport;
	extern _RHIClear					RHIClear;

	extern _RHIGetShaderFloat4			RHIGetShaderFloat4;
	extern _RHISetShaderFloat4			RHISetShaderFloat4;
	extern _RHISetShaderFloat4Array		RHISetShaderFloat4Array;
	extern _RHIGetShaderFloat3			RHIGetShaderFloat3;
	extern _RHISetShaderFloat3			RHISetShaderFloat3;
	extern _RHISetShaderFloat3Array		RHISetShaderFloat3Array;
	extern _RHIGetShaderFloat2			RHIGetShaderFloat2;
	extern _RHISetShaderFloat2			RHISetShaderFloat2;
	extern _RHISetShaderFloat2Array		RHISetShaderFloat2Array;
	extern _RHIGetShaderFloat			RHIGetShaderFloat;
	extern _RHISetShaderFloat			RHISetShaderFloat;
	extern _RHISetShaderFloatArray		RHISetShaderFloatArray;

	extern _RHIGetShaderInt4			RHIGetShaderInt4;
	extern _RHISetShaderInt4			RHISetShaderInt4;
	extern _RHIGetShaderInt3			RHIGetShaderInt3;
	extern _RHISetShaderInt3			RHISetShaderInt3;
	extern _RHIGetShaderInt2			RHIGetShaderInt2;
	extern _RHISetShaderInt2			RHISetShaderInt2;
	extern _RHIGetShaderInt				RHIGetShaderInt;
	extern _RHISetShaderInt				RHISetShaderInt;

	extern _RHIGetShaderBool4			RHIGetShaderBool4;
	extern _RHISetShaderBool4			RHISetShaderBool4;
	extern _RHIGetShaderBool3			RHIGetShaderBool3;
	extern _RHISetShaderBool3			RHISetShaderBool3;
	extern _RHIGetShaderBool2			RHIGetShaderBool2;
	extern _RHISetShaderBool2			RHISetShaderBool2;
	extern _RHIGetShaderBool			RHIGetShaderBool;
	extern _RHISetShaderBool			RHISetShaderBool;

	extern _RHIGetShaderMatrix			RHIGetShaderMatrix;
	extern _RHISetShaderMatrix			RHISetShaderMatrix;

	extern _RHIGetShaderMatrixArray		RHIGetShaderMatrixArray;
	extern _RHISetShaderMatrixArray		RHISetShaderMatrixArray;

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

	extern _RHICreateEffect				RHICreateEffect;
}