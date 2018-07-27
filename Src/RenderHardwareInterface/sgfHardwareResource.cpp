#include "sgfRHIPCH.h"
#include "sgfHardwareResource.h"


namespace sgf
{
	TFastList<HardwareResource*> HardwareResource::ms_listHardwareResource;

	HardwareResource::HardwareResource()
	{
		ms_listHardwareResource.push_back(this);
	}

	//-------------------------------------------------------------------------
	HardwareResource::~HardwareResource()
	{
		ms_listHardwareResource.remove(this);
	}

	//-------------------------------------------------------------------------
	void 
		HardwareResource::OnLostDevice()
	{

	}

	//-------------------------------------------------------------------------
	void 
		HardwareResource::OnResetDevice()
	{

	}

	//-------------------------------------------------------------------------
	void HardwareResource::LostDevice()
	{
		for (TFastList<HardwareResource*>::iterator it = ms_listHardwareResource.begin();
			it != ms_listHardwareResource.end(); ++it)
		{
			(*it)->OnLostDevice();
			++it;
		}
	}

	//-------------------------------------------------------------------------
	void HardwareResource::ResetDevice()
	{
		for (TFastList<HardwareResource*>::iterator it = ms_listHardwareResource.begin();
			it != ms_listHardwareResource.end(); ++it)
		{
			(*it)->ResetDevice();
			++it;
		}
	}

	
}
