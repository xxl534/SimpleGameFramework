#pragma once

/********************************************************************
	created:	2018/06/13
	created:	13:6:2018   8:43
	filename: 	E:\SimpleGameFramework\Src\Core\sgfArray.h
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfArray
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	template<typename T, bool NeedCtor = true, bool NeedDtor = true, int alignment = ALIGNMENT_DEFAULT >
	class TArray
	{
	public:
		typedef T*			iterator;
		typedef const T*	const_iterator;
		typedef T			value_type;
	public:
		TArray();
		TArray(const TArray<T, NeedCtor, NeedDtor, alignment>& a_rhs);
		TArray(int a_nCapacity);
		TArray(int a_nSize, const T& a_Default);
		TArray(int a_nSize, const T& a_Default, int a_nCapacity);
		~TArray();

		T&			operator[](int a_nIdx);
		const T&	operator[](int a_nIdx) const;
		void		operator=(const TArray<T, NeedCtor, NeedDtor, alignment>& a_rhs);
		bool		operator==(const TArray<T, NeedCtor, NeedDtor, alignment>& a_rhs) const;
		bool		operator!=(const TArray<T, NeedCtor, NeedDtor, alignment>& a_rhs) const;

		int			size() const;
		void		resize(int a_nSize);
		void		resize(int a_nSize, const T& a_Default);
		int			capacity() const;
		int			get_reserve() const;
		void		reserve(int a_nReserveSize);

		void		swap(TArray<T, NeedCtor, NeedDtor, alignment>& a_rhs);
		void		push_back(const T& a_rhs);
		void		pop_back();
		void		swap_back(int a_nIdx);
		
		bool		empty() const;
		void		clear();
		void		trim();

		iterator	find(const T& a_val);
		const_iterator	find(const T& a_val) const;

		int			find_index(const T& a_val) const;

		void		insert(int a_nIdx, const T& a_val);
		void		insert(iterator a_itor, const T& a_val);
		void		insert(int a_nIdx, const T& a_val, int a_nCount);
		void		insert(iterator a_itor, const T& a_val, int a_nCount);
		void		insert(int a_nIdx, const TArray<T, NeedCtor, NeedDtor, alignment>& a_arr);
		void		insert(iterator a_itor, const TArray<T, NeedCtor, NeedDtor, alignment>& a_arr);
		void		insert(int a_nIdx, const T* a_arr, int a_nLen);
		void		insert(iterator a_itor, const T* a_arr, int a_nLen);
		void		erase(int a_nIdx, int a_nCount = 1);
		void		erase(iterator a_where);
		void		erase(iterator a_itorStart, iterator a_itorEnd);

		iterator	begin();
		const_iterator	begin() const;
		iterator	end();
		const_iterator	end() const;

		T&			front();
		const T&	front() const;
		T&			back();
		const T&	back() const;

		void		to_array(T** out_pArray) const;
	private:
		void		_copy(const TArray<T, NeedCtor, NeedDtor, alignment>& a_rhs);
		void		_cleanup();
		void		_realloc(int a_nCapacity);
		void		_set_capacity(int a_nCapacity);
		void		_grow(int a_nMinSize = -1);
		void		_move(int a_nFrom, int a_nTo);
	private:
		int			m_nSize;
		int			m_nCapacity;
		T*			m_pData;
	};

}
#define ALIGN_MALLOC(a,b) malloc(a)
#define	ALIGN_FREE(a) free(a)
#include "sgfArray.inl"