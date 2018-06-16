#pragma once
/********************************************************************
	created:	2018/05/06
	created:	6:5:2018   16:32
	filename: 	E:\SimpleGameFramework\Src\Engine\Render\sgfRenderWindow.h
	file path:	E:\SimpleGameFramework\Src\Engine\Render
	file base:	sgfRenderWindow
	file ext:	h
	author:		xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	class RenderWindow
	{
	public:
				RenderWindow();
		virtual ~RenderWindow();

		int64			GetId() const;
		virtual bool	IsValid() const;
		int32			GetWidth() const;
		int32			GetHeight() const;
		virtual RHIViewportDesc&	GetViewport();

		virtual void	Setup();
		virtual void	SwapBuffers(bool a_bWaitForVSyn = true) = 0;

		static RenderWindow*	GetRenderWindow(int64 a_nId);
		static void				DestroyAll();
	protected:
		int64		m_nId;
		int32		m_nWidth;
		int32		m_nHeight;
		bool		m_bValid;
		RHIViewportDesc	m_sViewportDesc;
		//static
		static int64							ms_nValidId;
		static THashMap<int64, RenderWindow*>	ms_mapRenderWindow;
	};
}