#pragma once
/********************************************************************
	created:	2018/06/30
	created:	30:6:2018   7:16
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\sgfRHIIndexBuffer.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface
	file base:	sgfRHIIndexBuffer
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	struct RHIIndexBuffer : public HardwareResource
	{
		int			m_nCount;
		void*		m_pHWData;
		void*		m_pMemData;
		bool		m_bLocked;
		bool		m_bLockedReadonly;
		ERHIResourceUsage	m_eUsage;

		RHIIndexBuffer()
			:m_nCount(0)
			,m_pHWData(NULL)
			,m_pMemData(NULL)
			,m_bLocked(false)
			,m_bLockedReadonly(false)
		{
		}

		virtual void OnResetDevice() {}
		virtual void OnLostDevice() {}
	};

	typedef	TRefCountPtr<RHIIndexBuffer> RHIIndexBufferRef;
}