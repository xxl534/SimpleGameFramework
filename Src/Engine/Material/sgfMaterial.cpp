#include "sgfEnginePCH.h"
#include "sgfMaterial.h"
#include "sgfMaterialLayer.h"
#include "sgfShaderEffect.h"

namespace sgf
{
	//-------------------------------------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//MaterialProperties
	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------
	MaterialProperties::MaterialProperties()
	{

	}

	//-------------------------------------------------------------------------
	MaterialProperties::MaterialProperties(const MaterialProperties& a_rhs)
	{
		int32 nCount = a_rhs.m_arrProperty.size();
		m_arrProperty.resize(nCount);
		for (int32 i = 0; i < nCount; ++i)
		{
			const Prop& sPropRhs = a_rhs.m_arrProperty[i];
			Prop& sProp = m_arrProperty[i];
			sProp.m_pDecl = sPropRhs.m_pDecl;

			int32 nDataSize = sProp.m_pDecl->m_nStride * sProp.m_pDecl->m_nCount;
			sProp.m_pValue = malloc(nDataSize);
			memcpy(sProp.m_pValue, sPropRhs.m_pValue, nDataSize);
		}
	}

	//-------------------------------------------------------------------------
	MaterialProperties::~MaterialProperties()
	{
		for (int32 i = 0; i < m_arrProperty.size(); i++)
		{
			SAFE_FREE(m_arrProperty[i].m_pValue);
		}
		m_arrProperty.clear();
	}

	//-------------------------------------------------------------------------
	void 
		MaterialProperties::_AddProperty(const ShaderEffectPropDecl* a_pDecl)
	{
		Prop sProp = { a_pDecl, malloc(a_pDecl->m_nStride * a_pDecl->m_nCount) };
		memcpy(sProp.m_pValue, a_pDecl->m_pDefaultValue, a_pDecl->m_nStride * a_pDecl->m_nCount);
		m_arrProperty.push_back(sProp);
	}

	//-------------------------------------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//MaterialTextures
	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------
	MaterialTextures::MaterialTextures()
	{

	}

	//-------------------------------------------------------------------------
	MaterialTextures::MaterialTextures(const MaterialTextures& a_rhs)
	{
		m_arrSlot = a_rhs.m_arrSlot;
	}

	//-------------------------------------------------------------------------
	MaterialTextures::~MaterialTextures()
	{

	}

	void MaterialTextures::_AddTexture(const ShaderEffectTexDecl* a_pDecl)
	{
		TexSlot sSlot = { a_pDecl, NULL, a_pDecl->m_eFilter, a_pDecl->m_eClampU, a_pDecl->m_eClampV, a_pDecl->m_eClampW };
		m_arrSlot.push_back(sSlot);
	}

	//-------------------------------------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//Material
	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------
	Material::Material()
		:m_bVisible(false)
		,m_pEffect(NULL)
		,m_pProperties(NULL)
		,m_pTextures(NULL)
		,m_uSortingGroup(32768)
		,m_uSortingOrder(32768)
	{

	}

	Material::Material(const String& a_szMtrl)
		:m_bVisible(false)
		, m_pEffect(NULL)
		, m_pProperties(NULL)
		, m_pTextures(NULL)
		, m_uSortingGroup(32768)
		, m_uSortingOrder(32768)
	{
		_LoadFromFileImpl(a_szMtrl);
	}

	Material::Material(const Material& a_rhs)
		:m_bVisible(false)
		, m_pEffect(NULL)
		, m_pProperties(NULL)
		, m_pTextures(NULL)
		, m_uSortingGroup(32768)
		, m_uSortingOrder(32768)
	{
		_Assign(a_rhs);
	}

	//-------------------------------------------------------------------------
	Material::~Material()
	{
		_Clear();
	}

	//-------------------------------------------------------------------------
	bool Material::IsVisible() const
	{
		return m_bVisible;
	}

	//-------------------------------------------------------------------------
	void 
		Material::SetVisible(bool a_bVisible)
	{
		m_bVisible = a_bVisible;
	}

	//-------------------------------------------------------------------------
	const String& 
		Material::GetEffectName() const
	{
		if( m_pEffect )
		{ 
			return m_pEffect->GetFileName();
		}
		return String::EmptyString();
	}

