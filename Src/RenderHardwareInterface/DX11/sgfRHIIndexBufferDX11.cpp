#include "sgfRHIPCH.h"
#include "sgfRHIDX11Private.h"
#include "sgfRHIIndexBufferDX11.h"

namespace sgf
{
	ID3D11Buffer* DX11_pHardwareIndexBuffer = NULL;
	//-------------------------------------------------------------------------
	static void 
		_ReleaseHWBuffer(RHIIndexBufferDX11* a_pIndexBuffer)
	{
		ID3D11Buffer* pBuffer = (ID3D11Buffer*)a_pIndexBuffer->m_pHWData;
		SAFE_RELEASE(pBuffer);
		a_pIndexBuffer->m_pHWData = NULL;
	}

	//-------------------------------------------------------------------------
	static void
		_RegainHWBuffer(RHIIndexBufferDX11* a_pIndexBuffer)
	{
		_ReleaseHWBuffer(a_pIndexBuffer);
		if (a_pIndexBuffer->m_eUsage == ERHIResourceUsage_Static)
		{
			D3D11_BUFFER_DESC desc;
			desc.Usage = D3D11_USAGE_IMMUTABLE;
			desc.ByteWidth = sizeof(uint32) * a_pIndexBuffer->m_nCount;
			desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA sInitData;
			sInitData.pSysMem = a_pIndexBuffer->m_pMemData;
			ID3D11Buffer* pD3D11Buffer;

			HR(DX11_pDevice->CreateBuffer(&desc, &sInitData, &pD3D11Buffer));
			a_pIndexBuffer->m_pHWData = pD3D11Buffer;
		}
	}

	//-------------------------------------------------------------------------
	RHIIndexBufferDX11::RHIIndexBufferDX11()
	{

	}

	//-------------------------------------------------------------------------
	RHIIndexBufferDX11::~RHIIndexBufferDX11()
	{
		_ReleaseHWBuffer(this);
		SAFE_FREE(m_pMemData);
	}

	//-------------------------------------------------------------------------
	void 
		RHIIndexBufferDX11::Init()
	{
		DX11_pHardwareIndexBuffer = NULL;
	}

	//-------------------------------------------------------------------------
	void 
		RHIIndexBufferDX11::Exit()
	{
		DX11_pHardwareIndexBuffer = NULL;
	}

	//-------------------------------------------------------------------------
	void 
		RHIIndexBufferDX11::Tick()
	{
		DX11_pHardwareIndexBuffer = NULL;
	}

	//-------------------------------------------------------------------------
	RHIIndexBufferRef RHICreateIndexBufferDX11(int32 a_nCount, void* a_pData, ERHIResourceUsage a_eUsage)
	{
		RHIIndexBufferDX11* pIndexBuffer = new RHIIndexBufferDX11();
		pIndexBuffer->m_nCount = a_nCount;
		pIndexBuffer->m_pHWData = NULL;
		pIndexBuffer->m_pMemData = malloc(sizeof(uint32) * a_nCount);
		pIndexBuffer->m_bLocked = false;
		pIndexBuffer->m_eUsage = a_eUsage;
		if (a_pData)
		{
			memcpy(pIndexBuffer->m_pMemData, a_pData, sizeof(uint32)* a_nCount);
		}
		else
		{
			memset(pIndexBuffer->m_pMemData, 0, sizeof(uint32)* a_nCount);
		}

		_RegainHWBuffer(pIndexBuffer);
		return pIndexBuffer;
	}

	//-------------------------------------------------------------------------
	void 
		RHISetIndexBufferDX11(const RHIIndexBufferRef& a_ref)
	{
		if (a_ref.IsValidRef())
		{
			DX11_pHardwareIndexBuffer = (ID3D11Buffer*)a_ref->m_pHWData;
		}
		else
		{
			DX11_pHardwareIndexBuffer = NULL;
		}
	}

	//-------------------------------------------------------------------------
	void*
		RHILockIndexBufferDX11(RHIIndexBufferRef& a_ref, int32 a_nOffset, int32 a_nSize, bool a_bReadonly)
	{
		if (!a_ref->m_bLocked)
		{
			a_ref->m_bLocked = true;
			a_ref->m_bLockedReadonly = a_bReadonly;
			return (uint32*)(a_ref->m_pMemData) + a_nOffset;
		}
		return NULL;
	}

	//-------------------------------------------------------------------------
	void 
		RHIUnlockIndexBufferDX11(RHIIndexBufferRef& a_ref)
	{
		if (a_ref->m_bLocked)
		{
			if (!a_ref->m_bLockedReadonly && a_ref->m_eUsage == ERHIResourceUsage_Static)
			{
				_RegainHWBuffer(a_ref.GetReference<RHIIndexBufferDX11>());
			}
			a_ref->m_bLocked = false;
		}
	}

}