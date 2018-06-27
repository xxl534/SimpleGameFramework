#pragma once
/********************************************************************
	created:	2018/06/27
	created:	27:6:2018   9:09
	filename: 	E:\SimpleGameFramework\Src\Core\sgfCRC.h
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfCRC
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	uint32 Crc32Little_Str(const char* a_sz);
	uint32 Crc32Little_Str(const wchar* a_sz);
	uint32 Crc32Little_Mem(const void* a_pData, int32 a_nLength);
}