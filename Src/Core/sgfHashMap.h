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
			int				m_hashNext;
		};

		class iterator
		{

		};

		class const_iterator
		{
		};

		class reverse_iterator
		{};

		class const_reverse_iterator
		{};
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
		int						m_nHashCount;
		int*					m_pHash;
		TArray<Pair>			m_arrPair;
	};

}

#include "sgfHashMap.inl"