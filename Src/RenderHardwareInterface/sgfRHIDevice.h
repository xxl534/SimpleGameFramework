#pragma once
/********************************************************************
	created:	2018/06/19
	created:	19:6:2018   9:09
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\sgfRHIDevice.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface
	file base:	sgfRHIDevice
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/
namespace sgf
{
	class RHIDevice
	{
	public:
		static RHIDevice*			Get();
		static void					Init( ERHIDeviceType a_eType = ERHIDeviceType_DX11 );
		static void					Tick();
		static void					Exit();
		static void					LostDevice();
		static void					ResetDevice();
		static void					Resize(int32 a_nWidth, int32 a_nHeight);
		virtual	ERHIDeviceType		GetType() const { return ERHIDeviceType_Invalid;  }
	protected:
		virtual void				_OnInit() = 0;
		virtual void				_OnExit() = 0;
		virtual void				_OnTick() = 0;
		virtual void				_OnLostDevice() = 0;
		virtual void				_OnResetDevice() = 0;
		virtual void				_OnResize(int32 a_nWidth, int32 a_nHeight) = 0;
	private:
		static RHIDevice*			ms_pInstance;
	};

	INLINE RHIDevice* 
		RHIDevice::Get()
	{
		return ms_pInstance;
	}
}