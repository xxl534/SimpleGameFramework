#pragma once
/********************************************************************
	created:	2018/06/29
	created:	29:6:2018   9:21
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\sgfRHIVertexBuffer.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface
	file base:	sgfRHIVertexBuffer
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	struct RHIVertexBuffer : public HardwareResource
	{
		int32			m_nStride;
		int32			m_nVertexCount;
		void*			m_pHWData;
		void*			m_pMemData;
		bool			m_bLocked;
		bool			m_bLockedReadonly;
		ERHIResourceUsage	m_eUsage;

		RHIVertexBuffer()
			:m_nStride(0)
			, m_nVertexCount(0)
			, m_pHWData(NULL)
			, m_pMemData(NULL)
			, m_bLocked(false)
			, m_bLockedReadonly(true)
		{

		}

	};

	typedef TRefCountPtr<RHIVertexBuffer>		RHIVertexBufferRef;
}