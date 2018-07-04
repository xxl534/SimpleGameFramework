#pragma once
/********************************************************************
	created:	2018/07/04
	created:	4:7:2018   9:10
	filename: 	E:\SimpleGameFramework\Src\Core\sgfHashSet.h
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfHashSet
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/
#include "sgfArray.h"
#include "sgfHashMap.h"

namespace sgf
{
	template<typename T>
	class THashSet
	{
	public:
		struct Value
		{
			INLINE Value() {}
			INLINE Value(const T& a_v) :m_value(a_v) {}
			T		m_value;
			int		m_nHashNext;
		};

		class iterator
		{
			friend class THashSet;
		public:
			INLINE iterator(TArray<Value>& a_arrData, int a_nIndex) :m_arrData(a_arrData), m_nIndex(a_nIndex) {}
			INLINE T&				operator* () { return m_arrData[m_nIndex].m_value; }
			INLINE T*				operator->() { return &(m_arrData[m_nIndex].m_value); }
			INLINE iterator&		operator++() { m_nIndex++; return *this; }
			INLINE iterator			operator++(int) { return iterator(m_arrData, m_nIndex++); }
			INLINE iterator&		operator--() { m_nIndex--; return *this; }
			INLINE iterator			operator--(int) { return iterator(m_arrData, m_nIndex--); }
			INLINE bool				operator==(const iterator& a_rhs) const { return &m_arrData == &a_rhs.m_arrData&&m_nIndex == a_rhs.m_nIndex; }
			INLINE bool				operator!=(const iterator& a_rhs) const { return !((*this) == a_rhs); }
			INLINE operator bool() const { return m_nIndex >= 0 && m_nIndex < m_arrData.size(); }
		protected:
			TArray<Value>&			m_arrData;
			int						m_nIndex;
		};

		class const_iterator
		{
			friend class THashSet;
		public:
			INLINE const_iterator(const TArray<Value>& a_arrData, int a_nIndex) :m_arrData(a_arrData), m_nIndex(a_nIndex) {}
			INLINE const T&			operator* () { return m_arrData[m_nIndex].m_value; }
			INLINE const T*			operator->() { return &(m_arrData[m_nIndex].m_value); }
			INLINE const_iterator&	operator++() { m_nIndex++; return *this; }
			INLINE const_iterator	operator++(int) { return iterator(m_arrData, m_nIndex++); }
			INLINE const_iterator&	operator--() { m_nIndex--; return *this; }
			INLINE const_iterator	operator--(int) { return iterator(m_arrData, m_nIndex--); }
			INLINE bool				operator==(const const_iterator& a_rhs) const { return &m_arrData == &a_rhs.m_arrData&&m_nIndex == a_rhs.m_nIndex; }
			INLINE bool				operator!=(const const_iterator& a_rhs) const { return !((*this) == a_rhs); }
			INLINE operator bool() const { return m_nIndex >= 0 && m_nIndex < m_arrData.size(); }
		protected:
			const TArray<Value>&	m_arrData;
			int						m_nIndex;
		};
		class reverse_iterator
		{
			friend class THashSet;
		public:
			INLINE reverse_iterator(TArray<Value>& a_arrData, int a_nIndex) :m_arrData(a_arrData), m_nIndex(a_nIndex) {}
			INLINE T&				operator* () { return m_arrData[m_nIndex].m_value; }
			INLINE T*				operator->() { return &(m_arrData[m_nIndex].m_value); }
			INLINE reverse_iterator&	operator++() { m_nIndex--; return *this; }
			INLINE reverse_iterator		operator++(int) { return iterator(m_arrData, m_nIndex--); }
			INLINE reverse_iterator&	operator--() { m_nIndex++; return *this; }
			INLINE reverse_iterator		operator--(int) { return iterator(m_arrData, m_nIndex++); }
			INLINE bool				operator==(const reverse_iterator& a_rhs) const { return &m_arrData == &a_rhs.m_arrData&&m_nIndex == a_rhs.m_nIndex; }
			INLINE bool				operator!=(const reverse_iterator& a_rhs) const { return !((*this) == a_rhs); }
			INLINE operator bool() const { return m_nIndex >= 0 && m_nIndex < m_arrData.size(); }
		protected:
			TArray<Value>&			m_arrData;
			int						m_nIndex;
		};
		class const_reverse_iterator
		{
			friend class THashSet;
		public:
			INLINE const_reverse_iterator(const TArray<Value>& a_arrData, int a_nIndex) :m_arrData(a_arrData), m_nIndex(a_nIndex) {}
			INLINE const T&			operator* () { return m_arrData[m_nIndex].m_value; }
			INLINE const T*			operator->() { return &(m_arrData[m_nIndex].m_value); }
			INLINE const_reverse_iterator&	operator++() { m_nIndex--; return *this; }
			INLINE const_reverse_iterator	operator++(int) { return iterator(m_arrData, m_nIndex--); }
			INLINE const_reverse_iterator&	operator--() { m_nIndex++; return *this; }
			INLINE const_reverse_iterator	operator--(int) { return iterator(m_arrData, m_nIndex++); }
			INLINE bool				operator==(const const_reverse_iterator& a_rhs) const { return &m_arrData == &a_rhs.m_arrData&&m_nIndex == a_rhs.m_nIndex; }
			INLINE bool				operator!=(const const_reverse_iterator& a_rhs) const { return !((*this) == a_rhs); }
			INLINE operator bool() const { return m_nIndex >= 0 && m_nIndex < m_arrData.size(); }
		protected:
			const TArray<Value>&	m_arrData;
			int						m_nIndex;
		};

	public:
		THashSet();
		THashSet(int a_nCapacity);
		THashSet(const THashSet<T>& a_rhs);
		~THashSet();

		iterator					begin();
		const_iterator				begin() const;
		iterator					end();
		const_iterator				end() const;
		reverse_iterator			rbegin();
		const_reverse_iterator		rbegin() const;
		reverse_iterator			rend();
		const_reverse_iterator		rend() const;

		void						clear();
		bool						has(const T& a_value) const;		//same to count,my define
		bool						empty() const;
		void						insert(const T& a_value);

		void						erase(const T& a_value);
		void						erase(iterator a_itWhere);
		iterator					find(const T& a_value);
		const_iterator				find(const T& a_value) const;

		int							size() const;
		void						swap(THashSet<T>& a_rhs);

		void						operator =(const THashSet<T>& a_rhs);
	protected:
		void						_rehash();
		int							_findIndex(const T& a_value) const;
		void						_add(const T& a_value);
		void						_relax();

	protected:
		int				m_nHashCount;
		int*			m_arrHashIdx;
		TArray<Value>	m_arrData;
	};
}

#include "sgfHashSet.inl"