	//-------------------------------------------------------------------------
	int32 
		Material::GetPropertyCount() const
	{
		return m_pEffect->GetPropertyDeclCount();
	}

	//-------------------------------------------------------------------------
	int32 
		Material::GetPropertyIndex(const String& a_szName) const
	{
		const ShaderEffectPropDecl* pDecl = m_pEffect->GetPropertyDecl(a_szName);
		if (pDecl)
		{
			return pDecl->m_nIndex;
		}
		return -1;
	}

	//-------------------------------------------------------------------------
	const String& 
		Material::GetPropertyName(int32 a_nIdx) const
	{
		const ShaderEffectPropDecl* pDecl = m_pEffect->GetPropertyDecl(a_nIdx);
		if (pDecl)
		{
			return pDecl->m_szName;
		}
		return String::EmptyString();
	}

	//-------------------------------------------------------------------------
	const String& 
		Material::GetPropertyDisplay(int32 a_nIdx) const
	{
		const ShaderEffectPropDecl* pDecl = m_pEffect->GetPropertyDecl(a_nIdx);
		if (pDecl)
		{
			return pDecl->m_szDisplay;
		}
		return String::EmptyString();
	}

	//-------------------------------------------------------------------------
	ERHIShaderConstantType 
		Material::GetPropertyType(int32 a_nIdx) const
	{
		const ShaderEffectPropDecl* pDecl = m_pEffect->GetPropertyDecl(a_nIdx);
		if (pDecl)
		{
			return pDecl->m_eType;
		}
		return ERHIShaderConstantType_Invalid;
	}

	//-------------------------------------------------------------------------
	bool 
		Material::GetPropertyValue(int32 a_nIdx, void*& out_pData, int32* out_pStride /*= NULL*/, int32* out_pCount /*= NULL*/, ERHIShaderConstantType* out_pType /*= NULL*/)
	{
		if (a_nIdx >= 0 && a_nIdx < m_pProperties->GetCount())
		{
			out_pData = m_pProperties->GetValue(a_nIdx);
			if (out_pStride)
			{
				*out_pStride = m_pProperties->GetStride(a_nIdx);
			}
			if (out_pCount)
			{
				*out_pCount = m_pProperties->GetArraySize(a_nIdx);
			}
			if (out_pType)
			{
				*out_pType = m_pProperties->GetType(a_nIdx);
			}
			return true;
		}
		return false;
	}

	//-------------------------------------------------------------------------
	bool 
		Material::SetPropertyValue(int32 a_nIdx, const void* a_pData, int32 a_nStride, int32 a_nCount, ERHIShaderConstantType a_eCheckType)
	{
		int32 nCountMax = m_pProperties->GetArraySize(a_nIdx);
		if (a_nIdx >= 0 && a_nIdx < m_pProperties->GetCount() &&
			a_nStride == m_pProperties->GetStride(a_nIdx) &&
			a_nCount <= nCountMax &&
			(a_eCheckType == ERHIShaderConstantType_Invalid || a_eCheckType == m_pProperties->GetType(a_nIdx))
			)
		{
			if (a_nCount != nCountMax ||
				memcmp(m_pProperties->GetValue(a_nIdx), a_pData, a_nStride * a_nCount) != 0
				)
			{
				m_pProperties->SetValue(a_nIdx, a_pData, a_nCount * a_nStride);
				_MarkConstantsDirty();
			}
			return true;
		}
		return false;
	}

	//-------------------------------------------------------------------------
	int32 
		Material::GetTextureCount() const
	{
		return m_pTextures->GetCount();
	}

	//-------------------------------------------------------------------------
	int32 
		Material::GetTextureIndex(const String& a_szName) const
	{
		return m_pTextures->GetIndex(a_szName);
	}

	//-------------------------------------------------------------------------
	const String& 
		Material::GetTextureName(int32 a_nIdx) const
	{
		return m_pTextures->GetName(a_nIdx);
	}

	//-------------------------------------------------------------------------
	ERHISamplerFilter 
		Material::GetTextureSampleFilter(int32 a_nIdx) const
	{
		return m_pTextures->GetSamplerFilter(a_nIdx);
	}

