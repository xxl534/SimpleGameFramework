#include "sgfEnginePCH.h"
#include "sgfRenderWindow.h"

namespace sgf
{
	THashMap<int64, RenderWindow*> RenderWindow::ms_mapRenderWindow;
	int64 RenderWindow::ms_nValidId = 0;

	//-------------------------------------------------------------------------
	RenderWindow::RenderWindow()
		:m_nWidth(1)
		,m_nHeight(1)
		,m_bValid(true)
		,m_sViewportDesc( 0, 0, m_nWidth,m_nHeight)
	{
		m_nId = ms_nValidId++;
		ms_mapRenderWindow.insert(m_nId, this);
	}

	//-------------------------------------------------------------------------
	RenderWindow::~RenderWindow()
	{
		ms_mapRenderWindow.remove(m_nId);
	}

	//-------------------------------------------------------------------------
	int64 
		RenderWindow::GetId() const
	{
		return m_nId;
	}

	//-------------------------------------------------------------------------
	bool 
		RenderWindow::IsValid() const
	{
		return m_bValid;
	}

	//-------------------------------------------------------------------------
	int32 
		RenderWindow::GetWidth() const
	{
		return m_nWidth;
	}

	//-------------------------------------------------------------------------
	int32 
		RenderWindow::GetHeight() const
	{
		return m_nHeight;
	}

	//-------------------------------------------------------------------------
	RHIViewportDesc&
		RenderWindow::GetViewport()
	{
		return m_sViewportDesc;
	}

	//-------------------------------------------------------------------------
	void 
		RenderWindow::Setup()
	{
		//todo need implementation
	}

	//-------------------------------------------------------------------------
	RenderWindow* 
		RenderWindow::GetRenderWindow(int64 a_nId)
	{
		THashMap<int64, RenderWindow*>::iterator it = ms_mapRenderWindow.find(a_nId);
		if (it != ms_mapRenderWindow.end())
		{
			return it.value();
		}
		else
		{
			return NULL;
		}
	}

	//-------------------------------------------------------------------------
	void 
		RenderWindow::DestroyAll()
	{
		for (THashMap<int64, RenderWindow*>::iterator it = ms_mapRenderWindow.begin(); it != ms_mapRenderWindow.end(); ++it)
		{
			SAFE_DELETE(it.value());
		}
		ms_mapRenderWindow.clear();
	}

}
