#pragma once
/********************************************************************
	created:	2018/07/10
	created:	10:7:2018   7:26
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\sgfRHIShaderConstant.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface
	file base:	sgfRHIShaderConstant
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	class RHIShaderConstantDecl
	{
	public:
		String					m_szName;
		int32					m_nHandle;		//dx11ÖÐÎªÆ«ÒÆÁ¿
		ERHIShaderConstantType	m_eType;
		int32					m_nStride;
		int32					m_nCount;
	};

	class RHIShaderConstants : public HardwareResource
	{
	public:
		virtual int32							Count() = 0;
		virtual const RHIShaderConstantDecl*	GetConstantDecl(int32 a_nIdx) const = 0;
		virtual const RHIShaderConstantDecl*	GetConstantDecl(const String& a_szName) const = 0;
		virtual void							SetContantValue(int32 a_nidx, const void* a_pData, int32 a_nStride, int32 a_nCount) = 0;

		virtual void							InitConstantMap(const TArray<RHIShaderConstantDecl*> a_arrDecl, const TArray<void*> a_arrValue);
		//skeleton palette
		//light map
		//light info
	};
	typedef TRefCountPtr<RHIShaderConstants> RHIShaderConstantsRef;
}