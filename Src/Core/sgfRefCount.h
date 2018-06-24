#pragma once
/********************************************************************
	created:	2018/06/24
	created:	24:6:2018   7:25
	filename: 	E:\SimpleGameFramework\Src\Core\sgfRefCount.h
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfRefCount
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	class TRefCountedObject
	{
	public:
		TRefCountedObject():m_nRefCount(0){}
		virtual ~TRefCountedObject();
		int32 AddRef() const
		{
			return ++m_nRefCount;
		}
		int32 Release() const
		{
			int32 nRefs = --m_nRefCount;
			if (nRefs == 0)
			{
				delete this;
			}
			return nRefs;
		}
		int32 GetRefCount() const
		{
			return m_nRefCount;
		}
	private:
		mutable int32	m_nRefCount;
	};

	template<typename RefType>
	class TRefCountPtr
	{
		typedef RefType* RefPtr;
	public:
		TRefCountPtr():m_pRef(NULL){}

		TRefCountPtr(RefType* a_pRef, bool a_bAddRef = true)
			:m_pRef( a_pRef )
		{
			if (m_pRef && a_bAddRef)
			{
				m_pRef->AddRef();
			}
		}

		template<typename T> explicit TRefCountPtr(T* a_pRef, bool a_bAddRef = true)
			:m_pRef(a_pRef)
		{
			if (m_pRef && a_bAddRef)
			{
				m_pRef->AddRef();
			}
		}

		TRefCountPtr(const TRefCountPtr& a_rhs)
			:m_pRef( a_rhs.m_pRef)
		{
			if (m_pRef)
			{
				m_pRef->AddRef();
			}
		}

		template<typename T> explicit TRefCountPtr(const TRefCountPtr<T>& a_rhs)
		{
			m_pRef = a_rhs.GetReference();
			if (m_pRef)
			{
				m_pRef->AddRef();
			}
		}

		~TRefCountPtr()
		{
			if( m_pRef )
			{
				m_pRef->Release();
			}
		}

		TRefCountPtr& operator=(RefType* a_pRef)
		{
			RefType* pOldRef = m_pRef;
			m_pRef = a_pRef;
			if( m_pRef )
			{
				m_pRef->AddRef();
			}
			if (pOldRef)
			{
				pOldRef->Release();
			}
			return *this;
		}

		TRefCountPtr& operator=(const TRefCountPtr& a_rhs)
		{
			return this->operator=(a_rhs.m_pRef);
		}

		bool operator==(RefType* a_pRhs) const
		{
			return m_pRef == a_pRhs;
		}

		template<typename T> bool operator==(T* a_pRhs) const
		{
			return m_pRef == a_pRhs;
		}

		bool operator!=(RefType* a_pRhs) const
		{
			return m_pRef != a_pRhs;
		}

		template<typename T> bool operator!=(T* a_pRhs) const
		{
			return m_pRef != a_pRhs;
		}

		RefType* operator->() const
		{
			return m_pRef;
		}

		operator RefPtr() const
		{
			return m_pRef;
		}

		RefType* GetReference() const
		{
			return m_pRef;
		}

		template<typename T>
		T* GetReference() const
		{
			return static_cast<T*>(m_pRef);
		}

		bool IsValidRef() const
		{
			return m_pRef != NULL;
		}

		void SafeRelease()
		{
			this->operator=(NULL);
		}

		int GetRefCount()
		{
			if (m_pRef)
			{
				return m_pRef->GetRefCount();
			}
			else
			{
				return 0;
			}
		}
	private:
		RefType* m_pRef;
	};
}