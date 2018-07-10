#pragma once
/********************************************************************
	created:	2018/07/09
	created:	9:7:2018   8:39
	filename: 	E:\SimpleGameFramework\Src\Engine\Material\sgfShaderPass.h
	file path:	E:\SimpleGameFramework\Src\Engine\Material
	file base:	sgfShaderPass
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	class ShaderPass
	{
		friend class ShaderEffect;
	public:
		enum ETech
		{
			ETech_Skinning	= 0x01,
			ETech_Fog		= 0x02,
			ETech_LightMap	= 0x04,

			ETech_Count		= 8,
		};
	public:
		inline int32							GetRenderQueueId() const { return m_nRenderQueue; }
		inline const RHIShaderRef&				GetRHIShader(int32 a_nTech) const { return m_arrShaderTech[a_nTech]; }
		inline const RHIRasterizerStateRef&		GetRasterizerState() const { return m_refRasterizerState; }
		inline const RHIBlendStateRef&			GetRHIBlendState() const { return m_refBlendState; }
		inline const RHIDepthStencilStateRef&	GetRHIDepthStencilState() const { return m_refIDepthStencilState; }
	private:
		ShaderPass();
		~ShaderPass();

		inline ShaderPass&	operator=(const ShaderPass& a_rhs) { return *this; }
		void							_LoadFromXml(rapidxml::xml_node<char>* a_pNode);
		TArray<RHIShader::Macro>		_LoadTechMacros(rapidxml::xml_node<char>* a_pNode, const String& a_szTech);

		void							_LoadRasterizerState(rapidxml::xml_node<char>* a_pNode);
		void							_LoadBlendState(rapidxml::xml_node<char>* a_pNode);
		void							_LoadDepthStencilState(rapidxml::xml_node<char>* a_pNode);
		void							_LoadTechs(rapidxml::xml_node<char>* a_pNode);
	private:
		int32							m_nRenderQueue;
		RHIRasterizerStateRef			m_refRasterizerState;
		RHIBlendStateRef				m_refBlendState;
		RHIDepthStencilStateRef			m_refIDepthStencilState;
		TArray<RHIShaderRef>			m_arrShaderTech;
	};
}