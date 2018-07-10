#pragma once
/********************************************************************
	created:	2018/07/10
	created:	10:7:2018   8:13
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\sgfRHIDepthStencilState.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface
	file base:	sgfRHIDepthStencilState
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	struct RHIDepthStencilFuncDesc
	{
		ERHIStencilFunc			m_eStendcilFailOper;
		ERHIStencilFunc			m_eStendcilDepthFailOper;
		ERHIStencilFunc			m_eStendcilPassOper;
		ERHIComparisonFunc		m_eStencilFunc;
	};

	struct RHIDepthStencilStateDesc
	{
		int32					m_nDepthEnable;
		int32					m_nDepthWriteMask;
		ERHIComparisonFunc		m_eDepthFunc;
		int32					m_nStencilEnable;
		int32					m_nStencilReadMask;
		int32					m_nStencilWriteMask;
		RHIDepthStencilFuncDesc	m_sFrontFaceFuncDesc;
		RHIDepthStencilFuncDesc	m_sBackFaceFuncDesc;

		RHIDepthStencilStateDesc()
			:m_nDepthEnable(1)
			, m_nDepthWriteMask(1)
			, m_eDepthFunc(ERHIComparisonFunc_Less)
			, m_nStencilEnable(0)
			, m_nStencilReadMask(0xFF)
			, m_nStencilWriteMask(0xff)
		{
			const RHIDepthStencilFuncDesc func = { ERHIStencilFunc_Keep, ERHIStencilFunc_Keep, ERHIStencilFunc_Keep, ERHIComparisonFunc_Always };
			m_sFrontFaceFuncDesc = func;
			m_sBackFaceFuncDesc = func;
		}

		inline bool		operator==(const RHIDepthStencilStateDesc& a_rhs) const
		{
			return memcmp(this, &a_rhs, sizeof(RHIDepthStencilStateDesc)) == 0;
		}
		inline bool		operator!=(const RHIDepthStencilStateDesc& a_rhs) const
		{
			return memcmp(this, &a_rhs, sizeof(RHIDepthStencilStateDesc)) != 0;
		}
	};

	class RHIDepthStencilState : public HardwareResource
	{
	public:
		const RHIDepthStencilStateDesc& GetDesc() const { return m_sDesc; }
	protected:
		RHIDepthStencilStateDesc	m_sDesc;
	};
	typedef TRefCountPtr<RHIDepthStencilState>	RHIDepthStencilStateRef;
}