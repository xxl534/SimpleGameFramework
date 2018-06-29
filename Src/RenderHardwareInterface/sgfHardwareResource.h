#pragma once
/********************************************************************
	created:	2018/06/24
	created:	24:6:2018   8:25
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\sgfHardwareResource.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface
	file base:	sgfHardwareResource
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	class HardwareResource : public TRefCountedObject
	{
	public:
		HardwareResource();
		virtual ~HardwareResource();

		virtual int32	GetMemoryUsage() const {
			return 0;
		}
		virtual void	OnLostDevice() = 0;
		virtual void	OnResetDevice() = 0;

		static void		LostDevice();
		static void		ResetDevice();
	private:
		static TFastList<HardwareResource*> ms_listHardwareResource;
	};
}