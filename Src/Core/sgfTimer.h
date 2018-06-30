#pragma once
/********************************************************************
	created:	2018/06/21
	created:	21:6:2018   19:09
	filename: 	E:\SimpleGameFramework\Src\Core\sgfTimer.h
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfTimer
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/
#include "sgfSingleton.h"

namespace sgf
{
	class Timer : public TSingleton<Timer>
	{
		friend class TSingleton<Timer>;
	public:
		void	Initialize();
		void	Destroy();
		void	Tick();
		void	Pause();
		bool	IsPaused() const;
		void	Continue();

		double	GetRate() const;
		void	SetRate(double a_dRate);

		double	GetElapsed(bool a_bEnableRate = true) const;
		double	GetForceElasped(bool a_bEnableRate = true) const;
		double	GetRealElapsed() const;
		double	GetRunningTime() const;
		double	GetFps() const;
		int64	GetCurrentFrame() const;
		double	GetCurrentTime() const;
	private:
		Timer();
		~Timer();
	private:
		int64	m_llStartTick;
		int64	m_llPreTick;
		int64	m_llFrec;
		int64	m_llCurrentFrame;
		int64	m_llFpsFrame;
		
		double	m_dElapsed;
		double	m_dRunningTime;
		double	m_dFps;
		double	m_dFpsTime;

		bool	m_bPaused;
		double	m_dRate;

	};

	//-------------------------------------------------------------------------
	inline void
		Timer::Pause()
	{
		m_bPaused = true;
	}

	//-------------------------------------------------------------------------
	inline bool 
		Timer::IsPaused() const
	{
		return m_bPaused;
	}

	//-------------------------------------------------------------------------
	inline void 
		Timer::Continue()
	{
		m_bPaused = false;
	}

	//-------------------------------------------------------------------------
	inline double
		Timer::GetRate() const
	{
		return m_dRate;
	}

	//-------------------------------------------------------------------------
	inline void
		Timer::SetRate(double a_dRate)
	{
		m_dRate = a_dRate;
	}

	//-------------------------------------------------------------------------
	inline double 
		Timer::GetElapsed(bool a_bEnableRate /*= true*/) const
	{
		return m_bPaused ? 0.0 : (a_bEnableRate ? m_dElapsed * m_dRate : m_dElapsed);
	}

	//-------------------------------------------------------------------------
	inline double 
		Timer::GetForceElasped(bool a_bEnableRate /*= true*/) const
	{
		return a_bEnableRate ? m_dElapsed * m_dRate : m_dElapsed;
	}

	//-------------------------------------------------------------------------
	inline double 
		Timer::GetRealElapsed() const
	{
		return m_dElapsed;
	}

	//-------------------------------------------------------------------------
	inline double 
		Timer::GetRunningTime() const
	{
		return m_dRunningTime;
	}

	//-------------------------------------------------------------------------
	inline double 
		Timer::GetFps() const
	{
		return m_dFps;
	}

	//-------------------------------------------------------------------------
	inline int64
		Timer::GetCurrentFrame() const
	{
		return m_llCurrentFrame;
	}
	
}