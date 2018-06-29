#include "sgfRHIPCH.h"
#include "sgfRHIVertexInput.h"

namespace sgf
{ 
	uint32 GetTypeHash(const RHIVertexInputDesc& a_desc)
	{
		uint32 uHash = GetTypeHash(a_desc.m_arrElement.size());
		for (int32 i = 0; i < a_desc.m_arrElement.size(); ++i)
		{
			uHash += GetTypeHash(a_desc.m_arrElement[i].SemanticName) + GetTypeHash(a_desc.m_arrElement[i].Type) + GetTypeHash(a_desc.m_arrElement[i].Param);
		}
		return uHash;
	}
}


