#include "sgfRHIPCH.h"
#include "sgfRHIDevice.h"
#include "DX11/sgfRHIDeviceDX11.h"

namespace sgf
{
	RHIDevice* RHIDevice::ms_pInstance = NULL;
	//-------------------------------------------------------------------------
	void 
		RHIDevice::Init(ERHIDeviceType a_eType /*= ERHIDeviceType_DX11 */)
	{
		ASSERT(ms_pInstance == NULL);
		if (a_eType == ERHIDeviceType_DX11)
		{
			ms_pInstance = new RHIDeviceDX11();
		}
		ASSERT(ms_pInstance != NULL);
		ms_pInstance->_OnInit();
	}

	//-------------------------------------------------------------------------
	void 
		RHIDevice::Tick()
	{
		ASSERT(ms_pInstance);
		ms_pInstance->_OnTick();
	}

	//----------------------------------------
	void 
		RHIDevice::Exit()
	{
		ASSERT(ms_pInstance);
		ms_pInstance->_OnExit();
		SAFE_DELETE(ms_pInstance);

		_FreeBuildinConstantsValues();
	}

	//----------------------------------------
	void 
		RHIDevice::LostDevice()
	{
		Get()->_OnLostDevice();
	}

	//----------------------------------------
	void 
		RHIDevice::ResetDevice()
	{
		Get()->_OnResetDevice();
	}

	//----------------------------------------
	void 
		RHIDevice::Resize(int32 a_nWidth, int32 a_nHeight)
	{
		Get()->_OnResize(a_nWidth, a_nHeight);
	}

	//----------------------------------------
	TArray<RHIShaderConstantDecl>	s_arrBuildinConstantDecl;
	TArray<void*>					s_arrBuildinConstantValue;
	THashMap<String, int32>			s_mapBuildinConstantNames;
	//----------------------------------------
	RHIShaderConstantDecl*
		RHIGetShaderConstantDeclDefault(const String& szName)
	{
		return &s_arrBuildinConstantDecl[s_mapBuildinConstantNames[szName]];
	}

	//-------------------------------------------------------------------------
	const void*
		RHIGetShaderConstantValueDefault(int32 a_nIdx)
	{
		return s_arrBuildinConstantValue[a_nIdx];
	}

	//-------------------------------------------------------------------------
	void
		RHISetShaderConstantValueDefault(int32 a_nIdx, const void* a_pData, int32 a_nStride, int32 a_nCount)
	{
		memcpy(s_arrBuildinConstantValue[a_nIdx], a_pData, a_nStride*a_nCount);
	}

	//-------------------------------------------------------------------------
	const Matrix4f&
		RHIGetShaderMatrixDefault(ERHIShaderMatrix a_eMatrix)
	{
		return *(const Matrix4f*)s_arrBuildinConstantValue[a_eMatrix];
	}

	//-------------------------------------------------------------------------
	void
		RHISetShaderMatrixDefault(ERHIShaderMatrix a_eMatrix, const Matrix4f& a_mat)
	{
		memcpy(s_arrBuildinConstantValue[a_eMatrix], &a_mat, s_arrBuildinConstantDecl[a_eMatrix].m_nStride);
	}

	//-------------------------------------------------------------------------
	const Matrix4f*
		RHIGetShaderMatrixArrayDefault(ERHIShaderMatrix a_eMatrix, int32* a_nCount)
	{
		*a_nCount = s_arrBuildinConstantDecl[a_eMatrix].m_nCount;
		return (const Matrix4f*)s_arrBuildinConstantValue[a_eMatrix];
	}

	//-------------------------------------------------------------------------
	void
		RHISetShaderMatrixArrayDefault(ERHIShaderMatrix a_eMatrix, const Matrix4f* a_pMat, int32 a_nCount)
	{
		memcpy(s_arrBuildinConstantValue[a_eMatrix], a_pMat, s_arrBuildinConstantDecl[a_eMatrix].m_nStride*a_nCount);
	}

