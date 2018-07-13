#include "sgfRHIDX11Private.h"
#include "sgfRHIShaderDX11.h"

namespace sgf
{ 
	typedef THashMap<String, RHIShaderDX11*> ShaderMapDX11;
	typedef THashMap<String, ID3D11VertexShader*> VertexShaderMapDX11;
	typedef THashMap<String, ID3D11PixelShader*> PixelShaderMapDX11;
	ShaderMapDX11 DX11_mapShader;
	VertexShaderMapDX11 DX11_mapVertexShader;
	PixelShaderMapDX11	DX11_mapPixelShader;
	RHIShaderDX11* DX11_pShader = NULL;
	//-------------------------------------------------------------------------
	RHIShaderDX11::RHIShaderDX11(const String& a_szVS, const String& a_szPS, const TArray<RHIShader::Macro>& a_arrMacro)
		:m_pVertexShader(NULL)
		,m_pPixelShader(NULL)
	{
		_Initialize(a_szVS, a_szPS, a_arrMacro);
	}

	//-------------------------------------------------------------------------
	RHIShaderDX11::~RHIShaderDX11()
	{

	}

	//-------------------------------------------------------------------------
	void 
		RHIShaderDX11::Setup(const RHIShaderConstantsRef& a_refCons, const RHIShaderTexturesRef& a_refTexs)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	//-------------------------------------------------------------------------
	RHIShaderConstantsRef 
		RHIShaderDX11::CreateShaderConstants()
	{
		throw std::exception("The method or operation is not implemented.");
	}

	//-------------------------------------------------------------------------
	RHIShaderTexturesRef 
		RHIShaderDX11::CreateShaderTextures()
	{
		throw std::exception("The method or operation is not implemented.");
	}
	
	//-------------------------------------------------------------------------
	void 
		RHIShaderDX11::OnLostDevice()
	{
		
	}

	//-------------------------------------------------------------------------
	void 
		RHIShaderDX11::OnResetDevice()
	{
		
	}

	//-------------------------------------------------------------------------
	void 
		RHIShaderDX11::Init()
	{

	}

	//-------------------------------------------------------------------------
	void 
		RHIShaderDX11::Tick()
	{

	}

	//-------------------------------------------------------------------------
	void 
		RHIShaderDX11::Exit()
	{
		for (ShaderMapDX11::iterator it = DX11_mapShader.begin(); it != DX11_mapShader.end(); ++it)
		{
			it->second->Release();
		}
		DX11_mapShader.clear();
		for (VertexShaderMapDX11::iterator it = DX11_mapVertexShader.begin(); it != DX11_mapVertexShader.end(); ++it)
		{
			SAFE_RELEASE(it->second);
		}
		DX11_mapVertexShader.clear();
		for (PixelShaderMapDX11::iterator it = DX11_mapPixelShader.begin(); it != DX11_mapPixelShader.end(); ++it)
		{
			SAFE_RELEASE(it->second);
		}
		DX11_mapPixelShader.clear();
	}

	//-------------------------------------------------------------------------
	String 
		_UniqueIndividualShaderName(const String& a_szShader, const TArray<RHIShader::Macro>& a_arrMacro)
	{
		String szName = a_szShader;
		for (int32 i = 0; i < a_arrMacro.size(); ++i)
		{
			szName.append(a_arrMacro[i].a_szKey);
			szName.append(a_arrMacro[i].a_szValue);
		}
		return szName;
	}

	//-------------------------------------------------------------------------
	TArray<D3D_SHADER_MACRO,false,false> 
		_GetDX11Marco(const TArray<RHIShader::Macro>& a_arrMacro)
	{
		TArray<D3D_SHADER_MACRO, false, false> arrDXMacro(a_arrMacro.size() + 1);
		for (int32 i = 0; i < a_arrMacro.size(); ++i)
		{
			arrDXMacro[i].Name = a_arrMacro[i].a_szKey.c_str();
			arrDXMacro[i].Definition = a_arrMacro[i].a_szValue.c_str();
		}
		arrDXMacro.back().Name = NULL;
		arrDXMacro.back().Definition = NULL;
		return arrDXMacro;
	}

	//-------------------------------------------------------------------------
	ID3D11VertexShader* 
		_CreateVertexShader(const String& a_szVS, const TArray<RHIShader::Macro>& a_arrMacro)
	{
		TArray<D3D_SHADER_MACRO, false, false> arrDXMacro = _GetDX11Marco( a_arrMacro );
		ID3D10Blob* sCompiledShader = NULL;
		ID3D10Blob* sCompilationMsgs = NULL;
		HRESULT hr = D3DCompileFromFile(a_szVS.c_str, arrDXMacro.begin(), NULL, "main", "vs_5_0", D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, NULL, &sCompiledShader, &sCompilationMsgs);
		if (sCompilationMsgs != NULL)
		{
			MessageBox(0, (char*)sCompilationMsgs->GetBufferPointer(), 0, 0);
			SAFE_RELEASE(sCompilationMsgs);
		}
		HR(hr);
		ID3D11VertexShader* pVertexShader;
		HR(DX11_pDevice->CreateVertexShader(sCompiledShader->GetBufferPointer(), sCompiledShader->GetBufferSize(), NULL, &pVertexShader));
		SAFE_RELEASE(sCompiledShader);
		return pVertexShader;
	}

