#include "sgfSceneCamera.h"

namespace sgf
{

	SceneCamera::SceneCamera()
		:m_nRenderWindowId( -1 )
	{

	}

	//-------------------------------------------------------------------------
	SceneCamera::~SceneCamera()
	{

	}

	//-------------------------------------------------------------------------
	void SceneCamera::SetRenderWindow(RenderWindow * a_pRenderWindow)
	{
		if (a_pRenderWindow)
		{
			/*if( a_pRenderWindow->IsValid())
			{
				m_nRenderWindowId = a_pRenderWindow->GetId();
			}
			else
			{
				
			}*/
		}
	}

	RenderWindow* SceneCamera::GetRenderWindow() const
	{
		return NULL;
	}

}
