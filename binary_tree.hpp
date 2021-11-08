#pragma once

#include <iostream>
#include <memory>
#include <__tree>
#include "tree_algorithm.hpp"
#include <map>
namespace ft
{


	template <class _Tp, class _Compare, class _Allocator> class __tree;
	template <class _Tp, class Iterator, class _DiffType> class tree_iterator;
		
		
	// /**********************  STRUTTURA NODI **********************/
	template <typename T>
	class Node {
		public:
			T key;
			class Node *left, *right;
			class Node *parent;
			bool is_black;
			Node()
			{
				left = nullptr;
				right = nullptr;
				parent = nullptr;
				is_black = true;
			}
			Node(T data) : key(data)
			{
				left = nullptr;
				right = nullptr;
				is_black = true;
				parent = nullptr;

			}

	};


/******************************** CLASSE TREE ********************************/


template <class _Tp, class _Compare, class Allocator >
class __tree
{
public:
	//friend class map;
    typedef _Tp                                     	value_type;
    typedef _Compare                                 	value_compare;
    typedef Allocator                               	allocator_type;
    typedef typename allocator_type::pointer         	pointer;
    typedef typename allocator_type::const_pointer   	const_pointer;
    typedef typename allocator_type::size_type       	size_type;
    typedef typename allocator_type::difference_type 	difference_type;
    typedef tree_iterator<value_type, pointer, difference_type>            	iterator;
    typedef tree_iterator<value_type, const_pointer, difference_type> 		const_iterator;
	typedef class Node <_Tp>							_Node;



private:
    pointer           	begin_node; // nei costruttori punta all'end node
	_Node*				end_node; //deve essere genitore di root
	Allocator			__alloc;
	size_type			__size;
	value_compare		__value_compare;

public:
    pointer 	__end_node() { return end_node; }
    Allocator& __node_alloc() {return __alloc; }
    const Allocator& __node_alloc() const {return __alloc;}
          iterator __begin_node() {return (iterator)begin_node;}
    const iterator& __begin_node() const {return (iterator)begin_node;}
          size_type& size() { return __size; }
    const size_type& size() const { return __size; }
          value_compare& value_comp() { return __value_compare; }
    const value_compare& value_comp() const { return __value_compare; }
    _Node* __root() const { return end_node->left; }
	__tree() : __size(0)
	{
		_Node* a = new _Node;
		end_node = a;
		begin_node =  __end_node();
	}
    explicit __tree(const value_compare& __comp) : __size(0), __value_compare(__comp)
	{
		__begin_node() = __end_node();
	}
    explicit __tree(const allocator_type& __a) : __alloc(__a), __size(0)
	{
		__begin_node() = __end_node();
	}
    __tree(const value_compare& __comp, const allocator_type& __a) : __alloc(__a), __size(0), __value_compare(__comp)
	{
    	__begin_node() = __end_node();
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

          iterator begin()  {return       iterator(__begin_node());}
    const_iterator begin() const {return const_iterator(__begin_node());}
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
		std::pair<iterator, iterator> __p = __equal_range_multi(__k); // da cambiare!!
		size_type __r = 0;
		for (; __p.first != __p.second; ++__r)
			__p.first = erase(__p.first);
		return __r;
	}

	template <class _Key>
	pointer& __find_equal(pointer& __parent, const _Key& __v)
	{
		pointer __nd = __root();
		if (__nd != nullptr)
		{
			while (true)
			{
				if (value_comp()(__v, __nd->key)) //se v é minore d
				{
					if (__nd->__left_ != nullptr) {
						__nd = __nd->__left_;
					} else {
						__parent = __nd;
						return __parent->__left_;
					}
				}
				else if (value_comp()(__nd->key, __v))
				{
					if (__nd->__right_ != nullptr) {
						__nd = __nd->__right_;
					} else {
						__parent = __nd;
						return __nd->__right_;
					}
				}
				else
				{
					__parent = __nd;
					return *__nd;
				}
			}
		}
		__parent = __end_node();
		return __parent->__left_;
	}

	std::pair<iterator, bool> insert( const value_type& value )
	{
		_Node *a = new _Node(value);
		pointer _root = __root();
		
		pointer x = nullptr;
		bool inserted = false;
		if (_root != nullptr) //se root esiste
		{
			x = _root;//puntiamo x a root
			while (true)
			{
				if (value_comp()(value, x->key)) //se la key é minore della root
				{
					if (x->left != nullptr) //se esiste un figlio di sinistra
						x = x->left;//ci spostiamo
					else{
						a->parent = x; //settiamo il nuovo parent a _root
						x->left = a;
						inserted = true;
						break ;
					}
				}
				else if (value_comp()(x->key, value))
				{
					if (x->right != nullptr)
						x = x->right;
					else
					{
						a->parent = x;
						x->right = a;
						inserted = true;
						break ;
					}
				}
				else
				{
					a->parent = x;
					break ;
				}
			}
		}
		else
		{
			end_node->left = a;
			a->parent = end_node;
			a->is_black = true;
		}
		if (begin_node->left != nullptr)
			begin_node = begin_node->left;
		balance_after_insert(__root(), a);
		__size++;
		std::cout << "root é " << __root()->key.first << std::endl;
		pointer r = a;
		std::pair<iterator,bool> miao;
		return std::pair<iterator,bool>((iterator)r, inserted);
	}

