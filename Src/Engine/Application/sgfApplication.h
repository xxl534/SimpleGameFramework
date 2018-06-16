#pragma once
/********************************************************************
	created:	2018/05/05
	created:	5:5:2018   20:20
	filename: 	E:\SimpleGameFramework\Src\Engine\Application\sgfApplication.h
	file path:	E:\SimpleGameFramework\Src\Engine\Application
	file base:	sgfApplication
	file ext:	h
	author:		xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	class GameWorld;
	class Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Initialize(int argc, char** argv, GameWorld* a_pWorld = NULL, int a_nWidth = 1280, int a_nHeight = 720) = 0;
		virtual void Run() = 0;
		virtual void Destroy() = 0;
		virtual void Exit() = 0;
		virtual bool IsExiting() = 0;
	public:
		static Application& Instance();
		static bool			HasInstance();
	private:
		static Application*	ms_pInstance;
	};
}