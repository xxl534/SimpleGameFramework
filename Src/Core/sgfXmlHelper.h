#pragma once
/********************************************************************
	created:	2018/07/05
	created:	5:7:2018   8:28
	filename: 	E:\SimpleGameFramework\Src\Core\sgfXmlHelper.h
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfXmlHelper
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/
#include "xml/rapidxml.hpp"
#include "sgfColor.h"
#include "sgfString.h"
#include "sgfMatrix.h"

namespace sgf
{
	extern rapidxml::xml_node<char>* AllocateXmlNode(rapidxml::xml_node<char>* a_pParent, const char* a_szName);

	extern const char*	GetXmlAttributeValue(rapidxml::xml_node<char>* a_pEle, const char* a_szName);
	//-------------------------------------------------------------------------
	template<typename T> static bool
		GetXmlAttribute(rapidxml::xml_node<char>* a_pEle, const char* a_szName, T& a_prop)
	{
		const char* sz = GetXmlAttributeValue(a_pEle, a_szName);
		if (sz)
		{
			a_prop.FromString(sz);
			return true;
		}
		return false;
	}

	//-------------------------------------------------------------------------
	static bool
		GetXmlAttribute(rapidxml::xml_node<char>* a_pEle, const char* a_szName, String& a_prop)
	{
		const char* szVal = GetXmlAttributeValue(a_pEle, a_szName);
		if (szVal)
		{
			a_prop = szVal;
			return true;
		}
		return false;
	}

	//-------------------------------------------------------------------------
	static bool
		GetXmlAttribute(rapidxml::xml_node<char>* a_pEle, const char* a_szName, int& a_prop)
	{
		const char* szVal = GetXmlAttributeValue(a_pEle, a_szName);
		if (szVal)
		{
			sscanf(szVal, "%d", &a_prop);
			return true;
		}
		return false;
	}

	//-------------------------------------------------------------------------
	static bool
		GetXmlAttribute(rapidxml::xml_node<char>* a_pEle, const char* a_szName, unsigned int& a_prop)
	{
		const char* szVal = GetXmlAttributeValue(a_pEle, a_szName);
		if (szVal)
		{
			sscanf(szVal, "%u", &a_prop);
			return true;
		}
		return false;
	}

	//-------------------------------------------------------------------------
	static bool
		GetXmlAttribute(rapidxml::xml_node<char>* a_pEle, const char* a_szName, float& a_prop)
	{
		const char* szVal = GetXmlAttributeValue(a_pEle, a_szName);
		if (szVal)
		{
			sscanf(szVal, "%f", &a_prop);
			return true;
		}
		return false;
	}

	//-------------------------------------------------------------------------
	static bool
		GetXmlAttribute(rapidxml::xml_node<char>* a_pEle, const char* a_szName, bool& a_prop)
	{
		const char* szVal = GetXmlAttributeValue(a_pEle, a_szName);
		if (szVal)
		{
			int b;
			sscanf(szVal, "%d", &b);
			a_prop = b == 0 ? false : true;
			return true;
		}
		return false;
	}

	//-------------------------------------------------------------------------
	static bool
		GetXmlAttribute(rapidxml::xml_node<char>* a_pEle, const char* a_szName, Color& col)
	{
		const char* szVal = GetXmlAttributeValue(a_pEle, a_szName);
		if (szVal)
		{
			int r, g, b, a;
			sscanf(szVal, "%d,%d,%d,%d", &r, &g, &b, &a);
			col = Color((uint8)r, (uint8)g, (uint8)b, (uint8)a);
			return true;
		}
		return false;
	}

	//------------------------------------------------------------------------
	template<typename T> static void
		SetXmlAttribute(rapidxml::xml_node<char>* a_pEle, const char* a_szName, const T& a_prop)
	{
		rapidxml::xml_document<char>* pDoc = a_pEle->document();
		rapidxml::xml_attribute<char>* pAttr = a_pEle->first_attribute(a_szName);
		if (pAttr)
		{
			pAttr->value(pDoc->allocate_string(a_prop.ToString().c_str()));
			return;
		}
		a_pEle->append_attribute(
			pDoc->allocate_attribute(
				pDoc->allocate_string(a_szName),
				pDoc->allocate_string(a_prop.ToString().c_str())
			)
		);
	}

	//-------------------------------------------------------------------------
	static void
		SetXmlAttribute(rapidxml::xml_node<char>* a_pEle, const char* a_szName, const char* a_prop)
	{
		rapidxml::xml_document<char>* pDoc = a_pEle->document();
		rapidxml::xml_attribute<char>* pAttr = a_pEle->first_attribute(a_szName);
		if (pAttr)
		{
			pAttr->value(pDoc->allocate_string(a_prop));
			return;
		}
		a_pEle->append_attribute(
			pDoc->allocate_attribute(
				pDoc->allocate_string(a_szName),
				pDoc->allocate_string(a_prop)
			)
		);
	}

	//-------------------------------------------------------------------------
	static void
		SetXmlAttribute(rapidxml::xml_node<char>* a_pEle, const char* a_szName, const String& a_prop)
	{
		rapidxml::xml_document<char>* pDoc = a_pEle->document();
		rapidxml::xml_attribute<char>* pAttr = a_pEle->first_attribute(a_szName);
		if (pAttr)
		{
			pAttr->value(pDoc->allocate_string(a_prop.c_str()));
			return;
		}
		a_pEle->append_attribute(
			pDoc->allocate_attribute(
				pDoc->allocate_string(a_szName),
				pDoc->allocate_string(a_prop.c_str())
			)
		);
	}

	static void
		SetXmlAttribute(rapidxml::xml_node<char>* a_pEle, const char* a_szName, const int& a_prop)
	{
		char buf[MAX_PATH];
		sprintf(buf, "%d", a_prop);
		rapidxml::xml_document<char>* pDoc = a_pEle->document();
		rapidxml::xml_attribute<char>* pAttr = a_pEle->first_attribute(a_szName);
		if (pAttr)
		{
			pAttr->value(pDoc->allocate_string(buf));
			return;
		}
		a_pEle->append_attribute(
			pDoc->allocate_attribute(
				pDoc->allocate_string(a_szName),
				pDoc->allocate_string(buf)
			)
		);
	}

	static void
		SetXmlAttribute(rapidxml::xml_node<char>* a_pEle, const char* a_szName, const unsigned int& a_prop)
	{
		char buf[MAX_PATH];
		sprintf(buf, "%u", a_prop);
		rapidxml::xml_document<char>* pDoc = a_pEle->document();
		rapidxml::xml_attribute<char>* pAttr = a_pEle->first_attribute(a_szName);
		if (pAttr)
		{
			pAttr->value(pDoc->allocate_string(buf));
			return;
		}
		a_pEle->append_attribute(
			pDoc->allocate_attribute(
				pDoc->allocate_string(a_szName),
				pDoc->allocate_string(buf)
			)
		);
	}

	static void
		SetXmlAttribute(rapidxml::xml_node<char>* a_pEle, const char* a_szName, const float& a_prop)
	{
		char buf[MAX_PATH];
		sprintf(buf, "%f", a_prop);
		rapidxml::xml_document<char>* pDoc = a_pEle->document();
		rapidxml::xml_attribute<char>* pAttr = a_pEle->first_attribute(a_szName);
		if (pAttr)
		{
			pAttr->value(pDoc->allocate_string(buf));
			return;
		}
		a_pEle->append_attribute(
			pDoc->allocate_attribute(
				pDoc->allocate_string(a_szName),
				pDoc->allocate_string(buf)
			)
		);
	}

	static void
		SetXmlAttribute(rapidxml::xml_node<char>* a_pEle, const char* a_szName, const bool& a_prop)
	{
		char buf[MAX_PATH];
		sprintf(buf, "%d", a_prop == 0 ? 0 : 1);
		rapidxml::xml_document<char>* pDoc = a_pEle->document();
		rapidxml::xml_attribute<char>* pAttr = a_pEle->first_attribute(a_szName);
		if (pAttr)
		{
			pAttr->value(pDoc->allocate_string(buf));
			return;
		}
		a_pEle->append_attribute(
			pDoc->allocate_attribute(
				pDoc->allocate_string(a_szName),
				pDoc->allocate_string(buf)
			)
		);
	}

	static void
		SetXmlAttribute(rapidxml::xml_node<char>* a_pEle, const char* a_szName, const Color& a_prop)
	{
		char buf[MAX_PATH];
		ColorByte4 ucol = a_prop.ToColorByte4();
		sprintf(buf, "%d,%d,%d,%d", ucol.r, ucol.g, ucol.b, ucol.a);

		rapidxml::xml_document<char>* pDoc = a_pEle->document();
		rapidxml::xml_attribute<char>* pAttr = a_pEle->first_attribute(a_szName);
		if (pAttr)
		{
			pAttr->value(pDoc->allocate_string(buf));
			return;
		}
		a_pEle->append_attribute(
			pDoc->allocate_attribute(
				pDoc->allocate_string(a_szName),
				pDoc->allocate_string(buf)
			)
		);
	}

	//-------------------------------------------------------------------------
	static bool
		GetXmlValue(rapidxml::xml_node<char>* a_pEle, String& a_prop, const String& szDefault = String::EmptyString())
	{
		if (a_pEle)
		{
			const char* szVal = a_pEle->value();
			if (szVal)
			{
				a_prop = szVal;
				return true;
			}
		}
		a_prop = szDefault;
		return false;
	}

	//-------------------------------------------------------------------------
	static bool
		GetXmlValue(rapidxml::xml_node<char>* a_pEle, int32& a_prop, int nDefault = 0)
	{
		if (a_pEle)
		{
			const char* szVal = a_pEle->value();
			if (szVal)
			{
				sscanf(szVal, "%d", &a_prop);
				return true;
			}
		}
		a_prop = nDefault;
		return false;
	}

	//-------------------------------------------------------------------------
	static bool
		GetXmlValue(rapidxml::xml_node<char>* a_pEle, unsigned int& a_prop, unsigned int uDefault = 0)
	{
		if (a_pEle)
		{
			const char* szVal = a_pEle->value();
			if (szVal)
			{
				sscanf(szVal, "%u", &a_prop);
				return true;
			}
		}
		a_prop = uDefault;
		return false;
	}

	//-------------------------------------------------------------------------
	static bool
		GetXmlValue(rapidxml::xml_node<char>* a_pEle, float& a_prop, float fDefault = 0.f)
	{
		if (a_pEle)
		{
			const char* szVal = a_pEle->value();
			if (szVal)
			{
				sscanf(szVal, "%f", &a_prop);
				return true;
			}
		}
		a_prop = fDefault;
		return false;
	}

	//-------------------------------------------------------------------------
	static bool
		GetXmlValue(rapidxml::xml_node<char>* a_pEle, bool& a_prop, bool bDefault = true)
	{
		if (a_pEle)
		{
			const char* szVal = a_pEle->value();
			if (szVal)
			{
				int b;
				sscanf(szVal, "%d", &b);
				a_prop = b == 0 ? false : true;
				return true;
			}
		}
		a_prop = bDefault;
		return false;
	}

	//-------------------------------------------------------------------------
	static bool
		GetXmlValue(rapidxml::xml_node<char>* a_pEle, Color& col, const Color& colDefault = Color(1.f, 1.f, 1.f, 1.f))
	{
		if (a_pEle)
		{
			const char* szVal = a_pEle->value();
			if (szVal)
			{
				int r, g, b, a;
				sscanf(szVal, "%d,%d,%d,%d", &r, &g, &b, &a);
				col = Color((uint8)r, (uint8)g, (uint8)b, (uint8)a);
				return true;
			}
		}
		col = colDefault;
		return false;
	}

	//-------------------------------------------------------------------------
	template<typename T> static bool
		GetXmlValue(rapidxml::xml_node<char>* a_pEle, T& out_value, const T& defaultValue = T())
	{
		if (a_pEle)
		{
			const char* szVal = a_pEle->value();
			if (szVal)
			{
				out_value.FromString(szVal);
				return true;
			}
		}
		out_value = defaultValue;
		return false;
	}
}