#include "sgfRHIPCH.h"
#include "sgfRHIDevice.h"
#include "DX11/sgfRHIDeviceDX11.h"

namespace sgf
{
	RHIDevice* RHIDevice::ms_pInstance = NULL; 
	//-------------------------------------------------------------------------
	void 
		RHIDevice::Init(ERHIDeviceType a_eType /*= ERHIDeviceType_DX11 */)
	{
		ASSERT(ms_pInstance == NULL);
		if (a_eType == ERHIDeviceType_DX11)
		{
			ms_pInstance = new RHIDeviceDX11();
		}
		ASSERT(ms_pInstance != NULL);
		ms_pInstance->_OnInit();
	}

	//-------------------------------------------------------------------------
	void RHIDevice::Tick()
	{

	}

	void RHIDevice::Exit()
	{

	}

	void RHIDevice::LostDevice()
	{

	}

	void RHIDevice::ResetDevice()
	{

	}

	void RHIDevice::Resize(int32 a_nWidth, int32 a_nHeight)
	{

	}
}
	
