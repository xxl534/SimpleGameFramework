#pragma once
/********************************************************************
	created:	2018/06/16
	created:	16:6:2018   10:14
	filename: 	E:\SimpleGameFramework\Src\Engine\Render\RHI\sgfRHIViewport.h
	file path:	E:\SimpleGameFramework\Src\Engine\Render\RHI
	file base:	sgfRHIViewport
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	struct RHIViewportDesc
	{
		RHIViewportDesc()
			:m_nX(0)
			,m_nY(0)
			,m_nWidth(1)
			,m_nHeight(1)
			,m_fMinDepth(0.f)
			,m_fMaxDepth(1.f)
		{

		}

		RHIViewportDesc(int32 a_nX, int32 a_nY, int32 a_nWidth, int32 a_nHeight, float a_fMinDepth = 0.f, float a_fMaxDepth = 1.f)
			:m_nX( a_nX)
			,m_nY( a_nY)
			,m_nWidth(a_nWidth)
			,m_nHeight(a_nHeight)
			,m_fMinDepth(a_fMinDepth)
			,m_fMaxDepth(a_fMaxDepth)
		{

		}

		void Setup(int32 a_nX, int32 a_nY, int32 a_nWidth, int32 a_nHeight, float a_fMinDepth = 0.f, float a_fMaxDepth = 1.f)
		{
			m_nX = a_nX;
			m_nY = a_nY;
			m_nWidth = a_nWidth;
			m_nHeight = a_nHeight;
			m_fMinDepth = a_fMinDepth;
			m_fMaxDepth = a_fMaxDepth;
		}

		int32 m_nX;
		int32 m_nY;
		int32 m_nWidth;
		int32 m_nHeight;
		float m_fMinDepth;
		float m_fMaxDepth;
	};
}