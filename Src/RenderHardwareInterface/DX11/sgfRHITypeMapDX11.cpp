#include "sgfRHIDX11Private.h"
#include "sgfRHITypeMapDX11.h"

namespace sgf
{
	D3D11_FILL_MODE DX11_arrFillMode[ERHIFillMode_Count] =
	{
		D3D11_FILL_WIREFRAME,
		D3D11_FILL_SOLID,
	};

	//-------------------------------------------------------------------------
	D3D11_CULL_MODE DX11_arrCullMode[ERHICullMode_Count] = {
		D3D11_CULL_FRONT,
		D3D11_CULL_BACK,
		D3D11_CULL_NONE,
	};

	//-------------------------------------------------------------------------
	D3D11_BLEND DX11_arrBlend[ERHIBlend_Count] = {
		D3D11_BLEND_ZERO,
		D3D11_BLEND_ONE,
		D3D11_BLEND_SRC_COLOR,
		D3D11_BLEND_INV_SRC_COLOR,
		D3D11_BLEND_SRC_ALPHA,
		D3D11_BLEND_INV_SRC_ALPHA,
		D3D11_BLEND_DEST_ALPHA,
		D3D11_BLEND_INV_DEST_ALPHA,
		D3D11_BLEND_DEST_COLOR,
		D3D11_BLEND_INV_DEST_COLOR,
		D3D11_BLEND_SRC_ALPHA_SAT,
		D3D11_BLEND_BLEND_FACTOR,
		D3D11_BLEND_INV_BLEND_FACTOR,
		D3D11_BLEND_SRC1_COLOR,
		D3D11_BLEND_INV_SRC1_COLOR,
		D3D11_BLEND_SRC1_ALPHA,
		D3D11_BLEND_INV_SRC1_ALPHA
	};

	//-------------------------------------------------------------------------
	D3D11_BLEND_OP DX11_arrBlendFunc[ERHIBlendFunc_Count] = {
		D3D11_BLEND_OP_ADD,
		D3D11_BLEND_OP_SUBTRACT,
		D3D11_BLEND_OP_REV_SUBTRACT,
		D3D11_BLEND_OP_MIN,
		D3D11_BLEND_OP_MAX
	};
}