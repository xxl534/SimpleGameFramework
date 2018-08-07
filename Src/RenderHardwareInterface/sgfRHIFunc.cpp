#include"sgfRHIPCH.h"
#include "sgfRHIFunc.h"

namespace sgf
{
	_RHIGetShaderConstantDecl	RHIGetShaderConstantDecl = NULL;
	_RHIGetShaderConstantValue	RHIGetShaderConstantValue = NULL;
	_RHISetShaderConstantValue	RHISetShaderConstantValue = NULL;

	_RHIGetShaderFloat4			RHIGetShaderFloat4 = NULL;
	_RHISetShaderFloat4			RHISetShaderFloat4 = NULL;
	_RHISetShaderFloat4Array	RHISetShaderFloat4Array = NULL;
	_RHIGetShaderFloat3			RHIGetShaderFloat3 = NULL;
	_RHISetShaderFloat3			RHISetShaderFloat3 = NULL;
	_RHISetShaderFloat3Array	RHISetShaderFloat3Array = NULL;
	_RHIGetShaderFloat2			RHIGetShaderFloat2 = NULL;
	_RHISetShaderFloat2			RHISetShaderFloat2 = NULL;
	_RHISetShaderFloat2Array	RHISetShaderFloat2Array = NULL;
	_RHIGetShaderFloat			RHIGetShaderFloat = NULL;
	_RHISetShaderFloat			RHISetShaderFloat = NULL;
	_RHISetShaderFloatArray		RHISetShaderFloatArray = NULL;

	_RHIGetShaderInt4			RHIGetShaderInt4 = NULL;
	_RHISetShaderInt4			RHISetShaderInt4 = NULL;
	_RHIGetShaderInt3			RHIGetShaderInt3 = NULL;
	_RHISetShaderInt3			RHISetShaderInt3 = NULL;
	_RHIGetShaderInt2			RHIGetShaderInt2 = NULL;
	_RHISetShaderInt2			RHISetShaderInt2 = NULL;
	_RHIGetShaderInt			RHIGetShaderInt = NULL;
	_RHISetShaderInt			RHISetShaderInt = NULL;

	_RHIGetShaderBool4			RHIGetShaderBool4 = NULL;
	_RHISetShaderBool4			RHISetShaderBool4 = NULL;
	_RHIGetShaderBool3			RHIGetShaderBool3 = NULL;
	_RHISetShaderBool3			RHISetShaderBool3 = NULL;
	_RHIGetShaderBool2			RHIGetShaderBool2 = NULL;
	_RHISetShaderBool2			RHISetShaderBool2 = NULL;
	_RHIGetShaderBool			RHIGetShaderBool = NULL;
	_RHISetShaderBool			RHISetShaderBool = NULL;

	_RHIGetShaderMatrix			RHIGetShaderMatrix = NULL;
	_RHISetShaderMatrix			RHISetShaderMatrix = NULL;
	_RHIGetShaderMatrixArray	RHIGetShaderMatrixArray = NULL;
	_RHISetShaderMatrixArray	RHISetShaderMatrixArray = NULL;

	_RHISetViewport				RHISetViewport = NULL;
	_RHIClear					RHIClear = NULL;

	_RHICreateVertexInput		RHICreateVertexInput = NULL;
	_RHISetVertexInput			RHISetVertexInput = NULL;

	_RHICreateVertexBuffer		RHICreateVertexBuffer = NULL;
	_RHISetVertexBuffer			RHISetVertexBuffer = NULL;
	_RHILockVertexBuffer		RHILockVertexBuffer = NULL;
	_RHIUnlockVertexBuffer		RHIUnlockVertexBuffer = NULL;

	_RHICreateIndexBuffer		RHICreateIndexBuffer = NULL;
	_RHISetIndexBuffer			RHISetIndexBuffer = NULL;
	_RHILockIndexBuffer			RHILockIndexBuffer = NULL;
	_RHIUnlockIndexBuffer		RHIUnlockIndexBuffer = NULL;

	_RHICreateTextureFromFile	RHICreateTextureFromFile = NULL;

	_RHICreateRasterizerState	RHICreateRasterizerState = NULL;
	_RHIGetRasterizerState		RHIGetRasterizerState = NULL;
	_RHISetRasterizerState		RHISetRasterizerState = NULL;

	_RHICreateBlendState		RHICreateBlendState = NULL;
	_RHIGetBlendState			RHIGetBlendState = NULL;
	_RHISetBlendState			RHISetBlendState = NULL;

	_RHICreateDepthStencilState	RHICreateDepthStencilState = NULL;
	_RHIGetDepthStencilState	RHIGetDepthStencilState = NULL;
	_RHISetDepthStencilState	RHISetDepthStencilState = NULL;

	_RHICreateEffect			RHICreateEffect = NULL;
}