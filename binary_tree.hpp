#pragma once

#include <iostream>
#include <memory>
#include <__tree>
#include "map.hpp"
#include "tree_algorithm.hpp"
#include "utils.hpp"
#include <map>
namespace ft
{


	template <class _Tp, class Node, class _Compare, class _Allocator> class __tree;
	template <class _Tp, class Iterator, class _DiffType, class Node> class tree_iterator;
	template <class _Tp, class Iterator, class _DiffType, class Node> class const_tree_iterator;
	template <class T> class Node;
		
	// /**********************  STRUTTURA NODI **********************/
	
	template <class T> //std::pair <T1, T2 
	class Node {
		public:
			//ft::pair<T1, T2> _pair
			T pair;
			// T1 first;
			// T2 second;
			class Node *left, *right;
			class Node *parent;
			bool is_black;
			Node(): left(nullptr), right(nullptr), parent(nullptr), is_black(true)
			{
				// first = NULL;
				// second = NULL;
				// left = nullptr;
				// right = nullptr;
				// parent = nullptr;
				// is_black = true;
			}
			Node(T _pair) : pair(_pair), left(nullptr), right(nullptr), parent(nullptr), is_black(true)
			{
				// left = nullptr;
				// right = nullptr;
				// is_black = true;
				// parent = nullptr;
			}
			~Node(){}

	};


	template <class _Key, class _Tp>
	struct __value_type
	{
			typedef _Key                                     key_type;
			typedef _Tp                                      mapped_type;
			typedef pair<const key_type, mapped_type>        value_type;

		private:
			value_type __cc;

		public:
			value_type& __get_value() { return __cc; }
			const value_type& __get_value() const { return __cc; }

		private:
			__value_type();
			__value_type(__value_type const&);
			__value_type& operator=(__value_type const&);
			~__value_type();
	};




/******************************** CLASSE TREE ********************************/

template <class _Tp, class Node, class _Compare, class Allocator >
class __tree
{
public:
    typedef _Tp                                     	value_type;
	typedef Node										_Node;
    typedef _Compare                                 	value_compare;
    typedef Allocator                               	allocator_type;
    typedef typename allocator_type::pointer         	pointer;
    typedef typename allocator_type::const_pointer   	const_pointer;
    typedef typename allocator_type::size_type       	size_type;
    typedef typename allocator_type::difference_type 	difference_type;
    typedef ft::tree_iterator<value_type, pointer, difference_type, _Node>            			iterator;
    typedef ft::const_tree_iterator<value_type, const_pointer, difference_type, _Node> 		const_iterator;




private:
    pointer           	begin_node; //punta sempre alla chiave piú piccola
	_Node*				end_node;
	Allocator			__alloc;
	size_type			__size;
	value_compare		__value_compare;

public:
    Node* 	__end_node() { return end_node; }
    Allocator& __node_alloc() {return __alloc; }
    const Allocator& __node_alloc() const {return __alloc;}
          iterator __begin_node() {return (iterator)begin_node;}
    const iterator& __begin_node() const {return (const_iterator)begin_node;}
          size_type& size() { return __size; }
    const size_type& size() const { return __size; }
          value_compare& value_comp() { return __value_compare; }
    const value_compare& value_comp() const { return __value_compare; }
    _Node* __root() const { return end_node->left; }
	__tree() : __size(0)
	{
		_Node* a;
		a = __alloc.allocate(1);
		end_node = a;
		begin_node =  __end_node();
	}
    explicit __tree(const value_compare& __comp) : __size(0), __value_compare(__comp)
	{
		begin_node = __end_node();
	}
    explicit __tree(const allocator_type& __a) : __alloc(__a), __size(0)
	{
		begin_node = __end_node();
	}
    __tree(const value_compare& __comp, const allocator_type& __a) : __alloc(__a), __size(0), __value_compare(__comp)
	{
    	begin_node = __end_node();
	}
    __tree(const __tree& __t) { *this = __t; }
    __tree& operator=(const __tree& __t){
		if (this != &__t)
		{
			__value_compare = __t.value_compare();
			if (__alloc != __t.__alloc)
				clear();
			else
				__alloc = __t.__alloc;
			end_node = __t.end_node;
			begin_node = __t.begin_node;
			__size = __t.__size;
		}
	}
    ~__tree() {}

          iterator begin()  {return       iterator(begin_node);}
    const_iterator begin() const {return const_iterator(begin_node);}
          iterator end() {return      iterator(__end_node());}
    const_iterator end() const {return const_iterator(__end_node());}

