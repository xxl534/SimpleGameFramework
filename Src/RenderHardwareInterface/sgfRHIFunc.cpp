#include"sgfRHIPCH.h"
#include "sgfRHIFunc.h"

namespace sgf
{
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
}