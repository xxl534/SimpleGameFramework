#pragma once
/********************************************************************
	created:	2018/07/10
	created:	10:7:2018   7:42
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\sgfRHIRasterizerState.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface
	file base:	sgfRHIRasterizerState
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	struct RHIRasterizerStateDesc
	{
		ERHIFillMode	m_eFillMode;
		ERHICullMode	m_eCullMode;
		int32			m_nFrontCounterClockwise;
		int32			m_nDepthBias;
		float			m_fDepthBiasClamp;
		float			m_fSlopeScaleDepthBias;
		int32			m_nDepthClipEnable;
		int32			m_nScissorEnable;
		int32			m_nMultisampleEnable;
		int32			m_nAntialiasedLineEnable;

		inline RHIRasterizerStateDesc()
			:m_eFillMode(ERHIFillMode_Solid)
			,m_eCullMode(ERHICullMode_Back)
			,m_nFrontCounterClockwise(1)
			,m_nDepthBias(0)
			,m_fDepthBiasClamp(0)
			,m_fSlopeScaleDepthBias(0)
			,m_nDepthClipEnable(1)
			,m_nScissorEnable(0)
			,m_nMultisampleEnable(0)
			,m_nAntialiasedLineEnable(0)
		{

		}

		
		inline bool			operator==(const RHIRasterizerStateDesc& a_rhs) const
		{
			return memcmp(this, &a_rhs, sizeof(RHIRasterizerStateDesc)) == 0;
		}
		bool			operator!=(const RHIRasterizerStateDesc& a_rhs) const
		{
			return memcmp(this, &a_rhs, sizeof(RHIRasterizerStateDesc)) != 0;
		}
	};

	class RHIRasterizerState : public HardwareResource
	{
	public:
		inline const RHIRasterizerStateDesc&	GetDesc() const { return m_sDesc; }
	protected:
		RHIRasterizerStateDesc			m_sDesc;
	};
	typedef TRefCountPtr<RHIRasterizerState>	RHIRasterizerStateRef;
}