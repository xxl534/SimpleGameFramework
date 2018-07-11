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
}