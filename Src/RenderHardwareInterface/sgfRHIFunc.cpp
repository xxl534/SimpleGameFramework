#include"sgfRHIPCH.h"
#include "sgfRHIFunc.h"

namespace sgf
{
	_RHISetViewport		RHISetViewport = NULL;
	_RHIClear			RHIClear = NULL;

	_RHICreateVertexInput	RHICreateVertexInput = NULL;
	_RHISetVertexInput		RHISetVertexInput = NULL;
}