	//-------------------------------------------------------------------------
	const float*
		RHIGetShaderFloat4Default(ERHIShaderFloat4 a_eType)
	{
		return (const float*)s_arrBuildinConstantValue[a_eType];
	}

	//-------------------------------------------------------------------------
	void
		RHISetShaderFloat4Default(ERHIShaderFloat4 a_eType, const float* pVal)
	{
		memcpy(s_arrBuildinConstantValue[a_eType], pVal, s_arrBuildinConstantDecl[a_eType].m_nStride);
	}

	//-------------------------------------------------------------------------
	void
		RHISetShaderFloat4ArrayDefault(ERHIShaderFloat4 a_eType, const float* pVal, int32 a_nCount)
	{
		memcpy(s_arrBuildinConstantValue[a_eType], pVal, s_arrBuildinConstantDecl[a_eType].m_nStride*a_nCount);
	}

	//-------------------------------------------------------------------------
	const float*
		RHIGetShaderFloat3Default(ERHIShaderFloat3 a_eType)
	{
		return (const float*)s_arrBuildinConstantValue[a_eType];
	}

	//-------------------------------------------------------------------------
	void
		RHISetShaderFloat3Default(ERHIShaderFloat3 a_eType, const float* pVal)
	{
		memcpy(s_arrBuildinConstantValue[a_eType], pVal, s_arrBuildinConstantDecl[a_eType].m_nStride);
	}

	//-------------------------------------------------------------------------
	void
		RHISetShaderFloat3ArrayDefault(ERHIShaderFloat3 a_eType, const float* pVal, int32 a_nCount)
	{
		memcpy(s_arrBuildinConstantValue[a_eType], pVal, s_arrBuildinConstantDecl[a_eType].m_nStride*a_nCount);
	}

	//-------------------------------------------------------------------------
	const float*
		RHIGetShaderFloat2Default(ERHIShaderFloat2 a_eType)
	{
		return (const float*)s_arrBuildinConstantValue[a_eType];
	}

	//-------------------------------------------------------------------------
	void
		RHISetShaderFloat2Default(ERHIShaderFloat2 a_eType, const float* pVal)
	{
		memcpy(s_arrBuildinConstantValue[a_eType], pVal, s_arrBuildinConstantDecl[a_eType].m_nStride);
	}

	//-------------------------------------------------------------------------
	void
		RHISetShaderFloat2ArrayDefault(ERHIShaderFloat2 a_eType, const float* pVal, int32 a_nCount)
	{
		memcpy(s_arrBuildinConstantValue[a_eType], pVal, s_arrBuildinConstantDecl[a_eType].m_nStride*a_nCount);
	}

	//-------------------------------------------------------------------------
	const float*
		RHIGetShaderFloatDefault(ERHIShaderFloat a_eType)
	{
		return (const float*)s_arrBuildinConstantValue[a_eType];
	}

	//-------------------------------------------------------------------------
	void
		RHISetShaderFloatDefault(ERHIShaderFloat a_eType, const float val)
	{
		memcpy(s_arrBuildinConstantValue[a_eType], &val, s_arrBuildinConstantDecl[a_eType].m_nStride);
	}

	//-------------------------------------------------------------------------
	void
		RHISetShaderFloatArrayDefault(ERHIShaderFloat a_eType, const float* pVal, int32 a_nCount)
	{
		memcpy(s_arrBuildinConstantValue[a_eType], pVal, s_arrBuildinConstantDecl[a_eType].m_nStride*a_nCount);
	}

	//-------------------------------------------------------------------------
	const int32*
		RHIGetShaderInt4Default(ERHIShaderInt4 a_eType)
	{
		return (const int32*)s_arrBuildinConstantValue[a_eType];
	}

	//-------------------------------------------------------------------------
	void
		RHISetShaderInt4Default(ERHIShaderInt4 a_eType, const int32* pVal)
	{
		memcpy(s_arrBuildinConstantValue[a_eType], pVal, s_arrBuildinConstantDecl[a_eType].m_nStride);
	}

