#pragma once
/********************************************************************
	created:	2018/06/30
	created:	30:6:2018   10:25
	filename: 	E:\SimpleGameFramework\Src\Engine\Material\sgfMaterial.h
	file path:	E:\SimpleGameFramework\Src\Engine\Material
	file base:	sgfMaterial
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	class ShaderEffect;
	class ShaderEffectPropDecl;
	class MaterialProperties
	{
		struct Prop
		{
			const ShaderEffectPropDecl* m_pDecl;
			void*						m_pValue;
		};
		friend class Material;
	public:
		int32							GetCount();
		int32							GetIndex(const String& a_szName);
		const String&					GetName(int32 a_nIdx);
		ERHIShaderConstantType			GetType(int32 a_nIdx);
		int32							GetStride(int32 a_nIdx);
		int32							GetArraySize(int32 a_nIdx);
		void*							GetValue(int32 a_nIdx);
		bool							SetValue(int32 a_nIdx, const void* a_pData, int32 a_nLen);
	private:
		MaterialProperties();
		MaterialProperties(const MaterialProperties& a_rhs);
		~MaterialProperties();
		void							_AddProperty(const ShaderEffectPropDecl* a_pDecl);
	private:
		TArray<Prop>		m_arrProperty;
	};

	class MaterialTextures
	{
		friend class Material;
	public:
		struct TexSlot
		{
			const ShaderEffectTexDecl*	m_pDecl;
			RHITextureRef				m_refTex;
			ERHISamplerFilter			m_eFilter;
			ERHIClampMode				m_eClampU;
			ERHIClampMode				m_eClampV;
			ERHIClampMode				m_eClampW;
		};
	public:
		int32							GetCount();
		int32							GetIndex(const String& a_szName);
		const String&					GetName(int32 a_nIdx);
		ERHIShaderConstantType			GetType(int32 a_nIdx);
		const RHITextureRef&			GetTexture(int32 a_nIdx);
		void							SetTexture(int32 a_nIdx, const RHITextureRef& a_refTex);
		ERHISamplerFilter				GetSamplerFilter(int32 a_nIdx);
		void							SetSamplerFilter(int32 a_nIdx, ERHISamplerFilter a_eFilter);
		ERHIClampMode					GetClampModeU(int32 a_nIdx);
		void							SetClampModeU(int32 a_nIdx, ERHIClampMode a_eMode);
		ERHIClampMode					GetClampModeV(int32 a_nIdx);
		void							SetClampModeV(int32 a_nIdx, ERHIClampMode a_eMode);
		ERHIClampMode					GetClampModeW(int32 a_nIdx);
		void							SetClampModeW(int32 a_nIdx, ERHIClampMode a_eMode);
		const TexSlot*					GetTextureSlot(int32 a_nIdx) const;

	private:
		MaterialTextures();
		MaterialTextures(const MaterialTextures& a_rhs);
		~MaterialTextures();
		void							_AddTexture(const ShaderEffectTexDecl* a_pDecl);
	private:
		TArray<TexSlot>					m_arrSlot;
	};

	class MaterialLayer;
	class Material
	{
	public:
		Material();
		Material(const String& a_szMtrl);
		Material(const Material& a_rhs);

		~Material();

		Material&					operator=(const Material& a_rhs);

		bool						IsVisible() const;
		void						SetVisible(bool a_bVisible);

		const String&				GetEffectName() const;

		//property
		int32						GetPropertyCount() const;
		int32						GetPropertyIndex(const String& a_szName) const;
		const String&				GetPropertyName(int32 a_nIdx) const;
		const String&				GetPropertyDisplay(int32 a_nIdx) const;
		ERHIShaderConstantType		GetPropertyType(int32 a_nIdx) const;
		bool						GetPropertyValue(int32 a_nIdx, void*& out_pData, int32* out_pStride = NULL, int32* out_pCount = NULL, ERHIShaderConstantType* out_pType = NULL);
		bool						SetPropertyValue(int32 a_nIdx, const void* a_pData, int32 a_nStride, int32 a_nCount, ERHIShaderConstantType a_eCheckType);
		template<typename T> bool	GetProperty(int32 a_nIdx, T*& out_pValue, int32* out_pCount = NULL);
		template<typename T> bool	SetProperty(int32 a_nIdx, const T* a_pValue, int32 a_nCount = 1);

		//texture
		int32						GetTextureCount() const;
		int32						GetTextureIndex(const String& a_szName) const;
		const String&				GetTextureName(int32 a_nIdx) const;
		ERHISamplerFilter			GetTextureSampleFilter(int32 a_nIdx) const;
		void						SetTextureSampleFilter(int32 a_nIdx, ERHISamplerFilter a_eFilter);
		ERHIClampMode				GetTextureClampModeU(int32 a_nIdx) const;
		void						SetTextureClampModeU(int32 a_nIdx, ERHIClampMode a_eMode);
		ERHIClampMode				GetTextureClampModeV(int32 a_nIdx) const;
		void						SetTextureClampModeV(int32 a_nIdx, ERHIClampMode a_eMode);
		ERHIClampMode				GetTextureClampModeW(int32 a_nIdx) const;
		void						SetTextureClampModeW(int32 a_nIdx, ERHIClampMode a_eMode);
		RHITextureRef				GetTexture(int32 a_nIdx) const;
		void						SetTexture(int32 a_nIdx, const RHITextureRef& a_refTex);
		void						SetTexture(int32 a_nIdx, const String& a_szName);
		
		//layer
		int32						GetLayerCount() const;
		MaterialLayer*				GetLayer(int32 a_nIdx) const;

		//sort key
		uint16						GetSortingGroupID() const;
		void						SetSortingGroupID(uint16 a_uId);
		uint16						GetSortingOrder() const;
		void						SetSortingOrder(uint16 a_uId);
		// key = SortGroupID<<16|SortingOrder
		uint32						GetSortingKey() const;
		void						SetSortingKey(uint32 a_uKey);

		bool						IsValid() const;
		Material*					Clone() const;

		void						LoadFromFile(const String& a_szMtrl);
		void						WriteToFile(DataWriter* a_pWriter);
		void						ReadFromFile(DataReader* a_pReader);
	protected:
		void						_LoadFromFileImpl(const String& a_szMtrl);
		void						_Assign(const Material& a_rhs);

		void						_MarkConstantsDirty();
		void						_MarkTexturesDirty();

		void						_Clear();

		void						_InitProperties();
		void						_InitTextures();
	protected:
		bool					m_bVisible;

		ShaderEffect*			m_pEffect;
		MaterialProperties*		m_pProperties;
		MaterialTextures*		m_pTextures;
		TArray<MaterialLayer*>	m_arrLayer;

		union
		{
			struct
			{
				uint16			m_uSortingGroup;
				uint16			m_uSortingOrder;
			};
			uint32				m_uSortingKey;
		};
	};

	class GfxMaterailSet
	{
	public:
		~GfxMaterailSet()
		{
			
		}

		Material*&			operator[](int a_nIdx);
		const Material*		operator[](int a_nIdx) const;

		void				push_back(Material* a_pMaterial);
		int32				size() const;
		void				clear();
		void				erase(int a_nIdx);
	private:
		TArray<Material*>	m_arrMaterials;
	};
	//-------------------------------------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//MaterialProperties
	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------
	int32
		MaterialProperties::GetCount()
	{
		return m_arrProperty.size();
	}

	//-------------------------------------------------------------------------
	int32
		MaterialProperties::GetIndex(const String& a_szName)
	{
		for (int32 i = 0; i < m_arrProperty.size(); ++i)
		{
			if (m_arrProperty[i].m_pDecl->m_szName == a_szName)
			{
				return i;
			}
		}
		return -1;
	}

	//-------------------------------------------------------------------------
	inline const String&
		MaterialProperties::GetName(int32 a_nIdx)
	{
		return m_arrProperty[a_nIdx].m_pDecl->m_szName;
	}

	//-------------------------------------------------------------------------
	inline ERHIShaderConstantType
		MaterialProperties::GetType(int32 a_nIdx)
	{
		return m_arrProperty[a_nIdx].m_pDecl->m_eType;
	}

	//-------------------------------------------------------------------------
	inline int32
		MaterialProperties::GetStride(int32 a_nIdx)
	{
		return m_arrProperty[a_nIdx].m_pDecl->m_nStride;
	}

	//-------------------------------------------------------------------------
	inline int32
		MaterialProperties::GetArraySize(int32 a_nIdx)
	{
		return m_arrProperty[a_nIdx].m_pDecl->m_nCount;
	}

	//-------------------------------------------------------------------------
	inline void*
		MaterialProperties::GetValue(int32 a_nIdx)
	{
		return m_arrProperty[a_nIdx].m_pValue;
	}

	//-------------------------------------------------------------------------
	inline bool
		MaterialProperties::SetValue(int32 a_nIdx, const void* a_pData, int32 a_nLen)
	{
		Prop& sProp = m_arrProperty[a_nIdx];
		if (sProp.m_pDecl->m_nStride * sProp.m_pDecl->m_nCount >= a_nLen)
		{
			memcpy(sProp.m_pValue, a_pData, a_nLen);
			return true;
		}
		return false;
	}

	//-------------------------------------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//MaterialTextures
	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------
	inline int32
		MaterialTextures::GetCount()
	{
		return m_arrSlot.size();
	}

	//-------------------------------------------------------------------------
	inline int32
		MaterialTextures::GetIndex(const String& a_szName)
	{
		for (int32 i = 0; i < m_arrSlot.size(); ++i)
		{
			if (m_arrSlot[i].m_pDecl->m_szName == a_szName)
			{
				return i;
			}
		}
		return -1;
	}

	//-------------------------------------------------------------------------
	inline const String&
		MaterialTextures::GetName(int32 a_nIdx)
	{
		return m_arrSlot[a_nIdx].m_pDecl->m_szName;
	}

	//-------------------------------------------------------------------------
	inline ERHIShaderConstantType
		MaterialTextures::GetType(int32 a_nIdx)
	{
		return m_arrSlot[a_nIdx].m_pDecl->m_eType;
	}

	//-------------------------------------------------------------------------
	inline const RHITextureRef&
		MaterialTextures::GetTexture(int32 a_nIdx)
	{
		return m_arrSlot[a_nIdx].m_refTex;
	}

	//-------------------------------------------------------------------------
	inline void
		MaterialTextures::SetTexture(int32 a_nIdx, const RHITextureRef& a_refTex)
	{
		m_arrSlot[a_nIdx].m_refTex = a_refTex;
	}

	//-------------------------------------------------------------------------
	inline ERHISamplerFilter
		MaterialTextures::GetSamplerFilter(int32 a_nIdx)
	{
		return m_arrSlot[a_nIdx].m_eFilter;
	}

	//-------------------------------------------------------------------------
	inline void
		MaterialTextures::SetSamplerFilter(int32 a_nIdx, ERHISamplerFilter a_eFilter)
	{
		m_arrSlot[a_nIdx].m_eFilter = a_eFilter;
	}

	//-------------------------------------------------------------------------
	inline ERHIClampMode
		MaterialTextures::GetClampModeU(int32 a_nIdx)
	{
		return m_arrSlot[a_nIdx].m_eClampU;
	}

	//-------------------------------------------------------------------------
	inline void
		MaterialTextures::SetClampModeU(int32 a_nIdx, ERHIClampMode a_eMode)
	{
		m_arrSlot[a_nIdx].m_eClampU = a_eMode;
	}

	//-------------------------------------------------------------------------
	inline ERHIClampMode 
		MaterialTextures::GetClampModeV(int32 a_nIdx)
	{
		return m_arrSlot[a_nIdx].m_eClampV;
	}

	//-------------------------------------------------------------------------
	inline void 
		MaterialTextures::SetClampModeV(int32 a_nIdx, ERHIClampMode a_eMode)
	{
		m_arrSlot[a_nIdx].m_eClampV = a_eMode;
	}

	//-------------------------------------------------------------------------
	inline ERHIClampMode 
		MaterialTextures::GetClampModeW(int32 a_nIdx)
	{
		return m_arrSlot[a_nIdx].m_eClampW;
	}

	//-------------------------------------------------------------------------
	inline void 
		MaterialTextures::SetClampModeW(int32 a_nIdx, ERHIClampMode a_eMode)
	{
		m_arrSlot[a_nIdx].m_eClampW = a_eMode;
	}

	//-------------------------------------------------------------------------
	inline const MaterialTextures::TexSlot* 
		MaterialTextures::GetTextureSlot(int32 a_nIdx) const
	{
		return &m_arrSlot[a_nIdx];
	}

	//-------------------------------------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//Material
	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------
	template<typename T>
	inline bool 
		Material::SetProperty(int32 a_nIdx, const T* a_pValue, int32 a_nCount /*= 1*/)
	{
		int32 nStride = sizeof(T);
		bool b = SetPropertyValue(a_nIdx, a_pValue, nStride, a_nCount, ERHIShaderConstantType_Invalid);
		return b;
	}

	//-------------------------------------------------------------------------
	template<typename T>
	inline bool 
		Material::GetProperty(int32 a_nIdx, T*& out_pValue, int32* out_pCount /*= NULL*/)
	{
		int32 nStride = 0;
		bool b = GetPropertyValue(a_nIdx, out_pValue, &nStride, out_pCount, NULL);
		return b && nStride == sizeof(T);
	}

	//-------------------------------------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//GfxMaterialSet
	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------
	inline Material*& 
		GfxMaterailSet::operator[](int a_nIdx)
	{
		return m_arrMaterials[a_nIdx];
	}

	//-------------------------------------------------------------------------
	inline const Material* 
		GfxMaterailSet::operator[](int a_nIdx) const
	{
		return m_arrMaterials[a_nIdx];
	}

	//-------------------------------------------------------------------------
	inline void 
		GfxMaterailSet::push_back(Material* a_pMaterial)
	{
		m_arrMaterials.push_back(a_pMaterial);
	}

	//-------------------------------------------------------------------------
	inline int32
		GfxMaterailSet::size() const
	{
		return m_arrMaterials.size();
	}

	//-------------------------------------------------------------------------
	inline void 
		GfxMaterailSet::clear()
	{
		for (int32 i = 0; i < m_arrMaterials.size(); ++i)
		{
			SAFE_DELETE(m_arrMaterials[i]);
		}
		m_arrMaterials.clear();
	}

	//-------------------------------------------------------------------------
	void 
		GfxMaterailSet::erase(int a_nIdx)
	{
		m_arrMaterials.erase(a_nIdx);
	}
}