#include "sgfCorePCH.h"
#include "sgfXmlHelper.h"

namespace sgf
{
	//-------------------------------------------------------------------------
	rapidxml::xml_node<char>*
		AllocateXmlNode(rapidxml::xml_node<char>* a_pParent, const char* a_szName)
	{
		rapidxml::xml_node<char>* pNewNode = a_pParent->document()->allocate_node(rapidxml::node_element, a_szName);
		a_pParent->append_node(pNewNode);
		return pNewNode;
	}

	//------------------------------------------------------------------------
	const char*
		GetXmlAttributeValue(rapidxml::xml_node<char>* a_pEle, const char* a_szName)
	{
		if (a_pEle)
		{
			rapidxml::xml_attribute<char>* pAttr = a_pEle->first_attribute(a_szName);
			return pAttr ? pAttr->value() : NULL;
		}
		return NULL;
	}
}