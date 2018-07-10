#pragma once
/********************************************************************
	created:	2018/07/09
	created:	9:7:2018   9:21
	filename: 	E:\SimpleGameFramework\Src\RenderHardwareInterface\sgfRHIShaderTexture.h
	file path:	E:\SimpleGameFramework\Src\RenderHardwareInterface
	file base:	sgfRHIShaderTexture
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/
#include "sgfRHIShaderConstant.h"

namespace sgf
{
	typedef RHIShaderConstantDecl RHIShaderTextureDecl;
	class RHIShaderTextures : public HardwareResource
	{
	public:
		virtual void						Setup() = 0;
		
		virtual int32						Count() const = 0;
		virtual const RHIShaderTextureDecl*	GetTextureDecl(int32 a_nIdx) const = 0;
		virtual const RHIShaderTextureDecl*	GetTextureDecl(const String& a_szName) const = 0;
		virtual void						SetTextureResource(int32 a_nIdx, const RHITextureRef& a_refTex) = 0;
		virtual void						SetTextureSampler(int32 a_nIdx, ERHISamplerFilter a_eFilter, ERHIClampMode a_eClampU, ERHIClampMode a_eClampV, ERHIClampMode a_eClampW) = 0;

		virtual void						InitTextureMap(MaterialTextures* a_pTextures) = 0;
		virtual void						UpdateTextureMap(MaterialTextures* a_pTextures) = 0;
	};

	typedef TRefCountPtr<RHIShaderTextures> RHIShaderTexturesRef;
}