	//-------------------------------------------------------------------------
	const int32*
		RHIGetShaderInt3Default(ERHIShaderInt3 a_eType)
	{
		return (const int32*)s_arrBuildinConstantValue[a_eType];
	}

	//-------------------------------------------------------------------------
	void
		RHISetShaderInt3Default(ERHIShaderInt3 a_eType, const int32* pVal)
	{
		memcpy(s_arrBuildinConstantValue[a_eType], pVal, s_arrBuildinConstantDecl[a_eType].m_nStride);
	}

	//-------------------------------------------------------------------------
	const int32*
		RHIGetShaderInt2Default(ERHIShaderInt2 a_eType)
	{
		return (const int32*)s_arrBuildinConstantValue[a_eType];
	}

	//-------------------------------------------------------------------------
	void
		RHISetShaderInt2Default(ERHIShaderInt2 a_eType, const int32* pVal)
	{
		memcpy(s_arrBuildinConstantValue[a_eType], pVal, s_arrBuildinConstantDecl[a_eType].m_nStride);
	}

	//-------------------------------------------------------------------------
	const int32*
		RHIGetShaderIntDefault(ERHIShaderInt a_eType)
	{
		return (const int32*)s_arrBuildinConstantValue[a_eType];
	}

	//-------------------------------------------------------------------------
	void
		RHISetShaderIntDefault(ERHIShaderInt a_eType, const int32 val)
	{
		memcpy(s_arrBuildinConstantValue[a_eType], &val, s_arrBuildinConstantDecl[a_eType].m_nStride);
	}

	//-------------------------------------------------------------------------
	const int32*
		RHIGetShaderBool4Default(ERHIShaderBool4 a_eType)
	{
		return (const int32*)s_arrBuildinConstantValue[a_eType];
	}

	//-------------------------------------------------------------------------
	void
		RHISetShaderBool4Default(ERHIShaderBool4 a_eType, const int32* pVal)
	{
		memcpy(s_arrBuildinConstantValue[a_eType], pVal, s_arrBuildinConstantDecl[a_eType].m_nStride);
	}

	//-------------------------------------------------------------------------
	const int32*
		RHIGetShaderBool3Default(ERHIShaderBool3 a_eType)
	{
		return (const int32*)s_arrBuildinConstantValue[a_eType];
	}

	//-------------------------------------------------------------------------
	void
		RHISetShaderBool3Default(ERHIShaderBool3 a_eType, const int32* pVal)
	{
		memcpy(s_arrBuildinConstantValue[a_eType], pVal, s_arrBuildinConstantDecl[a_eType].m_nStride);
	}

	//-------------------------------------------------------------------------
	const int32*
		RHIGetShaderBool2Default(ERHIShaderBool2 a_eType)
	{
		return (const int32*)s_arrBuildinConstantValue[a_eType];
	}

	//-------------------------------------------------------------------------
	void
		RHISetShaderBool2Default(ERHIShaderBool2 a_eType, const int32* pVal)
	{
		memcpy(s_arrBuildinConstantValue[a_eType], pVal, s_arrBuildinConstantDecl[a_eType].m_nStride);
	}

	//-------------------------------------------------------------------------
	const int32*
		RHIGetShaderBoolDefault(ERHIShaderBool a_eType)
	{
		return (const int32*)s_arrBuildinConstantValue[a_eType];
	}

	//-------------------------------------------------------------------------
	void
		RHISetShaderBoolDefault(ERHIShaderBool a_eType, const int32 val)
	{
		memcpy(s_arrBuildinConstantValue[a_eType], &val, s_arrBuildinConstantDecl[a_eType].m_nStride);
	}

