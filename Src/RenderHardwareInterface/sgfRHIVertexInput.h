#pragma once 
/********************************************************************
	created:	2018/06/24
	created:	24:6:2018   7:54
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\sgfRHIVertexInput.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface
	file base:	sgfRHIVertexInput
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	struct RHIVertexInputElement
	{
		String					SemanticName;
		ERHIShaderConstanceType	Type;
		union 
		{
			struct
			{
				int8					Stride : 8;
				int8					Offset : 8;
				int8					Slot : 8;
				int8					Normalize : 8;
			};
			int32						Param;
		};
		

		bool			operator==(const RHIVertexInputElement& a_rhs) const;
		bool			operator!=(const RHIVertexInputElement& a_rhs) const;
	};

	bool 
		RHIVertexInputElement::operator==(const RHIVertexInputElement& a_rhs) const
	{
		return SemanticName == a_rhs.SemanticName && Type == a_rhs.Type && Param == a_rhs.Param;
	}

	bool 
		RHIVertexInputElement::operator!=(const RHIVertexInputElement& a_rhs) const
	{
		return !((*this) == a_rhs);
	}

	struct RHIVertexInputDesc
	{
		TArray<RHIVertexInputElement> m_arrElement;

		bool			operator==(const RHIVertexInputDesc& a_rhs) const;
		bool			operator!=(const RHIVertexInputDesc& a_rhs) const;
	};

	bool RHIVertexInputDesc::operator==(const RHIVertexInputDesc& a_rhs) const
	{
		return m_arrElement == a_rhs.m_arrElement;
	}

	bool RHIVertexInputDesc::operator!=(const RHIVertexInputDesc& a_rhs) const
	{
		return !(*this == a_rhs);
	}

	class RHIVertexInput :public HardwareResource
	{
	public:
		const RHIVertexInputDesc&		GetDesc() const { return m_sDesc; }
	protected:
							RHIVertexInput( const RHIVertexInputDesc& a_sDesc):m_sDesc( a_sDesc ){}
							RHIVertexInput&		operator=(const RHIVertexInput& a_rhs) { return *this;  }
	protected:
		RHIVertexInputDesc	m_sDesc;
	};

	typedef TRefCountPtr<RHIVertexInput> RHIVertexInputRef;

}