	//-------------------------------------------------------------------------
	void 
		Material::SetTextureSampleFilter(int32 a_nIdx, ERHISamplerFilter a_eFilter)
	{
		m_pTextures->SetSamplerFilter(a_nIdx, a_eFilter);
	}

	//-------------------------------------------------------------------------
	ERHIClampMode 
		Material::GetTextureClampModeU(int32 a_nIdx) const
	{
		return m_pTextures->GetClampModeU(a_nIdx);
		_MarkTexturesDirty();
	}

	//-------------------------------------------------------------------------
	void 
		Material::SetTextureClampModeU(int32 a_nIdx, ERHIClampMode a_eMode)
	{
		m_pTextures->SetClampModeU(a_nIdx, a_eMode);
		_MarkTexturesDirty();
	}

	//-------------------------------------------------------------------------
	ERHIClampMode 
		Material::GetTextureClampModeV(int32 a_nIdx) const
	{
		return m_pTextures->GetClampModeV(a_nIdx);
	}

	//-------------------------------------------------------------------------
	void 
		Material::SetTextureClampModeV(int32 a_nIdx, ERHIClampMode a_eMode)
	{
		m_pTextures->SetClampModeV(a_nIdx, a_eMode);
		_MarkTexturesDirty();
	}

	//-------------------------------------------------------------------------
	ERHIClampMode 
		Material::GetTextureClampModeW(int32 a_nIdx) const
	{
		return m_pTextures->GetClampModeW(a_nIdx);
	}

	//-------------------------------------------------------------------------
	void 
		Material::SetTextureClampModeW(int32 a_nIdx, ERHIClampMode a_eMode)
	{
		m_pTextures->SetClampModeW(a_nIdx, a_eMode);
		_MarkTexturesDirty();
	}

	//-------------------------------------------------------------------------
	RHITextureRef 
		Material::GetTexture(int32 a_nIdx) const
	{
		return m_pTextures->GetTexture(a_nIdx);
	}

	//-------------------------------------------------------------------------
	void 
		Material::SetTexture(int32 a_nIdx, const RHITextureRef& a_refTex)
	{
		m_pTextures->SetTexture(a_nIdx, a_refTex);
		_MarkTexturesDirty();
	}

	//-------------------------------------------------------------------------
	void 
		Material::SetTexture(int32 a_nIdx, const String& a_szName)
	{
		RHITextureRef refTex = RHICreateTextureFromFile(a_szName, ERHIResourceUsage_Static, ERHIPixelFormat_Default, 1);
		SetTexture(a_nIdx, refTex);
	}

	//-------------------------------------------------------------------------
	int32 
		Material::GetLayerCount() const
	{
		return m_arrLayer.size();
	}

	//-------------------------------------------------------------------------
	MaterialLayer* 
		Material::GetLayer(int32 a_nIdx) const
	{
		return m_arrLayer[a_nIdx];
	}

	//-------------------------------------------------------------------------
	uint16 
		Material::GetSortingGroupID() const
	{
		return m_uSortingGroup;
	}

	//-------------------------------------------------------------------------
	void 
		Material::SetSortingGroupID(uint16 a_uId)
	{
		m_uSortingGroup = a_uId;
	}

	//-------------------------------------------------------------------------
	uint16
		Material::GetSortingOrder() const
	{
		return m_uSortingOrder;
	}

	//-------------------------------------------------------------------------
	void 
		Material::SetSortingOrder(uint16 a_uId)
	{
		m_uSortingOrder = a_uId;
	}

	//-------------------------------------------------------------------------
	uint32 
		Material::GetSortingKey() const
	{
		return m_uSortingKey;
	}

	//-------------------------------------------------------------------------
	void 
		Material::SetSortingKey(uint32 a_uKey)
	{
		m_uSortingKey = a_uKey;
	}

	//-------------------------------------------------------------------------
	bool 
		Material::IsValid() const
	{
		return m_pEffect != NULL;
	}

	//-------------------------------------------------------------------------
	Material* 
		Material::Clone() const
	{
		ASSERT(IsValid());
		return new Material(*this);
	}

