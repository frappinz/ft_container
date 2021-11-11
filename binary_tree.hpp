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

template <class _Tp, class Node, class _Compare, class Allocator > //pair, nodo<pair>, compare, allocator<node<pair
class __tree
{
public:
    typedef _Tp                                     	value_type; //pair
	typedef Node										_Node;
    typedef _Compare                                 	value_compare;
    typedef Allocator                               	allocator_type;
    typedef typename allocator_type::pointer         	pointer; //pointer a nodo
    typedef typename allocator_type::const_pointer   	const_pointer; // const pointer a nodo
    typedef typename allocator_type::size_type       	size_type;
    typedef typename allocator_type::difference_type 	difference_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
    typedef ft::tree_iterator<value_type, pointer, difference_type, _Node>            			iterator;
    typedef ft::const_tree_iterator<value_type, const_pointer, difference_type, _Node> 		const_iterator;




private:
    pointer          	_begin_node; //punta sempre al nodo con la chiave piú piccola
	pointer				_end_node; //genitore di root
	Allocator			_alloc;
	size_type			_size;
	value_compare		_value_compare;

public:
    pointer 	get_end_node() 	const { return _end_node; }
	pointer 	get_begin_node() const { return _begin_node; }

    		Allocator& 	get_alloc(){return _alloc; }
    const	Allocator& 	get_alloc() const {return _alloc; }

          size_type& size() { return _size; }
    const size_type& size() const { return _size; }
    		value_compare& value_comp() { return _value_compare; }
    const	value_compare& value_comp() const { return _value_compare; }
   	pointer get_root() const { return _end_node->left; }

	__tree() : _size(0)
	{
		_Node* a;
		a = _alloc.allocate(1);
		_end_node = a;
		_begin_node =  get_end_node();
	}
    explicit __tree(const value_compare& __comp) : _size(0), _value_compare(__comp)
	{
		_begin_node = get_end_node();
	}
    explicit __tree(const allocator_type& __a) : _alloc(__a), _size(0)
	{
		_begin_node = get_end_node();
	}
    __tree(const value_compare& __comp, const allocator_type& __a) : _alloc(__a), _size(0), _value_compare(__comp)
	{
    	_begin_node = get_end_node();
	}
    __tree(const __tree& __t) { *this = __t; }
    __tree& operator=(const __tree& __t){
		if (this != &__t)
		{
			_value_compare = __t.value_compare();
			if (_alloc != __t._alloc)
				clear();
			else
				_alloc = __t._alloc;
			_end_node = __t._end_node;
			_begin_node = __t._begin_node;
			_size = __t._size;
		}
	}
    ~__tree() {}


          iterator begin()  {return       iterator(_begin_node);}
    const_iterator cbegin() const {return const_iterator(get_begin_node());}
          iterator end() {return      iterator(get_end_node());}
    const_iterator end() const {return const_iterator(get_end_node());}

    size_type max_size() const { return _alloc.max_size(); }

    void clear(){
		_alloc.destroy(get_root());
		_size = 0;
		get_begin_node() = get_end_node();
		_end_node->left = nullptr;
	}

