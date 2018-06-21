#include "sgfCorePCH.h"
#include "sgfTimer.h"

namespace sgf
{
	Timer::Timer()
		:m_llStartTick(0)
		,m_llPreTick(0)
		,m_llFrec(0)
		,m_llCurrentFrame(0)
		,m_llFpsFrame(0)
		,m_dElapsed(0.0)
		,m_dRunningTime(0.0)
		,m_dFps(0.0)
		,m_dFpsTime(0.0)
		,m_bPaused(false)
		,m_dRate(1.0)
	{

	}

	//-------------------------------------------------------------------------
	Timer::~Timer()
	{

	}

	//-------------------------------------------------------------------------
	void 
		Timer::Initialize()
	{
		m_dRunningTime = 0.0;
		m_dElapsed = 0.0;
		m_dFps = 0.0;
		m_dFpsTime = 0.0;
		m_llCurrentFrame = 0;
		m_llFpsFrame = 0;
		m_bPaused = false;
		m_dRate = 1.0;

		QueryPerformanceCounter((LARGE_INTEGER*)&m_llStartTick);
		QueryPerformanceFrequency((LARGE_INTEGER*)&m_llFrec);
		m_llPreTick = m_llStartTick;
	}

	void Timer::Destroy()
	{
		m_dRunningTime = 0.0;
		m_dElapsed = 0.0;
		m_dFps = 0.0;
		m_dFpsTime = 0.0;
		m_llCurrentFrame = 0;
		m_llFpsFrame = 0;
		m_bPaused = false;
		m_dRate = 1.0;
	}

	void Timer::Tick()
	{
		m_llCurrentFrame++;
		if (m_llCurrentFrame < 0)
		{
			m_llCurrentFrame = 0;
		}

		int64 llCurrTick;
		QueryPerformanceCounter((LARGE_INTEGER*)&llCurrTick);
		m_dElapsed = static_cast<double>(llCurrTick - m_llPreTick) / static_cast<double>(m_llFrec);
		if (m_bPaused)
		{
			m_llStartTick += llCurrTick - m_llPreTick;
		}
		m_dRunningTime = static_cast<double>(llCurrTick - m_llStartTick) / static_cast<double>(m_llFrec);
		m_llPreTick = llCurrTick;

		if (m_bPaused)
		{
			m_dFps = 0.0;
			m_dFpsTime = m_dRunningTime;
			m_llFpsFrame = m_llCurrentFrame;
		}
		else
		{
			if (m_dRunningTime - m_dFpsTime >= 1.0)
			{
				int64 llFramePassed = m_llCurrentFrame - m_llFpsFrame;
				if (llFramePassed < 0)
				{
					llFramePassed = 0;
				}
				m_dFps = llFramePassed / (m_dRunningTime - m_dFpsTime);
				m_dFpsTime = m_dRunningTime;
				m_llFpsFrame = m_llCurrentFrame;
			}
		}
	}

	//-------------------------------------------------------------------------
	double
		Timer::GetCurrentTime() const
	{
		int64 llCurTick;
		QueryPerformanceCounter((LARGE_INTEGER*)&llCurTick);
		double dCurrentTime = static_cast<double>(llCurTick) / static_cast<double>(m_llFrec);
		return dCurrentTime;
	}
}
