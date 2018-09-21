#pragma once
/*************************************
	created: 2018/08/05 12:51 
	filename:	G:\Visual Studio 2015\SimpleGameFrame\Src\RenderHardwareInterface\DX11\sgfShaderConstantBufferDX11.h
	file path:	G:\Visual Studio 2015\SimpleGameFrame\Src\RenderHardwareInterface\DX11
	file base:	sgfShaderConstantBufferDX11
	file ext:	h	
	author: 	Xiexuelong
	
	purpose:
*************************************/

namespace sgf
{
	
	class ShaderConstantBufferDX11
	{
	public:
		ShaderConstantBufferDX11(ID3D11ShaderReflectionConstantBuffer* a_pReflectionBuffer);
		~ShaderConstantBufferDX11();

		ID3D11Buffer*		GetBuffer();
	private:
		ID3D11Buffer*		m_pBuffer;

		String				m_szName;
		int32				m_nSize;
		TArray<RHIShaderConstantDecl> m_arrVariableDecl;
	};
}