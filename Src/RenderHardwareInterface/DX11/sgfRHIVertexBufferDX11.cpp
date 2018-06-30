#include "sgfRHIPCH.h"
#include "sgfRHIDX11Private.h"
#include "sgfRHIVertexBufferDX11.h"

namespace sgf
{
#define DX11_MAX_VERTEX_SLOT 16
	ID3D11Buffer*	DX11_arrHardwareVertexBuffer[DX11_MAX_VERTEX_SLOT] = { NULL };

	//-------------------------------------------------------------------------
	static void 
		_ReleaseHWBuffer(RHIVertexBufferDX11* a_pVertexBuffer)
	{
		ID3D11Buffer* pBuffer = (ID3D11Buffer*)a_pVertexBuffer->m_pHWData;
		SAFE_RELEASE(pBuffer);
		a_pVertexBuffer->m_pHWData = NULL;
	}

	//-------------------------------------------------------------------------
	static void
		_RegainHWBuffer(RHIVertexBufferDX11* a_pVertexBuffer)
	{
		_ReleaseHWBuffer(a_pVertexBuffer);
		if (a_pVertexBuffer->m_eUsage == ERHIResourceUsage_Static)
		{
			D3D11_BUFFER_DESC desc;
			desc.Usage = D3D11_USAGE_IMMUTABLE;
			desc.ByteWidth = a_pVertexBuffer->m_nStride * a_pVertexBuffer->m_nVertexCount;
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA sInitData;
			sInitData.pSysMem = a_pVertexBuffer->m_pMemData;
			ID3D11Buffer* pD3D11Buffer;

			HR(DX11_pDevice->CreateBuffer(&desc, &sInitData, &pD3D11Buffer));
			a_pVertexBuffer->m_pHWData = pD3D11Buffer;
		}
	}

	//-------------------------------------------------------------------------
	RHIVertexBufferDX11::RHIVertexBufferDX11()
	{

	}

	//-------------------------------------------------------------------------
	RHIVertexBufferDX11::~RHIVertexBufferDX11()
	{
		_ReleaseHWBuffer( this );
		SAFE_FREE(m_pMemData);
	}

	//-------------------------------------------------------------------------
	void RHIVertexBufferDX11::Init()
	{
		for (int32 i = 0; i < DX11_MAX_VERTEX_SLOT; ++i)
		{
			DX11_arrHardwareVertexBuffer[i] = NULL;
		}
	}

	//-------------------------------------------------------------------------
	void RHIVertexBufferDX11::Exit()
	{
		for (int32 i = 0; i < DX11_MAX_VERTEX_SLOT; ++i)
		{
			DX11_arrHardwareVertexBuffer[i] = NULL;
		}
	}

	//-------------------------------------------------------------------------
	void RHIVertexBufferDX11::Tick()
	{
		for (int32 i = 0; i < DX11_MAX_VERTEX_SLOT; ++i)
		{
			DX11_arrHardwareVertexBuffer[i] = NULL;
		}
	}
	
	//-------------------------------------------------------------------------
	RHIVertexBufferRef 
		RHICreateVertexBufferDX11(int32 a_nStride, int32 a_nVertexCount, void* a_pSrc, ERHIResourceUsage a_eUsage)
	{
		RHIVertexBufferDX11* pVertexBuffer = new RHIVertexBufferDX11();
		pVertexBuffer->m_nStride = a_nStride;
		pVertexBuffer->m_nVertexCount = a_nVertexCount;
		pVertexBuffer->m_pHWData = NULL;
		int32 nDataSize = a_nStride * a_nVertexCount;
		pVertexBuffer->m_pMemData = malloc(nDataSize);
		pVertexBuffer->m_bLocked = false;
		pVertexBuffer->m_eUsage = a_eUsage;
		if (a_pSrc)
		{
			memcpy(pVertexBuffer->m_pMemData, a_pSrc, nDataSize);
		}
		else
		{
			memset(pVertexBuffer->m_pMemData, 0, nDataSize);
		}

		_RegainHWBuffer(pVertexBuffer);
		return pVertexBuffer;
	}

	//-------------------------------------------------------------------------
	void RHISetVertexBufferDX11(const RHIVertexBufferRef& a_refBuffer, int32 a_nSlot)
	{
		ASSERT(a_nSlot >= 0 && a_nSlot < DX11_MAX_VERTEX_SLOT);
		if (a_refBuffer.IsValidRef())
		{
			DX11_arrHardwareVertexBuffer[a_nSlot] = (ID3D11Buffer*)(a_refBuffer->m_pHWData);
		}
		else
		{
			DX11_arrHardwareVertexBuffer[a_nSlot] = NULL;
		}
	}

	//-------------------------------------------------------------------------
	void* 
		RHILockVertexBufferDX11(RHIVertexBufferRef& a_refBuffer, int32 a_nOffset, int32 a_nSize, bool a_bReadOnly)
	{
		if (!a_refBuffer->m_bLocked)
		{
			a_refBuffer->m_bLocked = true;
			a_refBuffer->m_bLockedReadonly = a_bReadOnly;
			return ((uint8*)a_refBuffer->m_pMemData) + a_nOffset * a_refBuffer->m_nStride;
		}
		return NULL;
	}

	//-------------------------------------------------------------------------
	void
		RHIUnlockVertexBufferDX11(RHIVertexBufferRef& a_refBuffer)
	{
		if (a_refBuffer->m_bLocked)
		{
			a_refBuffer->m_bLocked = false;
			if (a_refBuffer->m_bLockedReadonly == false && a_refBuffer->m_eUsage == ERHIResourceUsage_Static)
			{
				_RegainHWBuffer( a_refBuffer.GetReference<RHIVertexBufferDX11>() );
			}
		}
	}
}