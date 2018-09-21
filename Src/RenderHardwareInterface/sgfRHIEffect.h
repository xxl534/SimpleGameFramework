#pragma once
/********************************************************************
	created:	2018/07/09
	created:	9:7:2018   9:18
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\sgfRHIEffect.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface
	file base:	sgfRHIShader
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/
#include "sgfRHIShaderConstant.h"
#include "sgfRHIShaderTexture.h"

namespace sgf
{
	class RHIEffect : public HardwareResource
	{
	public:
		struct Macro
		{
			String a_szKey;
			String a_szValue;
		};
	public:
		virtual void					Setup(const RHIShaderConstantsRef& a_refCons, const RHIShaderTexturesRef& a_refTexs) = 0;
		virtual RHIShaderConstantsRef	CreateShaderConstants() = 0;
		virtual RHIShaderTexturesRef	CreateShaderTextures() = 0;
	};
	typedef TRefCountPtr<RHIEffect> RHIEffectRef;
}