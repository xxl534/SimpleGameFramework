#include "sgfCorePCH.h"
#include "sgfFileReader.h"
#include "sgfMath.h"
#include "sgfLog.h"
#include "sgfArchive.h"
namespace sgf
{
	//-------------------------------------------------------------------------
	FileReader::FileReader()
		:m_nSize(0)
		,m_nCurrent(0)
		,m_pData(NULL)
	{

	}

	//-------------------------------------------------------------------------
	FileReader::~FileReader()
	{
		SAFE_FREE(m_pData);
	}

	//-------------------------------------------------------------------------
	String 
		FileReader::GetFileName() const
	{
		return m_szFileName;
	}

	//-------------------------------------------------------------------------
	int32 
		FileReader::Size() const
	{
		return m_nSize;
	}

	//-------------------------------------------------------------------------
	int32 
		FileReader::ReadData(void* a_pDst, int32 a_nLen)
	{
		if (a_nLen > 0)
		{
			if (m_nCurrent + a_nLen > m_nSize)
			{
				a_nLen = m_nSize - m_nCurrent;
			}
			memcpy(a_pDst, m_pData + m_nCurrent, (size_t)a_nLen);
			m_nCurrent += a_nLen;
		}
		return a_nLen;
	}

	//-------------------------------------------------------------------------
	void* 
		FileReader::ReadData(int32 a_nLen)
	{
		void* pData = m_pData + m_nCurrent;
		m_nCurrent = MathClamp(m_nCurrent + a_nLen, 0, m_nSize);
		return pData;
	}

	//-------------------------------------------------------------------------
	const char* 
		FileReader::ReadLine()
	{
		if (m_nCurrent < m_nSize)
		{
			const char* ch = (const char*)(m_pData + m_nCurrent);
			int nLen = 1;
			while (ch[nLen - 1] != '\n'&&ch[nLen - 1] != '\r' && m_nCurrent + nLen < m_nSize)
			{
				++nLen;
			}
			m_nCurrent += nLen;

			if (ch[0] == '\r' || ch[0] == '\n')
			{
				return ReadLine();
			}

			return ch;
		}
		return NULL;
	}

	//-------------------------------------------------------------------------
	void* 
		FileReader::Data()
	{
		return m_pData;
	}

	//-------------------------------------------------------------------------
	bool 
		FileReader::IsEOF() const
	{
		return m_nCurrent >= m_nSize;
	}

	//-------------------------------------------------------------------------
	int32 
		FileReader::Seek(int32 a_nOffset)
	{
		int32 nNewPos = Min(m_nCurrent + a_nOffset, m_nSize);
		int32 nOffset = nNewPos - m_nCurrent;
		m_nCurrent = nNewPos;
		return nOffset;
	}

	//-------------------------------------------------------------------------
	int32 
		FileReader::GetCurrent() const
	{
		return m_nCurrent;
	}

	//-------------------------------------------------------------------------
	FileReader* 
		FileReader::OpenReadFile(const String& a_szFile)
	{
		if (a_szFile.empty())
		{
			LOG_INFO_DEBUG("Open file failed : file name is emply!");
			return NULL;
		}

		String szPath = Archive::GetWriteFullPath(a_szFile);
		FILE* pFile = fopen(szPath.c_str(), "rb");
		/*TCHAR szCurrWorkPath[MAX_PATH];
		memset(szCurrWorkPath, 0, sizeof(TCHAR)*MAX_PATH);
		GetCurrentDirectory(MAX_PATH, szCurrWorkPath);
		Archive::IsFileExist(szPath);
		const char* pMsg = strerror(errno);*/
		if (!pFile)
		{
			szPath = Archive::GetReadFullPath(a_szFile);
			pFile = fopen(szPath.c_str(), "rb");
		}
		if (pFile)
		{
			FileReader* pReader = new FileReader();
			pReader->m_szFileName = szPath;
			fseek(pFile, 0, SEEK_END);
			pReader->m_nSize = (int32)ftell(pFile);
			pReader->m_pData = (uint8*)malloc(pReader->m_nSize+1);
			fseek(pFile, 0, SEEK_SET);
			fread(pReader->m_pData, pReader->m_nSize, 1, pFile);
			//给数据末尾加个0，防止读取字符串最后读挂了
			pReader->m_pData[pReader->m_nSize] = 0;
			fclose(pFile);
			return pReader;
		}
		return NULL;
	}
}
	