	//----------------------------------------
	void 
		RHIDevice::_InitBuildinConstantDecls()
	{
#define DECLARE_SHADER_CONST(type,count,name) \
		decl.m_eType	= type;	\
		decl.m_nCount	= count; \
		decl.m_nHandle	= s_arrBuildinConstantDecl.size(); \
		decl.m_nStride	= RHIGetShaderConstantTypeSize( type ); \
		decl.m_szName	= name; \
		s_mapBuildinConstantNames[name] = decl.m_nHandle; \
		s_arrBuildinConstantDecl.push_back( decl );

		RHIShaderConstantDecl decl;

		DECLARE_SHADER_CONST(ERHIShaderConstantType_Matrix4, 1, "SGF_MATRIX_WORLD");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_Matrix4, 1, "SGF_MATRIX_MODEL");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_Matrix4, 1, "SGF_MATRIX_VIEW");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_Matrix4, 1, "SGF_MATRIX_PROJ");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_Matrix4, 1, "SGF_MATRIX_VIEW_PROJ");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_Matrix4, 1, "SGF_MATRIX_TEX_VIEW_PROJ");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_Matrix4, 1, "SGF_MATRIX_WORLD_VIEW");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_Matrix4, 1, "SGF_MATRIX_WORLD_VIEW_INV");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_Matrix4, 1, "SGF_MATRIX_WORLD_VIEW_PROJ");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_Matrix4, 1, "SGF_MATRIX_WORLD_VIEW_PROJ_INV");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_Matrix4, MAX_MATRIX_ARRAY_COUNT, "SGF_MATRIX_PALETTE");

		DECLARE_SHADER_CONST(ERHIShaderConstantType_4f, 1, "SGF_FLOAT4_LIGHTMAP_TILE");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_4f, 1, "SGF_FLOAT4_LIGHTMAP_FACTOR");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_4f, MAX_POINT_LIGHT_PER_OBJ, "SGF_FLOAT4_POINT_LIGHT_POS");

		DECLARE_SHADER_CONST(ERHIShaderConstantType_3f, 1, "SGF_FLOAT3_CAMERA_EYEAT");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_3f, 1, "SGF_FLOAT3_CAMERA_LOOKAT");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_3f, 1, "SGF_FLOAT3_CAMERA_LOOKUP");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_3f, MAX_POINT_LIGHT_PER_OBJ, "SGF_FLOAT3_POINT_LIGHT_COLOR");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_3f, 1, "SGF_FLOAT3_AMBIENT_LIGHT_COLOR");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_3f, 1, "SGF_FLOAT3_DIR_LIGHT0_COLOR");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_3f, 1, "SGF_FLOAT3_DIR_LIGHT0_DIR");

		DECLARE_SHADER_CONST(ERHIShaderConstantType_1f, 1, "SGF_FLOAT_TIME");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_1f, 1, "SGF_FLOAT_RUNNING_TIME");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_1f, 1, "SGF_FLOAT_RUNNING_TIME_NO_RATE");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_1f, 1, "SGF_FLOAT_ELAPSED");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_1f, 1, "SGF_FLOAT_ELAPSED_NO_RATE");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_1f, 1, "SGF_FLOAT_CAMERA_FOV");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_1f, 1, "SGF_FLOAT_WIDTH_DESIGN");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_1f, 1, "SGF_FLOAT_HEIGHT_DESIGN");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_1f, 1, "SGF_FLOAT_WIDTH_APP");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_1f, 1, "SGF_FLOAT_HEIGHT_APP");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_1f, 1, "SGF_FLOAT_FOG_START");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_1f, 1, "SGF_FLOAT_FOG_END");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_1f, 1, "SGF_FLOAT_FOG_RCPDIFF");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_1f, 1, "SGF_FLOAT_LIGHTING_PROFILE");

		DECLARE_SHADER_CONST(ERHIShaderConstantType_1b, 1, "SGF_BOOL_FOG");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_1b, 1, "SGF_BOOL_SKIN");
		DECLARE_SHADER_CONST(ERHIShaderConstantType_1b, 1, "SGF_BOOL_LIGHTMAP");

