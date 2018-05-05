#pragma once
/*************************************
	created: 2018/04/22 09:46 
	filename:	G:\Visual Studio 2015\SimpleGameFrame\Src\Win32\sgfWin32App.h
	file path:	G:\Visual Studio 2015\SimpleGameFrame\Src\Win32
	file base:	sgfWin32App
	file ext:	h	
	author: 	xiexuelong
	
	purpose:
*************************************/

#define WINDOW_CLASS "Win32 Application"

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720
namespace sgf
{
	class Win32App : public Application
	{
	public:
		Win32App( const String& a_szAppName = WINDOW_CLASS, WNDPROC a_proc = NULL, int32 a_nVersion = 0, int32 a_nOffsetX = 200, int32 a_nOffsetY = 200 );
		virtual ~Win32App();
		virtual void Initialize(int argc, char** argv, GameWorld* a_pWorld = NULL, int a_nWidth = DEFAULT_WINDOW_WIDTH, int a_nHeight = DEFAULT_WINDOW_HEIGHT) override;
		virtual void Run() override;
		virtual void Destroy() override;
		virtual void Exit() override;
	private:
		void	_LoadGameWorld(int argc, char** argv, GameWorld* a_pWorld, int a_nWidth, int a_nHeight);
	private:
		WNDPROC		m_fnProc;
		GameWorld*	m_pGameWorld;
		String		m_szAppName;

		int			m_nWidth;
		int			m_nHeight;
		int32		m_nOffsetX;
		int32		m_nOffsetY;
		bool		m_bExiting;
	};
}