	//-------------------------------------------------------------------------
	void 
		Material::LoadFromFile(const String& a_szMtrl)
	{
		if (IsValid() == false || m_pEffect->GetFileName() != a_szMtrl)
		{
			_LoadFromFileImpl(a_szMtrl);
		}
	}

	//-------------------------------------------------------------------------
	void 
		Material::WriteToFile(DataWriter* a_pWriter)
	{
		//todo unimplemented
	}

	//-------------------------------------------------------------------------
	void 
		Material::ReadFromFile(DataReader* a_pReader)
	{
		//todo unimplemented
	}

	//-------------------------------------------------------------------------
	void 
		Material::_LoadFromFileImpl(const String& a_szMtrl)
	{
		_Clear();

		m_pEffect = ShaderEffect::LoadFromFile(a_szMtrl);
		m_bVisible = m_pEffect->GetVisible();

		_InitProperties();
		_InitTextures();

		int32 nPassCount = m_pEffect->GetPassCount;
		for (int32 i = 0; i < nPassCount; ++i)
		{
			ShaderPass* pPass = m_pEffect->GetPass(i);
			m_arrLayer.push_back(
				new MaterialLayer(
					pPass,
					m_pProperties,
					m_pTextures,
					);
			);
		}
	}

	//-------------------------------------------------------------------------
	void 
		Material::_Assign(const Material& a_rhs)
	{
		if (!a_rhs.IsValid())
		{
			return;
		}

		_Clear();

		m_pEffect = a_rhs.m_pEffect;
		m_bVisible = a_rhs.m_bVisible;
		m_pProperties = new MaterialProperties(*(a_rhs.m_pProperties));
		m_pTextures = new MaterialTextures(*(a_rhs.m_pTextures));
		m_uSortingKey = a_rhs.m_uSortingKey;

		int32 nPassCount = m_pEffect->GetPassCount;
		for (int32 i = 0; i < nPassCount; ++i)
		{
			ShaderPass* pPass = m_pEffect->GetPass(i);
			m_arrLayer.push_back(
				new MaterialLayer(
					pPass,
					m_pProperties,
					m_pTextures,
					);
			);
		}
	}

	//-------------------------------------------------------------------------
	Material& 
		Material::operator=(const Material& a_rhs)
	{
		_Assign(a_rhs);
		return *this;
	}

	//-------------------------------------------------------------------------
	void
		Material::_MarkConstantsDirty()
	{
		for( int32 i = 0; i < m_arrLayer.size(); ++i )
		{
			m_arrLayer[i]->_MarkConstantsDirty();
		}
	}

	//-------------------------------------------------------------------------
	void 
		Material::_MarkTexturesDirty()
	{
		for (int32 i = 0; i < m_arrLayer.size(); ++i)
		{
			m_arrLayer[i]->_MarkTexturesDirty();
		}
	}

	//-------------------------------------------------------------------------
	void 
		Material::_Clear()
	{
		m_pEffect = NULL;
		m_bVisible = false;
		SAFE_DELETE(m_pProperties);
		SAFE_DELETE(m_pTextures);
		for (int32 i = 0; i < m_arrLayer.size(); i++)
		{
			SAFE_DELETE(m_arrLayer[i]);
		}
		m_arrLayer.clear();
	}

	//-------------------------------------------------------------------------
	void 
		Material::_InitProperties()
	{
		if (IsValid())
		{
			ASSERT(m_pProperties == NULL);
			m_pProperties = new MaterialProperties();
			int32 nCount = m_pEffect->GetPropertyDeclCount();
			for (int32 i = 0; i < nCount; ++i)
			{
				m_pProperties->_AddProperty(m_pEffect->GetPropertyDecl(i));
			}
		}
	}

	//-------------------------------------------------------------------------
	void 
		Material::_InitTextures()
	{
		if (IsValid())
		{
			ASSERT(m_pTextures == NULL);
			m_pTextures = new MaterialTextures();
			int32 nCount = m_pEffect->GetTextureDeclCount();
			for (int32 i = 0; i < nCount; ++i)
			{
				m_pTextures->_AddTexture(m_pEffect->GetTextureDecl(i));
			}
		}
	}

}