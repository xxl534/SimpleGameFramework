#pragma once
/********************************************************************
	created:	2018/06/13
	created:	13:6:2018   8:20
	filename: 	E:\SimpleGameFramework\Src\Engine\Camera\sgfSceneCamera.h
	file path:	E:\SimpleGameFramework\Src\Engine\Camera
	file base:	sgfSceneCamera
	file ext:	h
	author:		xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	class RenderWindow;
	class SceneCamera
	{
	public:
		SceneCamera();
		virtual ~SceneCamera();
		virtual void	SetRenderWindow(RenderWindow* a_pRenderWindow);
		virtual RenderWindow*	GetRenderWindow() const;
	private:
		int32			m_nRenderWindowId;
	};
}