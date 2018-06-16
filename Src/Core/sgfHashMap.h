#pragma once

/********************************************************************
	created:	2018/06/13
	created:	13:6:2018   8:41
	filename: 	E:\SimpleGameFramework\Src\Core\sgfHashMap.h
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfHashMap
	file ext:	h
	author:		xiexuelong
	
	purpose:	
*********************************************************************/
#include "sgfArray.h"

namespace sgf
{
	template<typename K,typename V>
	class THashMap
	{
	public:
		struct Pair
		{
			INLINE Pair() {}
			INLINE Pair(const K& a_k, const V& a_v) :first(a_k), second(a_v) {}
			K				first;
			V				second;
			int				m_nHashNext;
		};

		class iterator
		{
		public:
			INLINE iterator(TArray<Pair>& a_arrPair, int a_nIdx) :m_arrPair(a_arrPair), m_nIndex(a_nIdx) {}
			Pair&					operator* ();
			Pair*					operator->();
			iterator&				operator++();
			iterator				operator++(int);
			iterator&				operator--();
			iterator				operator--(int);
			bool					operator==(const iterator& a_rhs) const;
			bool					operator!=(const iterator& a_rhs) const;
									operator bool() const;
			const K&				key() const;
			V&						value();
		private:
			TArray<Pair>&		m_arrPair;
			int					m_nIndex;
		};

		class const_iterator
		{
		public:
			INLINE const_iterator(const TArray<Pair>& a_arrPair, int a_nIndex) :m_arrPair(a_arrPair), m_nIndex(a_nIndex) {}
			const Pair&				operator* () const;
			const Pair*				operator->() const;
			const_iterator&			operator++();
			const_iterator			operator++(int);
			const_iterator&			operator--();
			const_iterator			operator--(int);
			bool					operator==(const const_iterator& a_rhs) const;
			bool					operator!=(const const_iterator& a_rhs) const;
			operator bool() const;
			const K&				key() const;
			const V&				value() const;
		protected:
			const TArray<Pair>&		m_arrPair;
			int						m_nIndex;
		};

		class reverse_iterator
		{
		public:
			INLINE reverse_iterator(TArray<Pair>& a_arrPair, int a_nIndex) :m_arrPair(a_arrPair), m_nIndex(a_nIndex) {}
			Pair&					operator* ();
			Pair*					operator->();
			reverse_iterator&		operator++();
			reverse_iterator		operator++(int);
			reverse_iterator&		operator--();
			reverse_iterator		operator--(int);
			bool					operator==(const reverse_iterator& a_rhs) const;
			bool					operator!=(const reverse_iterator& a_rhs) const;
			operator bool() const;
			const K&				key() const;
			V&						value();
		protected:
			TArray<Pair>&			m_arrPair;
			int						m_nIndex;
		};

		class const_reverse_iterator
		{
		public:
			INLINE const_reverse_iterator(const TArray<Pair>& a_arrPair, int a_nIndex) :m_arrPair(a_arrPair), m_nIndex(a_nIndex) {}
			const Pair&				operator* () const;
			const Pair*				operator->() const;
			const_reverse_iterator&	operator++();
			const_reverse_iterator	operator++(int);
			const_reverse_iterator&	operator--();
			const_reverse_iterator	operator--(int);
			bool					operator==(const const_reverse_iterator& a_rhs) const;
			bool					operator!=(const const_reverse_iterator& a_rhs) const;
			operator bool() const;
			const K&				key() const;
			const V&				value() const;
		protected:
			const TArray<Pair>&		m_arrPair;
			int						m_nIndex;
		};

	public:
		THashMap();
		THashMap(int a_nCapacity);
		THashMap(const THashMap<K, V>& a_rhs);
		~THashMap();

		iterator				begin();
		const_iterator			begin() const;
		iterator				end();
		const_iterator			end() const;
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;

		void					clear();
		int						count(const K& k) const;	//consist to stl, return 1 if exist, otherwise return 0
		bool					hasKey(const K& k) const;
		bool					empty() const;

		void					set(const K& a_k, const V& a_v);
		void					insert(const K& a_k, const V& a_v);
		V&						operator[](const K& a_k);
		const V&				operator[](const K& a_k) const;
		void					operator=(const THashMap<K, V>& a_rhs);
		V*						findValue(const K& a_k);
		const V*				findValue(const K& a_k) const;
		const K*				findKey(const V& a_v, const K* a_pStart = NULL) const;
		void					remove(const K& a_k);

		void					erase(iterator a_itor);
		void					erase(iterator a_itorFrom, iterator a_itorTo);

		iterator				find(const K& a_k);
		const_iterator			find(const K& a_k) const;

		int						size() const;
		void					swap(THashMap<K, V>& a_rhs);
	private:
		void					_rehash();
		int						_findIndex(const K& a_k) const;
		void					_add(const K& a_k, const V& a_v);
		void					_relax();
	private:
		int						m_nHashCount;
		int*					m_arrHashIdx;
		TArray<Pair>			m_arrPair;
	};

}
#define HASH_INDEX_NONE	-1
#define HASH_REHASH_FACTOR 1.2

#include "sgfHashMap.inl"