#pragma once
/********************************************************************
	created:	2018/06/21
	created:	21:6:2018   7:19
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11\sgfRHIDX11Private.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface\DX11
	file base:	sgfRHIDX11Private
	file ext:	h
	author:		Xiexuelong

	purpose:
*********************************************************************/
#include <d3d11.h>
#include <dxgi.h>

#include "sgfRHIDeviceDX11.h"
#include "sgfRHIFuncDX11.h"
#include "sgfRHITypeMapDX11.h"

#if defined(_DEBUG)
	#ifndef HR
	#define HR( x )								\
	{											\
		HRESULT hr = (x);						\
		ASSERT( !FAILED(hr) );					\
	}											
    #endif //HR
#else
	#ifndef HR
	#define HR( x )								
	#endif
#endif