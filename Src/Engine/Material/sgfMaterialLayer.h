#pragma once
/********************************************************************
	created:	2018/06/30
	created:	30:6:2018   20:10
	filename: 	E:\SimpleGameFramework\Src\Engine\Material\sgfMaterialLayer.h
	file path:	E:\SimpleGameFramework\Src\Engine\Material
	file base:	sgfMaterialLayer
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	class MaterialProperties;
	class MaterialTextures;
	class ShaderPass;
	class MaterialLayer
	{
		friend class Material;
	private:
		MaterialLayer();
		MaterialLayer(ShaderPass* a_pPass, MaterialProperties* a_pProps, MaterialTextures* a_ptexs);
		~MaterialLayer();

		void						_MarkConstantsDirty();
		void						_MarkTexturesDirty();
	};
}