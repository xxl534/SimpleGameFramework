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
	struct RHIVertextInputElement
	{
		String					SemanticName;
		ERHIShaderConstanceType	Type;
		int8					Stride :8;
		int8					Offset : 8;
		int8					Slot : 8;
		int8					Normalize : 8;
	};

	struct RHIVertextInputDesc
	{
	private:
		TArray<RHIVertextInputElement> m_arrElement;
	};
}