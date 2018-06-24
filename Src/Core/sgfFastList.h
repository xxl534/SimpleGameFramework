#pragma once
/********************************************************************
	created:	2018/06/24
	created:	24:6:2018   8:46
	filename: 	E:\SimpleGameFramework\Src\Core\sgfFastList.h
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfFastList
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/
#include "sgfArray.h"
namespace sgf
{
	template<typename T> 
	class TFastList
	{
	public:
		struct Node
		{
			INLINE Node() {}
			INLINE Node(const Node& a_rhs) :m_Data(a_rhs.m_Data), m_pPrev(a_rhs.m_pPrev), m_pNext(a_rhs.m_pNext) {}
			INLINE Node(const T& a_val) : m_Data(a_val) {}
			T		m_Data;
			Node*	m_pPrev;
			Node*	m_pNext;
		};

		struct MemoryBlock
		{
			INLINE MemoryBlock() {}
			INLINE MemoryBlock(void* a_ptr, int a_nSize) :m_pMemoryBlock(a_ptr), m_nMemorySize(a_nSize) {}
			void*	m_pMemoryBlock;
			int		m_nMemorySize;
		};

		class iterator
		{
			friend class TFastList;
		public:
			INLINE iterator() {}
			INLINE iterator(const iterator& a_it) :m_pNode(a_it.m_pNode) {}
			INLINE iterator(Node* a_pNode) : m_pNode(a_pNode) {}
			INLINE bool			operator==(const iterator& a_rhs) const { return m_pNode == a_rhs.m_pNode; }
			INLINE bool			operator!=(const iterator& a_rhs) const { return m_pNode != a_rhs.m_pNode; }
			INLINE iterator&	operator++() { assert(m_pNode); m_pNode = m_pNode->m_pNext; return *this; }
			INLINE iterator		operator++(int) { assert(m_pNode); m_pNode = m_pNode->m_pNext; return iterator(m_pNode->m_pPrev); }
			INLINE iterator&	operator--() { assert(m_pNode); m_pNode = m_pNode->m_pPrev; return *this; }
			INLINE iterator		operator--(int) { assert(m_pNode); m_pNode = m_pNode->m_pPrev; return iterator(m_pNode->m_pNext); }
			INLINE T&			operator *() { assert(m_pNode); return m_pNode->m_Data; }
			INLINE T*			operator->() { assert(m_pNode); return &(m_pNode->m_Data); }
			INLINE void			next() { assert(m_pNode); m_pNode = m_pNode->m_pNext; }
			INLINE void			prev() { assert(m_pNode); m_pNode = m_pNode->m_pPrev; }
		private:
			Node*				m_pNode;
		};

		class const_iterator
		{
			friend class TFastList;
		public:
			INLINE const_iterator() {}
			INLINE const_iterator(const const_iterator& a_it) :m_pNode(a_it.m_pNode) {}
			INLINE const_iterator(const Node* a_pNode) : m_pNode(a_pNode) {}
			INLINE bool				operator==(const const_iterator& a_rhs) const { return m_pNode == a_rhs.m_pNode; }
			INLINE bool				operator!=(const const_iterator& a_rhs) const { return m_pNode != a_rhs.m_pNode; }
			INLINE const_iterator&	operator++() { assert(m_pNode); m_pNode = m_pNode->m_pNext; return *this; }
			INLINE const_iterator	operator++(int) { assert(m_pNode); m_pNode = m_pNode->m_pNext; return const_iterator(m_pNode->m_pPrev); }
			INLINE const_iterator&	operator--() { assert(m_pNode); m_pNode = m_pNode->m_pPrev; return *this; }
			INLINE const_iterator	operator--(int) { assert(m_pNode); m_pNode = m_pNode->m_pPrev; return const_iterator(m_pNode->m_pNext); }
			INLINE const T&			operator *() { assert(m_pNode); return m_pNode->m_Data; }
			INLINE const T*			operator->() { assert(m_pNode); return &(m_pNode->m_Data); }
			INLINE void				next() { assert(m_pNode); m_pNode = m_pNode->m_pNext; }
			INLINE void				prev() { assert(m_pNode); m_pNode = m_pNode->m_pPrev; }
		private:
			const Node*					m_pNode;
		};

		class reverse_iterator
		{
			friend class TFastList;
		public:
			INLINE reverse_iterator() {}
			INLINE reverse_iterator(const reverse_iterator& a_it) :m_pNode(a_it.m_pNode) {}
			INLINE reverse_iterator(Node* a_pNode) : m_pNode(a_pNode) {}
			INLINE bool					operator==(const reverse_iterator& a_rhs) const { return m_pNode == a_rhs.m_pNode; }
			INLINE bool					operator!=(const reverse_iterator& a_rhs) const { return m_pNode != a_rhs.m_pNode; }
			INLINE reverse_iterator&	operator++() { assert(m_pNode); m_pNode = m_pNode->m_pPrev; return *this; }
			INLINE reverse_iterator		operator++(int) { assert(m_pNode); m_pNode = m_pNode->m_pPrev; return reverse_iterator(m_pNode->m_pNext); }
			INLINE reverse_iterator&	operator--() { assert(m_pNode); m_pNode = m_pNode->m_pNext; return *this; }
			INLINE reverse_iterator		operator--(int) { assert(m_pNode); m_pNode = m_pNode->m_pNext; return reverse_iterator(m_pNode->m_pPrev); }
			INLINE T&					operator *() { assert(m_pNode); return m_pNode->m_Data; }
			INLINE T*					operator->() { assert(m_pNode); return &(m_pNode->m_Data); }
			INLINE void					next() { assert(m_pNode); m_pNode = m_pNode->m_pPrev; }
			INLINE void					prev() { assert(m_pNode); m_pNode = m_pNode->m_pNext; }
		private:
			Node*						m_pNode;
		};

		class const_reverse_iterator
		{
			friend class TFastList;
		public:
			INLINE const_reverse_iterator() {}
			INLINE const_reverse_iterator(const const_reverse_iterator& a_it) :m_pNode(a_it.m_pNode) {}
			INLINE const_reverse_iterator(const Node* a_pNode) : m_pNode(a_pNode) {}
			INLINE bool						operator==(const const_reverse_iterator& a_rhs) const { return m_pNode == a_rhs.m_pNode; }
			INLINE bool						operator!=(const const_reverse_iterator& a_rhs) const { return m_pNode != a_rhs.m_pNode; }
			INLINE const_reverse_iterator&	operator++() { assert(m_pNode); m_pNode = m_pNode->m_pPrev; return *this; }
			INLINE const_reverse_iterator	operator++(int) { assert(m_pNode); m_pNode = m_pNode->m_pPrev; return const_reverse_iterator(m_pNode->m_pNext); }
			INLINE const_reverse_iterator&	operator--() { assert(m_pNode); m_pNode = m_pNode->m_pNext; return *this; }
			INLINE const_reverse_iterator	operator--(int) { assert(m_pNode); m_pNode = m_pNode->m_pNext; return const_reverse_iterator(m_pNode->m_pPrev); }
			INLINE const T&					operator *() const { assert(m_pNode); return m_pNode->m_Data; }
			INLINE const T*					operator->() const { assert(m_pNode); return &(m_pNode->m_Data); }
			INLINE void						next() { assert(m_pNode); m_pNode = m_pNode->m_pPrev; }
			INLINE void						prev() { assert(m_pNode); m_pNode = m_pNode->m_pNext; }
		private:
			const Node*							m_pNode;
		};

	public:
		TFastList();
		TFastList(const TFastList<T>& a_rhs);
		~TFastList();

		void					operator=(const TFastList<T> a_rhs);
		bool					operator==(const TFastList<T> a_rhs) const;
		bool					operator!=(const TFastList<T> a_rhs) const;

		T&						front();
		const T&				front() const;
		T&						back();
		const T&				back() const;

		void					push_back(const T& a_val);
		void					pop_back();
		void					push_front(const T& a_val);
		void					pop_front();

		iterator				begin();
		const_iterator			begin() const;
		iterator				end();
		const_iterator			end() const;
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;

		iterator				insert(iterator a_itWhere, const T& a_val);
		void					remove(iterator a_itWhere);
		iterator				remove_return_next(iterator a_itWhere);		//custom function
		reverse_iterator		insert(reverse_iterator a_itWhere, const T& a_val);
		void					remove(reverse_iterator a_itWhere);
		reverse_iterator		remove_return_next(reverse_iterator a_itWhere);
		void					remove(const T& a_val);

		iterator				find(const T& a_val);						//custom function
		const_iterator			find(const T& a_val) const;				//custom function
		iterator				find(const T& a_val, iterator a_it);						//custom function
		const_iterator			find(const T& a_val, const_iterator a_it) const;
		reverse_iterator		rfind(const T& a_val);						//custom function
		const_reverse_iterator	rfind(const T& a_val) const;				//custom function
		reverse_iterator		rfind(const T& a_val, reverse_iterator a_it);						//custom function
		const_reverse_iterator	rfind(const T& a_val, const_reverse_iterator a_it) const;


		//custom function
		bool					empty() const;
		int						size() const;
		void					clear();
		void					swap(TFastList<T>& a_rhs);
		void					to_array(T** a_outArray) const;

	protected:
		void					_init(int a_nCapacity);
		void					_assign(const_iterator a_beginNode, const_iterator a_endNode);
		Node*					_alloc_node(const T& a_val);
		void					_free_node(Node* a_pNode);

	protected:
		Node*					m_pHead;
		int						m_nSize;
		//use to pre malloc memory
		TArray<Node*, false, false>			m_arrFreeNode;
		TArray<MemoryBlock, false, false>	m_arrMemoryBlock;
	};
}
#define FASTLIST_INCREASE_STEP		20
#include "sgfFastList.inl"