    size_type max_size() const { return __alloc.max_size(); }

    void clear(){
		__alloc.destroy(__root());
		__size = 0;
		__begin_node() = __end_node();
		end_node->left = nullptr;
	}

    void swap(__tree& __t){
    	std::swap(begin_node, __t.begin_node);
    	std::swap(end_node, __t.end_node);
    	std::swap(__alloc, __t.__alloc);
    	std::swap(__size, __t.__size);
		std::swap(__value_compare, __t.__value_compare);
    	if (size() == 0)
			__begin_node() = __end_node();
		else
			__end_node()->left->parent = static_cast<pointer>(__end_node());
		if (__t.size() == 0)
			__t.__begin_node() = __t.__end_node();
		else
			__t.__end_node()->left->parent = static_cast<pointer>(__t.__end_node());
	}
    void erase(const_iterator __p){
		pointer __np = __p.__get_np();
		iterator __r = __remove_node_pointer(__np);
		Allocator& __na = __node_alloc();
		__alloc.destroy(__na, __get_ptr(const_cast<pointer>(*__p)));
		__alloc.deallocate(__na, __np, 1);
	}

    void erase(const_iterator __f, const_iterator __l){
		while (__f != __l)
			__f = erase(__f);

	}

	template <class _Key>
	size_type erase(const _Key& __k)
	{
		ft::pair<iterator, iterator> __p = __equal_range_multi(__k); // da cambiare!!
		size_type __r = 0;
		for (; __p.first != __p.second; ++__r)
			__p.first = erase(__p.first);
		return __r;
	}

	ft::pair<iterator, bool> insert( const value_type& value )
	{
		pointer _root = __root();
		pointer x = nullptr;
		pointer newnode = nullptr;
		bool inserted = false;
		if (_root != nullptr) //se root esiste
		{
			x = _root;//puntiamo x a root
			while (true)
			{
				if (value_comp()(value, x->pair)) //se la key é minore della root
				{
					if (x->left != nullptr) //se esiste un figlio di sinistra
						x = x->left;//ci spostiamo
					else{
						newnode = x->left;
						newnode = __alloc.allocate(sizeof(_Node)); 
						__alloc.construct(newnode, _Node(value));
						newnode->parent = x;
						x->left = newnode;
						inserted = true;
						break ;
					}
				}
				else if (value_comp()(x->pair, value))
				{
					if (x->right != nullptr)
						x = x->right;
					else
					{
						newnode = x->right;
						newnode = __alloc.allocate(sizeof(_Node)); 
						__alloc.construct(newnode, _Node(value));
						newnode->parent = x;
						x->right = newnode;
						inserted = true;
						break ;
					}
				}
				else//se troviamo un'uguaglianza sostituiamo il data
				{
					newnode = x;
					newnode->pair.second = value.second;
					break ;
				}
			}
		}
		else
		{
			newnode = _root;
			newnode = __alloc.allocate(sizeof(_Node)); 
			__alloc.construct(newnode, _Node(value));
			end_node->left = newnode;
			newnode->parent = end_node;
			newnode->is_black = true;
		}
		if (begin_node->left != nullptr)
			begin_node = begin_node->left;
		balance_after_insert(__root(), newnode);
		__size++;
		pointer r = newnode;
		ft::pair<iterator,bool> miao;
		return ft::pair<iterator,bool>((iterator)r, inserted);
	}