	//-------------------------------------------------------------------------
	ID3D11VertexShader* 
		_ParseVertexShader(const String& a_szVS, const TArray<RHIShader::Macro>& a_arrMacro)
	{
		String szName = _UniqueIndividualShaderName(a_szVS, a_arrMacro);
		VertexShaderMapDX11::iterator it = DX11_mapVertexShader.find(szName);
		if (it != DX11_mapVertexShader.end())
		{
			return it->second;
		}
		else
		{
			ID3D11VertexShader* pVertexShader = _CreateVertexShader(a_szVS, a_arrMacro);
			DX11_mapVertexShader.insert(szName, pVertexShader);
			return pVertexShader;
		}
	}

	//-------------------------------------------------------------------------
	ID3D11PixelShader*
		_CreatePixelShader(const String& a_szPS, const TArray<RHIShader::Macro>& a_arrMacro)
	{
		TArray<D3D_SHADER_MACRO, false, false> arrDXMacro = _GetDX11Marco(a_arrMacro);
		ID3D10Blob* sCompiledShader = NULL;
		ID3D10Blob* sCompilationMsgs = NULL;
		HRESULT hr = D3DCompileFromFile(a_szPS.c_str, arrDXMacro.begin(), NULL, "main", "ps_5_0", D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, NULL, &sCompiledShader, &sCompilationMsgs);
		if (sCompilationMsgs != NULL)
		{
			MessageBox(0, (char*)sCompilationMsgs->GetBufferPointer(), 0, 0);
			SAFE_RELEASE(sCompilationMsgs);
		}
		HR(hr);
		ID3D11PixelShader* pPixelShader;
		HR(DX11_pDevice->CreatePixelShader(sCompiledShader->GetBufferPointer(), sCompiledShader->GetBufferSize(), NULL, &pPixelShader));
		SAFE_RELEASE(sCompiledShader);
		return pPixelShader;
	}

	//-------------------------------------------------------------------------
	ID3D11PixelShader*
		_ParserPixelShader(CONST String& a_szPS, const TArray<RHIShader::Macro>& a_arrMacro)
	{
		String szName = _UniqueIndividualShaderName(a_szPS, a_arrMacro);
		PixelShaderMapDX11::iterator it = DX11_mapPixelShader.find(szName);
		if (it != DX11_mapPixelShader.end())
		{
			return it->second;
		}
		else
		{
			ID3D11PixelShader* pPixelShader = _CreatePixelShader(a_szPS, a_arrMacro);
			DX11_mapPixelShader.insert(szName, pPixelShader);
			return pPixelShader;
		}
	}
	//-------------------------------------------------------------------------
	void 
		RHIShaderDX11::_Initialize(const String& a_szVS, const String& a_szPS, const TArray<RHIShader::Macro>& a_arrMacro)
	{
		m_pVertexShader = _ParseVertexShader(a_szVS, a_arrMacro);
		m_pPixelShader = _ParserPixelShader(a_szPS, a_arrMacro);
		_InitAttribute();
		_InitUniform();
	}

	//-------------------------------------------------------------------------
	void 
		RHIShaderDX11::_InitAttribute()
	{

	}

	//-------------------------------------------------------------------------
	void 
		RHIShaderDX11::_InitUniform()
	{

	}

	//-------------------------------------------------------------------------
	String 
		_UniqueShaderName(const String& a_szVS, const String& a_szPS, const TArray<RHIShader::Macro>& a_arrMacro)
	{
		String szUniqueName = a_szVS + a_szPS;
		for (int32 i = 0; i < a_arrMacro.size(); ++i)
		{
			szUniqueName.append(a_arrMacro[i].a_szKey);
			szUniqueName.append(a_arrMacro[i].a_szValue);
		}
		return szUniqueName;
	}
	//-------------------------------------------------------------------------
	RHIShaderRef
		RHICreateShaderDX11(const String& a_szVS, const String& a_szPS, const TArray<RHIShader::Macro>& a_arrMacro)
	{
		String szUniqueName = _UniqueShaderName(a_szVS, a_szPS, a_arrMacro);
		ShaderMapDX11::iterator it = DX11_mapShader.find(szUniqueName);
		if (it != DX11_mapShader.end())
		{
			return it->second;
		}
		else
		{
			RHIShaderDX11* pShader = new RHIShaderDX11(a_szVS, a_szPS, a_arrMacro);
			pShader->AddRef();
			DX11_mapShader.insert(szUniqueName, pShader);
			return pShader;
		}
	}
}
