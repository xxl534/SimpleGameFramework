#include "sgfEnginePCH.h"
#include "sgfApplication.h"

namespace sgf
{
	Application* Application::ms_pInstance = NULL;
	//-------------------------------------------------------------------------
	Application::Application()
	{
		ASSERT(ms_pInstance == NULL);
		ms_pInstance = this;
	}

	//-------------------------------------------------------------------------
	Application::~Application()
	{
		ASSERT(ms_pInstance == this);
		ms_pInstance = NULL;
	}

	//-------------------------------------------------------------------------
	Application& 
		Application::Instance()
	{
		return *ms_pInstance;
	}

	//-------------------------------------------------------------------------
	bool 
		Application::HasInstance()
	{
		return ms_pInstance != NULL;
	}

}