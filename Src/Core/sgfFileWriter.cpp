#include "sgfCorePCH.h"
#include "sgfFileWriter.h"
#include "sgfArchive.h"
#include "sgfLog.h"

namespace sgf
{

	FileWriter::FileWriter()
		:m_nSize(0)
		,m_pFile(NULL)
		,m_bTemp(true)
	{

	}

	//-------------------------------------------------------------------------
	FileWriter::~FileWriter()
	{
		if (m_pFile)
		{
			fclose(m_pFile);
			m_pFile = NULL;
			if (m_bTemp)
			{
				Archive::Delete(m_szFileName);
				Archive::Rename(m_szFileName + ".tmp", m_szFileName);
			}
		}
	}

	//-------------------------------------------------------------------------
	const String& 
		FileWriter::GetFileName() const
	{
		return m_szFileName;
	}

	//-------------------------------------------------------------------------
	int32 
		FileWriter::Size() const
	{
		return m_nSize;
	}

	//-------------------------------------------------------------------------
	void 
		FileWriter::WriteData(const void* a_pDst, int32 a_nLen)
	{
		if (a_nLen > 0)
		{
			fwrite(a_pDst, a_nLen, 1, m_pFile);
			m_nSize += a_nLen;
		}
	}

	//-------------------------------------------------------------------------
	void 
		FileWriter::Save()
	{
		if (m_pFile)
		{
			fflush(m_pFile);
		}
	}

	//-------------------------------------------------------------------------
	FileWriter* 
		FileWriter::OpenWriteFile(const String& a_szFile, bool a_bTemp /*= true*/)
	{
		FILE* pFile = NULL;
		String szPath = Archive::GetWriteFullPath(a_szFile);
		String szOpenPath = a_bTemp ? (szPath + ".tmp") : szPath;
		pFile = fopen( szOpenPath.c_str(), "wb");
		LOG_INFO_DEBUG("FileWriter create file : %s", szPath.c_str());
		if (!pFile)
		{
			int nIdx = szPath.rfind('/');
			if (nIdx != INVALID_INDEX)
			{
				String szDir = szPath.subString(0, nIdx);
				LOG_INFO_DEBUG("FileWriter create directory : %s", szDir.c_str());
				Archive::CreateDirectory(szDir);
				pFile = fopen(szOpenPath.c_str(), "wb");
			}
		}
		if (pFile)
		{
			FileWriter* pWriter = new FileWriter();
			pWriter->m_szFileName = szPath;
			pWriter->m_nSize = 0;
			pWriter->m_pFile = pFile;
			pWriter->m_bTemp = a_bTemp;
			return pWriter;
		}
		return NULL;
	}

}