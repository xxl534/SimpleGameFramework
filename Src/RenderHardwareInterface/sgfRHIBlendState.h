#pragma once
/********************************************************************
	created:	2018/07/10
	created:	10:7:2018   7:56
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\sgfRHIBlendState.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface
	file base:	sgfRHIBlendState
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	struct RHIRenderTargetBlendDesc
	{
		int32				m_nBlendEnable;
		ERHIBlend			m_eSrcBlend;
		ERHIBlend			m_eDstBlend;
		ERHIBlendFunc		m_eBlendOper;
		ERHIBlend			m_eSrcAlphaBlend;
		ERHIBlend			m_eDstAlphaBlend;
		ERHIBlendFunc		m_eAlphaBlendOper;
		int32				m_nRenderTargetWriteMask;
	};

#define RHI_BLEND_TARGET_COUNT_MAX 8
	struct RHIBlendStateDesc
	{
		int32						m_nAlphaToCoverageEnable;
		int32						m_nIndependentBlendEnable;
		RHIRenderTargetBlendDesc	m_arrRenderTarget[RHI_BLEND_TARGET_COUNT_MAX];
		
		RHIBlendStateDesc()
		{
			memset(this, 0, sizeof(RHIBlendStateDesc));
		}

		inline bool	operator==(const RHIBlendStateDesc& a_rhs ) const
		{
			return memcmp(this, &a_rhs, sizeof(RHIBlendStateDesc)) == 0;
		}
		inline bool	operator!=(const RHIBlendStateDesc& a_rhs) const
		{
			return memcmp(this, &a_rhs, sizeof(RHIBlendStateDesc)) != 0;
		}
	};

	class RHIBlendState : public HardwareResource
	{
	public:
		const RHIBlendStateDesc&	GetDesc() const { return m_sDesc; }
	protected:
		RHIBlendStateDesc			m_sDesc;
	};
	typedef TRefCountPtr<RHIBlendState>	RHIBlendStateRef;
}