	iterator insert( iterator hint, const value_type& value )
	{
		ft::pair<iterator, bool> miao;
		pointer newnode = nullptr;
		if(value_comp()(value, *hint)) // se la nuova key é minore della key nell'iteratore consigliato
		{
			if (hint.base()->left == nullptr) // e non ha figli di sinistra
			{
				newnode = __alloc.allocate(sizeof(_Node));
				__alloc.construct(newnode, _Node(value));
				hint.base()->left = newnode;
				newnode->parent = hint.base();
				__size++;
				balance_after_insert(__root(), newnode);
				return (iterator)newnode;
			}
			else
				miao = insert(value);
		}
		else
		{
			if (hint.base()->right == nullptr) // e non ha figli di sinistra
			{
				newnode = __alloc.allocate(sizeof(_Node));
				__alloc.construct(newnode, _Node(value));
				hint.base()->right = newnode;
				newnode->parent = hint.base();
				__size++;
				balance_after_insert(__root(), newnode);
				return (iterator)newnode;
			}
			else
				miao = insert(value);
		}
		return (miao.first);
	//}
		// pointer	__parent;
		// pointer __dummy;
		// pointer& __child = __find_equal(hint, __parent, __dummy, value);
		// pointer __r = static_cast<pointer>(__child);
		// if (__child == nullptr)
		// {
		// 	__child = __alloc.allocate(sizeof(_Node)); 
		// 	__alloc.construct(__child, _Node(value));
		// 	__child->parent = __parent;
			
		// 	// _Node *a = NULL;
		// 	// __alloc.construct(a, value);

		// 	//__r = __alloc.allocate(1);
		// 	//Node *a(value);
		// 	//a = __r;
		// 	//a.first = value.first;
		// 	//a->second = value.second;
		// 	// a->parent = __parent;
		// 	if (begin_node->left != nullptr)
		// 		begin_node = begin_node->left;
		// 	balance_after_insert(__root(), __child);
		// 	__size++;
		// }
		//return iterator(__r);
	}


	template <class key_type>
	iterator 		find(const key_type& k)
	{
		iterator p = lower_bound(k, __root(), __end_node());
		if (p != end() && !value_comp()(k, *p))
			return p;
		return end();
	}

	template <class key_type>
	const_iterator 	find(const key_type& k) const
	{
		const_iterator p = lower_bound(k, __root(), __end_node());
		if (p != end() && !value_comp()(k, *p))
			return p;
		return end();
	}

	template <class key_type>
	size_type      	count(const key_type& k) const
	{
		pointer rt = __root();
		while (rt != nullptr)
		{
			if (value_comp()(k, rt->pair))
			{
				rt = static_cast<pointer>(rt->left);
			}
			else if (value_comp()(rt->pair, k))
				rt = static_cast<pointer>(rt->right);
			else
				return 1;
		}
		return 0;
	}

	template <class key_type>
	iterator 		lower_bound(const key_type& k, pointer start, pointer result)
	{
		while (start != nullptr) // se la root esiste
		{
			if (!value_comp()(start->key, k)) //torna vero se root >= k, falso se root < k
			{
				result = start;
				start = start->left;
			}
			else
			{
				start = start->right;
			}
		}
		return iterator(result);
	}

	template <class key_type>
	const_iterator 	lower_bound(const key_type& k, pointer start, pointer result) const
	{
		while (start != nullptr) // se la root esiste
		{
			if (!value_comp()(start->pair, k)) //torna vero se root >= k, falso se root < k
			{
				result = start;
				start = start->left;
			}
			else
			{
				start = start->right;
			}
		}
		return const_iterator(result);
	}

	template <class key_type>
	iterator 		__lower_bound(const key_type& k)
	{
		pointer root = __root();
		pointer result = __end_node();
		return (iterator)lower_bound(k, root, result);
	}

	template <class key_type>
	const_iterator 		__lower_bound(const key_type& k) const
	{
		pointer root = __root();
		pointer result = __end_node();
		return (const_iterator)lower_bound(k, root, result);
	}
	
	template <class key_type>
	iterator 		upper_bound(const key_type& k)
	{
		pointer root = __root();
		pointer result = __end_node();
		while (root != nullptr)
		{
			if (value_comp()(k, root->pair))
			{
				result = root;
				root = root->__left_;
			}
			else
				root =root->__right_;
		}
		return iterator(result);
	}

	template <class key_type>
	const_iterator 	upper_bound(const key_type& k) const
	{
		pointer root = __root();
		pointer result = __end_node();
		while (root != nullptr)
		{
			if (value_comp()(k, root->pair))
			{
				result = root;
				root = root->__left_;
			}
			else
				root =root->__right_;
		}
		return const_iterator(result);
	}

	template <class key_type>
	ft::pair<iterator,iterator>             equal_range(const key_type& k)
	{
		typedef ft::pair<iterator, iterator> _Pp;
		pointer result = __end_node();
		pointer root = __root();
		while (root != nullptr)
		{
			if (value_comp()(k, root->pair))
			{
				result = root;
				root = root->left;
			}
			else if (value_comp()(root->pair, k))
				root = root->right;
			else
				return _Pp(lower_bound(k, root->left, root), upper_bound(k, root->righ, result));
		}
		return _Pp(iterator(result), iterator(result));
	}