	template <class _Key>
	pointer& __find_equal(const_iterator __hint, pointer& __parent, pointer& __dummy,
                                                const _Key& __v)
	{
		if (__hint == end() || value_comp()(__v, *__hint))  // check before
		{
			// __v < *__hint
			const_iterator __prior = __hint;
			if (__prior == begin() || value_comp()(*--__prior, __v))
			{
				// *prev(__hint) < __v < *__hint
				if (__hint.__ptr_->__left_ == nullptr)
				{
					__parent = __hint.__ptr_;
					return __parent->__left_;
				}
				else
				{
					__parent = __prior.__ptr_;
					return (__prior.__ptr_)->__right_;
				}
			}
			// __v <= *prev(__hint)
			return __find_equal(__parent, __v);
		}
		else if (value_comp()(*__hint, __v))  // check after
		{
			// *__hint < __v
			const_iterator __next = _VSTD::next(__hint);
			if (__next == end() || value_comp()(__v, *__next))
			{
				// *__hint < __v < *_VSTD::next(__hint)
				if (__hint.__get_np()->__right_ == nullptr)
				{
					__parent = static_cast<pointer>(__hint.__ptr_);
					return static_cast<pointer>(__hint.__ptr_)->__right_;
				}
				else
				{
					__parent = static_cast<pointer>(__next.__ptr_);
					return __parent->__left_;
				}
			}
			// *next(__hint) <= __v
			return __find_equal(__parent, __v);
		}
		// else __v == *__hint
		__parent = static_cast<pointer>(__hint.__ptr_);
		__dummy = static_cast<pointer>(__hint.__ptr_);
		return __dummy;
	}



	iterator insert( iterator hint, const value_type& value )
	{
		pointer	__parent;
		pointer __dummy;
		pointer& __child = __find_equal(hint.__ptr_, __parent, __dummy, value);
		pointer __r = static_cast<pointer>(__child);
		if (__child == nullptr)
		{
			_Node *a = new _Node(value);
			a->parent = __parent;
			if (begin_node->left != nullptr)
				begin_node = begin_node->left;
			balance_after_insert(__root(), a);
			__size++;
		}
		return iterator(__r);
	}
    //iterator find(const _Key& __v);


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
			if (value_comp()(k, rt->key))
			{
				rt = static_cast<pointer>(rt->left);
			}
			else if (value_comp()(rt->key, k))
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
			if (value_comp()(k, root->key))
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
			if (value_comp()(k, root->key))
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
	std::pair<iterator,iterator>             equal_range(const key_type& k)
	{
		typedef std::pair<iterator, iterator> _Pp;
		pointer result = __end_node();
		pointer root = __root();
		while (root != nullptr)
		{
			if (value_comp()(k, root->key))
			{
				result = root;
				root = root->left;
			}
			else if (value_comp()(root->key, k))
				root = root->right;
			else
				return _Pp(lower_bound(k, root->left, root), upper_bound(k, root->righ, result));
		}
		return _Pp(iterator(result), iterator(result));
	}

	template <class key_type>
	std::pair<const_iterator,const_iterator> equal_range(const key_type& k) const
	{
		typedef std::pair<const_iterator, const_iterator> _Pp;
		pointer result = __end_node();
		pointer root = __root();
		while (root != nullptr)
		{
			if (value_comp()(k, root->key))
			{
				result = root;
				root = root->left;
			}
			else if (value_comp()(root->key, k))
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
			__begin_node() = __r.__ptr_;
		--size();
		__tree_remove(__end_node()->left, static_cast<pointer>(__ptr));
		return __r;
	}

};





	/******************************* CLASSE TREE_ITERATOR *******************************/

	template <class _Tp, class Iterator, class _DiffType>
	class tree_iterator 
	{
		typedef Iterator                                      	pointer;
		pointer __ptr_;

	public:
		typedef _Tp                                            value_type;
		typedef _DiffType                                      difference_type;
		typedef value_type&                                    reference;
	
		tree_iterator() {}
		reference operator*() const { return get_np()->key; }  
		pointer operator->() const { return *(get_np()->key); }
		pointer get_np() const { return static_cast<pointer>(__ptr_); }
		tree_iterator& operator++() 
		{ 
			__ptr_ = static_cast<pointer>(next_iter(__ptr_));
			return *this;
		}
		tree_iterator operator++(int)
			{tree_iterator __t(*this); ++(*this); return __t;}

		tree_iterator& operator--() {
		__ptr_ = static_cast<pointer>(prev_iter(
			static_cast<pointer>(__ptr_)));
		return *this;
		}
		tree_iterator operator--(int)
			{tree_iterator __t(*this); --(*this); return __t;}

		friend
		bool operator==(const tree_iterator& __x, const tree_iterator& __y)
			{return __x.__ptr_ == __y.__ptr_;}
		friend
		bool operator!=(const tree_iterator& __x, const tree_iterator& __y)
			{return !(__x == __y);}
		explicit tree_iterator(pointer __p) : __ptr_(__p) {}
		pointer base() const { return static_cast<pointer>(__ptr_); }
	}; //tree_iterator
}//namespace