    void swap(__tree& __t){
    	std::swap(_begin_node, __t._begin_node);
    	std::swap(_end_node, __t._end_node);
    	std::swap(_alloc, __t._alloc);
    	std::swap(_size, __t._size);
		std::swap(_value_compare, __t._value_compare);
    	if (size() == 0)
			get_begin_node() = get_end_node();
		else
			get_end_node()->left->parent = static_cast<pointer>(get_end_node());
		if (__t.size() == 0)
			__t.get_begin_node() = __t.get_end_node();
		else
			__t.get_end_node()->left->parent = static_cast<pointer>(__t.get_end_node());
	}
    void erase(const_iterator __p){
		pointer __np = __p.__get_np();
		iterator __r = __remove_node_pointer(__np);
		Allocator& __na = get_alloc();
		_alloc.destroy(__na, __get_ptr(const_cast<pointer>(*__p)));
		_alloc.deallocate(__na, __np, 1);
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
		pointer _root = get_root();
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
						newnode = _alloc.allocate(sizeof(_Node)); 
						_alloc.construct(newnode, _Node(value));
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
						newnode = _alloc.allocate(sizeof(_Node)); 
						_alloc.construct(newnode, _Node(value));
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
			newnode = _alloc.allocate(sizeof(_Node)); 
			_alloc.construct(newnode, _Node(value));
			_end_node->left = newnode;
			newnode->parent = _end_node;
			newnode->is_black = true;
		}
		if (_begin_node->left != nullptr)
			_begin_node = _begin_node->left;
		balance_after_insert(get_root(), newnode);
		_size++;
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
				newnode = _alloc.allocate(sizeof(_Node));
				_alloc.construct(newnode, _Node(value));
				hint.base()->left = newnode;
				newnode->parent = hint.base();
				_size++;
				balance_after_insert(get_root(), newnode);
				return (iterator)newnode;
			}
			else
				miao = insert(value);
		}
		else
		{
			if (hint.base()->right == nullptr) // e non ha figli di sinistra
			{
				newnode = _alloc.allocate(sizeof(_Node));
				_alloc.construct(newnode, _Node(value));
				hint.base()->right = newnode;
				newnode->parent = hint.base();
				_size++;
				balance_after_insert(get_root(), newnode);
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
		// 	__child = _alloc.allocate(sizeof(_Node)); 
		// 	_alloc.construct(__child, _Node(value));
		// 	__child->parent = __parent;
			
		// 	// _Node *a = NULL;
		// 	// _alloc.construct(a, value);

		// 	//__r = _alloc.allocate(1);
		// 	//Node *a(value);
		// 	//a = __r;
		// 	//a.first = value.first;
		// 	//a->second = value.second;
		// 	// a->parent = __parent;
		// 	if (_begin_node->left != nullptr)
		// 		_begin_node = _begin_node->left;
		// 	balance_after_insert(get_root(), __child);
		// 	_size++;
		// }
		//return iterator(__r);
	}


	template <class key_type>
	iterator 		find(const key_type& k)
	{
		iterator p = __lower_bound(k, get_root(), get_end_node());
		if (p != end() && !value_comp()(k, *p))
			return p;
		return end();
	}

	template <class key_type>
	const_iterator 	find(const key_type& k) const
	{
		const_iterator p = lower_bound(k, get_root(), get_end_node());
		if (p != end() && !value_comp()(k, *p))
			return p;
		return end();
	}

	template <class key_type>
	size_type      	count(const key_type& k) const
	{
		pointer rt = get_root();
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
	iterator 		__lower_bound(const key_type& k, pointer start, pointer result)
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
		return iterator(result);
	}

	template <class key_type>
	const_iterator 	__lower_bound(const key_type& k, pointer start, pointer result) const
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
	iterator 		lower_bound(const key_type& k)
	{
		pointer root = get_root();
		pointer result = get_end_node();
		return (iterator)__lower_bound(k, root, result);
	}

	template <class key_type>
	const_iterator 		lower_bound(const key_type& k) const
	{
		pointer root = get_root();
		pointer result = get_end_node();
		return (const_iterator)__lower_bound(k, root, result);
	}
	

	template <class key_type>
	const_iterator	__upper_bound(const key_type& __v, pointer start, pointer result) const
	{
		while (start != nullptr)
		{
			if (value_comp()(__v, start->pair))
			{
				result = static_cast<pointer>(start);
				start = static_cast<pointer>(start->left);
			}
			else
				start = static_cast<pointer>(start->right);
		}
		return const_iterator(result);
	}

	template <class key_type>
	iterator	__upper_bound(const key_type& __v, pointer start, pointer result)
	{
		while (start != nullptr)
		{
			if (value_comp()(__v, start->pair))
			{
				result = static_cast<pointer>(start);
				start = static_cast<pointer>(start->left);
			}
			else
				start = static_cast<pointer>(start->right);
		}
		return iterator(result);
	}

	template <class key_type>
	iterator 		upper_bound(const key_type& k)
	{
		pointer root = get_root();
		pointer result = get_end_node();
		while (root != nullptr)
		{
			if (value_comp()(k, root->pair))
			{
				result = root;
				root = root->left;
			}
			else
				root =root->right;
		}
		return iterator(result);
	}

	template <class key_type>
	const_iterator 	upper_bound(const key_type& k) const
	{
		pointer root = get_root();
		pointer result = get_end_node();
		while (root != nullptr)
		{
			if (value_comp()(k, root->pair))
			{
				result = root;
				root = root->left;
			}
			else
				root =root->right;
		}
		return const_iterator(result);
	}

	template <class key_type>
	ft::pair<iterator,iterator>             equal_range(const key_type& k)
	{
		typedef ft::pair<iterator, iterator> _Pp;
		pointer result = get_end_node();
		pointer root = get_root();
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
				return _Pp(__lower_bound(k, root->left, root), __upper_bound(k, root->right, result));
		}
		return _Pp(iterator(result), iterator(result));
	}

	template <class key_type>
	ft::pair<const_iterator,const_iterator> equal_range(const key_type& k) const
	{
		typedef ft::pair<const_iterator, const_iterator> _Pp;
		pointer result = get_end_node();
		pointer root = get_root();
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
				return _Pp(__lower_bound(k, root->left, root), __upper_bound(k, root->right, result));
		}
		return _Pp(const_iterator(result), const_iterator(result));
	}

	iterator __remove_node_pointer(pointer __ptr)
	{
		iterator __r(__ptr);
		++__r;
		if (get_begin_node() == __ptr)
			get_begin_node() = __r.current;
		--size();
		__tree_remove(get_end_node()->left, static_cast<pointer>(__ptr));
		return __r;
	}

};





	/******************************* CLASSE TREE_ITERATOR *******************************/

	template <class _Tp, class Iterator, class _DiffType, class Node>
	class tree_iterator 
	{
		typedef Iterator   	iterator;
		iterator current;


	public:
		typedef _Tp                             value_type;
		typedef _DiffType                       difference_type;
		typedef _Tp&                  			reference;
		typedef _Tp*							pointer;
	
		tree_iterator() : current(nullptr) {}
		explicit tree_iterator(Iterator __p) : current(__p) {}
		template <class U> tree_iterator(const tree_iterator<_Tp, U, _DiffType, Node>& u) : current(u.base()) {}
		template <class U> tree_iterator& operator=(const tree_iterator<_Tp, U, _DiffType, Node>& u) { current = u.base(); return *this; }
		
		iterator base() const { return current; }
		reference operator*() const { return  current->pair; }  
		pointer operator->() const { return &(operator*()); }
		tree_iterator& operator++()
		{ 
			current = static_cast<iterator>(next_iter(current));
			return *this;
		}
		tree_iterator operator++(int)
		{
			tree_iterator __t(*this); ++(*this); return __t;
		}
		tree_iterator& operator--()
		{
			current = static_cast<iterator>(prev_iter(static_cast<iterator>(current)));
			return *this;
		}
		tree_iterator operator--(int)
		{
			tree_iterator __t(*this); --(*this); return __t;
		}

		friend
		bool operator==(const tree_iterator& __x, const tree_iterator& __y)
			{return __x.current == __y.current;}
		friend
		bool operator!=(const tree_iterator& __x, const tree_iterator& __y)
			{return !(__x == __y);}
		~tree_iterator(){}
	}; //tree_iterator



	/******************************* CONST_TREE_ITERATOR *******************************/

	template <class _Tp, class Iterator, class _DiffType, class Node> //pair, const nodo*, difftype, node<pair 
	class const_tree_iterator 
	{
		typedef Iterator   	const_iterator; //const Nodo*
		//typedef _Tp&		reference;
		const_iterator current;


	public:
		typedef _Tp                                     value_type;
		typedef _DiffType                               difference_type;
		typedef const _Tp&                  			reference;
		typedef const _Tp*								pointer;
	
		const_tree_iterator() : current(nullptr) {}
		explicit const_tree_iterator(Iterator __p) : current(__p) {}
		const_tree_iterator(const const_tree_iterator& u) : current(u) {}
		//template <class U> const_tree_iterator(const const_tree_iterator<_Tp, U, _DiffType, Node> &u) : current(u.base()) {}
		template <class U> const_tree_iterator& operator=(const const_tree_iterator<_Tp, U, _DiffType, Node>& u) { current = u.base(); return *this; }
		
		const const_iterator base() const { return current; }
		reference operator*() const { return  current->pair; }  
		pointer operator->() const { return &(operator*()); }
		const_tree_iterator& operator++()
		{ 
			current = static_cast<const_iterator>(next_iter(current));
			return *this;
		}
		const_tree_iterator operator++(int)
		{
			const_tree_iterator __t(*this); ++(*this); return __t;
		}

		const_tree_iterator& operator--() 
		{
			current = static_cast<const_iterator>(prev_iter(static_cast<const_iterator>(current)));
			return *this;
		}
		const_tree_iterator operator--(int)
		{
			const_tree_iterator __t(*this); --(*this); return __t;
		}

		friend
		bool operator==(const const_tree_iterator& __x, const const_tree_iterator& __y)
			{return __x.current == __y.current;}
		friend
		bool operator!=(const const_tree_iterator& __x, const const_tree_iterator& __y)
			{return !(__x.current == __y.current);}
		~const_tree_iterator(){}
	}; //tree_iterator

}//namespace