	template <class key_type>
	ft::pair<const_iterator,const_iterator> equal_range(const key_type& k) const
	{
		typedef ft::pair<const_iterator, const_iterator> _Pp;
		pointer result = __end_node();
		pointer root = __root();
		while (root != nullptr)
		{
			if (value_comp()(k, root->pair))
			{
				result = root;
				root = root->left;
			}
			else if (value_comp()(root->pair, k))
				root = root->right;
			else
				return _Pp(lower_bound(k, root->left, root), upper_bound(k, root->righ, result));
		}
		return _Pp(const_iterator(result), const_iterator(result));
	}

	iterator __remove_node_pointer(pointer __ptr)
	{
		iterator __r(__ptr);
		++__r;
		if (__begin_node() == __ptr)
			__begin_node() = __r.current;
		--size();
		__tree_remove(__end_node()->left, static_cast<pointer>(__ptr));
		return __r;
	}

};





	/******************************* CLASSE TREE_ITERATOR *******************************/

	template <class _Tp, class Iterator, class _DiffType, class Node>
	class tree_iterator 
	{
		typedef Iterator   	iterator;
		typedef _Tp*		pointer;
		//typedef _Tp&		reference;
		Node* current;


	public:
		typedef _Tp                                            value_type;
		typedef _DiffType                                      difference_type;
		typedef value_type&                                    reference;
	
		tree_iterator() : current(nullptr) {}
		explicit tree_iterator(Iterator __p) : current(__p) {}
		template <class U> tree_iterator(const tree_iterator<_Tp, U, _DiffType, Node>& u) : current(u.base()) {}
		template <class U> tree_iterator& operator=(const tree_iterator<_Tp, U, _DiffType, Node>& u) { current = u.base(); return *this; }
		Node* base() const { return static_cast<iterator>(current); }
		reference operator*() const { return  (*current).pair; }  
		pointer operator->() const { return *(current)->pair; }
		tree_iterator& operator++()
		{ 
			current = static_cast<iterator>(next_iter(current));
			return *this;
		}
		tree_iterator operator++(int)
			{tree_iterator __t(*this); ++(*this); return __t;}

		tree_iterator& operator--() {
		current = static_cast<iterator>(prev_iter(
			static_cast<iterator>(current)));
		return *this;
		}
		tree_iterator operator--(int)
			{tree_iterator __t(*this); --(*this); return __t;}

		friend
		bool operator==(const tree_iterator& __x, const tree_iterator& __y)
			{return __x.current == __y.current;}
		friend
		bool operator!=(const tree_iterator& __x, const tree_iterator& __y)
			{return !(__x == __y);}
		~tree_iterator(){}
	}; //tree_iterator



	/******************************* CONST_TREE_ITERATOR *******************************/

	template <class _Tp, class Iterator, class _DiffType, class Node>
	class const_tree_iterator 
	{
		typedef Iterator   	const_iterator;
		typedef _Tp*		pointer;
		//typedef _Tp&		reference;
		Node* current;


	public:
		typedef _Tp                                            value_type;
		typedef _DiffType                                      difference_type;
		typedef value_type&                                    reference;
	
		const_tree_iterator() : current(nullptr) {}
		explicit const_tree_iterator(Iterator __p) : current(__p) {}
		template <class U> 
		const_tree_iterator(const const_tree_iterator<_Tp, U, _DiffType, Node>& u) : current(u.base()) {}
		template <class U> 
		const_tree_iterator& operator=(const const_tree_iterator<_Tp, U, _DiffType, Node>& u) { current = u.base(); return *this; }
		Node* base() const { return static_cast<const_iterator>(current); }
		reference operator*() const { return  (*current).pair; }  
		pointer operator->() const { return *(current)->pair; }
		const_tree_iterator& operator++()
		{ 
			current = static_cast<const_iterator>(next_iter(current));
			return *this;
		}
		const_tree_iterator operator++(int)
			{const_tree_iterator __t(*this); ++(*this); return __t;}

		const_tree_iterator& operator--() {
		current = static_cast<const_iterator>(prev_iter(
			static_cast<const_iterator>(current)));
		return *this;
		}
		const_tree_iterator operator--(int)
			{const_tree_iterator __t(*this); --(*this); return __t;}

		friend
		bool operator==(const const_tree_iterator& __x, const const_tree_iterator& __y)
			{return __x.current == __y.current;}
		friend
		bool operator!=(const const_tree_iterator& __x, const const_tree_iterator& __y)
			{return !(__x == __y);}
		~const_tree_iterator(){}
	}; //tree_iterator

}//namespace