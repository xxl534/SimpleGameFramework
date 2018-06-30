#pragma once
/********************************************************************
	created:	2018/06/30
	created:	30:6:2018   16:36
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\sgfRHITexture.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface
	file base:	sgfRHITexture
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	struct RHITexture : public HardwareResource
	{
		virtual void	OnLostDevice() {}
		virtual void	OnResetDevice() {}
	};

	typedef TRefCountPtr<RHITexture>		RHITextureRef;
}