#undef DECLARE_SHADER_CONST
		ASSERT(s_arrBuildinConstantDecl.size() == ERHIShaderConstantBuildin_Max);
	}

	//----------------------------------------
	const TArray<RHIShaderConstantDecl>& 
		RHIDevice::_GetBuildinConstantDecls()
	{
		return s_arrBuildinConstantDecl;
	}

	//----------------------------------------
	void 
		RHIDevice::_InitBuildinConstantsFuncs()
	{
		RHIGetShaderConstantDecl = RHIGetShaderConstantDeclDefault;
		RHIGetShaderConstantValue = RHIGetShaderConstantValueDefault;
		RHISetShaderConstantValue = RHISetShaderConstantValueDefault;

		RHIGetShaderMatrix = RHIGetShaderMatrixDefault;
		RHISetShaderMatrix = RHISetShaderMatrixDefault;

		RHIGetShaderMatrixArray = RHIGetShaderMatrixArrayDefault;
		RHISetShaderMatrixArray = RHISetShaderMatrixArrayDefault;

		RHIGetShaderFloat4 = RHIGetShaderFloat4Default;
		RHISetShaderFloat4 = RHISetShaderFloat4Default;
		RHISetShaderFloat4Array = RHISetShaderFloat4ArrayDefault;
		RHIGetShaderFloat3 = RHIGetShaderFloat3Default;
		RHISetShaderFloat3 = RHISetShaderFloat3Default;
		RHISetShaderFloat3Array = RHISetShaderFloat3ArrayDefault;
		RHIGetShaderFloat2 = RHIGetShaderFloat2Default;
		RHISetShaderFloat2 = RHISetShaderFloat2Default;
		RHISetShaderFloat2Array = RHISetShaderFloat2ArrayDefault;
		RHIGetShaderFloat = RHIGetShaderFloatDefault;
		RHISetShaderFloat = RHISetShaderFloatDefault;
		RHISetShaderFloatArray = RHISetShaderFloatArrayDefault;

		RHIGetShaderInt4 = RHIGetShaderInt4Default;
		RHISetShaderInt4 = RHISetShaderInt4Default;
		RHIGetShaderInt3 = RHIGetShaderInt3Default;
		RHISetShaderInt3 = RHISetShaderInt3Default;
		RHIGetShaderInt2 = RHIGetShaderInt2Default;
		RHISetShaderInt2 = RHISetShaderInt2Default;
		RHIGetShaderInt = RHIGetShaderIntDefault;
		RHISetShaderInt = RHISetShaderIntDefault;

		RHIGetShaderBool4 = RHIGetShaderBool4Default;
		RHISetShaderBool4 = RHISetShaderBool4Default;
		RHIGetShaderBool3 = RHIGetShaderBool3Default;
		RHISetShaderBool3 = RHISetShaderBool3Default;
		RHIGetShaderBool2 = RHIGetShaderBool2Default;
		RHISetShaderBool2 = RHISetShaderBool2Default;
		RHIGetShaderBool = RHIGetShaderBoolDefault;
		RHISetShaderBool = RHISetShaderBoolDefault;
	}

	//----------------------------------------
	void 
		RHIDevice::_InitBuildinConstantsValues()
	{
		_FreeBuildinConstantsValues();
		s_arrBuildinConstantValue.resize(s_arrBuildinConstantDecl.size(), NULL);
		for (int32 i = 0; i < s_arrBuildinConstantDecl.size(); i++)
		{
			s_arrBuildinConstantValue[i] = malloc(s_arrBuildinConstantDecl[i].m_nStride*s_arrBuildinConstantDecl[i].m_nCount);
		}
	}

	//----------------------------------------
	void 
		RHIDevice::_FreeBuildinConstantsValues()
	{
		for (int32 i = 0; i < s_arrBuildinConstantValue.size(); i++)
		{
			SAFE_FREE(s_arrBuildinConstantValue[i]);
		}
		s_arrBuildinConstantValue.clear();
	}
}
	
