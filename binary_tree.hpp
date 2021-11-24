#pragma once

#include <iostream>
#include <memory>
#include <__tree>
#include "map.hpp"
#include "tree_algorithm.hpp"
#include "utils.hpp"
#include "tree_iterator.hpp"
#include <map>
namespace ft
{


	template <class _Tp, class _Compare, class _Allocator> class __tree;
	template <class _Tp> class tree_iterator;
	template <class _Tp> class const_tree_iterator;
	template <typename T> struct Node;
		
	// /**********************  STRUTTURA NODI **********************/
	
	template <typename T> //std::pair <T1, T2 
	struct Node {
			public:
				T pair;
				struct Node *left, *right;
				struct Node *parent;
				bool is_black;
				bool is_end;
				Node() : left(nullptr), right(nullptr), parent(nullptr), is_black(true), is_end(false) {}
				Node(T value) : pair(value), left(nullptr), right(nullptr), parent(nullptr), is_black(true), is_end(false){}
				~Node(){}
			};




/******************************** CLASSE TREE ********************************/

template <class _Tp, class _Compare, class Allocator = std::allocator<Node<_Tp> > > //pair, compare, allocator<node<pair
class __tree
{
public:
	typedef struct Node<_Tp>							_Node;
	typedef _Node*										nodeptr;
    typedef _Tp                                     	value_type;
    typedef _Compare                                 	value_compare;
    typedef Allocator                               	allocator_type;
    typedef typename allocator_type::pointer        	pointer;
    typedef typename allocator_type::const_pointer   	const_pointer;
    typedef typename allocator_type::size_type       	size_type;
    typedef typename allocator_type::difference_type 	difference_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
    typedef ft::tree_iterator<_Tp>            			iterator;
    typedef ft::const_tree_iterator<_Tp> 				const_iterator;
	typedef ft::tree_reverse_iterator<_Tp>				reverse_iterator;
	typedef ft::const_tree_reverse_iterator<_Tp>		const_reverse_iterator;

private:
	nodeptr				root;
    nodeptr         	_begin_node; //punta sempre al nodo con la chiave piú piccola
	nodeptr				_end_node; //genitore di root
	Allocator			_alloc;
	size_type			_size;
	value_compare		_value_compare;

public:
    nodeptr 	get_end_node() 	const { return _end_node; }
	nodeptr 	get_begin_node() const { return _begin_node; }

    		Allocator& 	get_alloc(){return _alloc; }
    const	Allocator& 	get_alloc() const {return _alloc; }

          size_type& size() { return _size; }
    const size_type& size() const { return _size; }
    		value_compare& value_comp() { return _value_compare; }
    const	value_compare& value_comp() const { return _value_compare; }
   	nodeptr get_root() const { return root; }
	void	set_root(nodeptr x) { root = x; }
	void	find_new_root(nodeptr x) {
		while (x->parent != nullptr)
			x = x->parent;
		root = x;
	}

	void	find_new_end(nodeptr root)
	{
		nodeptr x = root;
		while (x->right && !x->right->is_end)
			x = x->right;
		x->right = _end_node;
		_end_node->parent = x;
	}

	__tree() : _size(0)
	{
		root = nullptr;
		_begin_node = _alloc.allocate(1);
		_end_node = _alloc.allocate(1);
		_end_node->is_end = true;
		_begin_node = _end_node;
	}
    explicit __tree(const value_compare& __comp) : _size(0), _value_compare(__comp)
	{
		//root = _alloc.allocate(1);
		root = nullptr;
		_begin_node = _alloc.allocate(1);
		_end_node = _alloc.allocate(1);
		_end_node->is_end = true;
		_begin_node = _end_node;
	}
    explicit __tree(const allocator_type& __a) : _alloc(__a), _size(0)
	{
		//root = _alloc.allocate(1);
		root = nullptr;
		_begin_node = _alloc.allocate(1);
		_end_node = _alloc.allocate(1);
		_end_node->is_end = true;
		_begin_node = _end_node;
	}
    __tree(const value_compare& __comp, const allocator_type& __a) : _alloc(__a), _size(0), _value_compare(__comp)
	{
		root = nullptr;
		_begin_node = _alloc.allocate(1);
		_end_node = _alloc.allocate(1);
		_end_node->is_end = true;
		_begin_node = _end_node;
	}

    __tree(const __tree& __t)  {
		if (this != &__t)
		{
			_value_compare = __t.value_comp();
			if (_alloc != __t._alloc)
				clear();
			else
				_alloc = __t._alloc;

			_end_node = _alloc.allocate(1);
			for(iterator i = __t.begin(); i != __t.end(); i++)
				insert(*i);
		}
	}
    __tree& operator=(const __tree& __t){
		if (this != &__t)
		{
			_value_compare = __t.value_comp();
			if (_alloc != __t._alloc)
				clear();
			else
				_alloc = __t._alloc;
			_end_node = __t._end_node;
			_begin_node = __t._begin_node;
			_size = __t._size;
		}
		return *this;
	}
    ~__tree() {}


          iterator begin() const {return       iterator(_begin_node);}
    const_iterator cbegin() const {return const_iterator(_begin_node);}
          iterator end() const {return      iterator(_end_node);}
    const_iterator cend() const {return const_iterator(_end_node);}

    size_type max_size() const { return _alloc.max_size(); }




	template <class U>
	_Node *newnode (U& value) 
	{
		_Node *a = _alloc.allocate(1);
		_Node n(value);
		_alloc.construct(a, n);
		return a;
	}

    void clear(){
		_alloc.destroy(get_root());
		_size = 0;
		_begin_node = _end_node;
	}

    void swap(__tree& __t){
    	std::swap(_begin_node, __t._begin_node);
    	std::swap(_end_node, __t._end_node);
    	std::swap(_alloc, __t._alloc);
    	std::swap(_size, __t._size);
		std::swap(_value_compare, __t._value_compare);
    	if (size() == 0)
			_begin_node = _end_node;
		else
			get_end_node()->left->parent = static_cast<nodeptr>(get_end_node());
		if (__t.size() == 0)
			__t._begin_node = __t.get_end_node();
		else
			__t.get_end_node()->left->parent = static_cast<nodeptr>(__t.get_end_node());
	}
    void erase_position(iterator __p){
		pointer __np = __p.base();
		iterator __r = __remove_node_nodeptr(__np);
		find_new_root(_begin_node);
		_alloc.destroy(__p.base());
		_alloc.deallocate(__np, 1);
		find_new_end(root);
	}

    void erase_range(iterator __f, iterator __l){
		iterator tmp;
		while(__f != __l)
		{
			tmp = __f;
			if(__f++ != __l)
				erase_position(tmp);
		}

	}

	template <class _Key>
	size_type erase_key(const _Key& __k)
	{
		ft::pair<iterator, iterator> __p = equal_range(__k); // da cambiare!!
		size_type __r = 0;
		for (; __p.first != __p.second; ++__r)
			erase_position(__p.first);
		return __r;
	}

	ft::pair<iterator, bool> insert(const value_type& value )
	{
		nodeptr _root = get_root();
		nodeptr x = nullptr;
		nodeptr nuovo = nullptr;
		bool inserted = false;
		if (_root != nullptr && _size != 0) //se root esiste
		{
			x = _root;//puntiamo x a root
			while (true)
			{
				if (value_comp()(value, x->pair)) //se la key é minore della root
				{
					if (x->left != nullptr) //se esiste un figlio di sinistra
						x = x->left;//ci spostiamo
					else{
						nuovo = newnode(value);
						nuovo->parent = x;
						x->left = nuovo;
						inserted = true;
						break ;
					}
				}
				else if (value_comp()(x->pair, value))
				{
					if (x->right != nullptr && x->right != _end_node)
						x = x->right;
					else
					{
						nuovo = newnode(value);
						nuovo->parent = x;
						x->right = nuovo;
						nuovo->right = _end_node;
						_end_node->parent = nuovo;
						_end_node->left = nullptr;
						nuovo->left = nullptr;
						inserted = true;
						break ;
					}
				}
				else//se troviamo un'uguaglianza sostituiamo il data
				{
					x->pair.second = value.second;
					break ;
				}
			}
		}
		else 						// É L'UNICO CHE FORSE FUNZIONA!!! 
		{
			root = newnode(value);
			nodeptr r = root;
			_size++;
			root->right = _end_node;
			_begin_node = root;
			_end_node->parent = root;
			return ft::pair<iterator,bool>((iterator)r, true);
		}
		if (_begin_node->left != nullptr)
			_begin_node = _begin_node->left;
		// while (_end_node->parent->right != _end_node)
		// 	++_end_node;
	
		if (inserted == true)
		{
			balance_after_insert(get_root(), nuovo);
			find_new_root(nuovo);
			//_end_node->parent = tree_max(root);
			_size++;
		}
		nodeptr r = nuovo;
		return ft::pair<iterator,bool>((iterator)r, inserted);
	}


	iterator insert( iterator hint, const value_type& value )
	{
		ft::pair<iterator, bool> miao;
		if (root == nullptr)
			miao = insert(value);
		else if(value_comp()(value, *hint)) // se la nuova key é minore della key nell'iteratore consigliato
		{
			if (hint.base()->left == nullptr) // e non ha figli di sinistra
			{
				_Node *nuovo = newnode(value);
				hint.base()->left = nuovo;
				nuovo->parent = hint.base();
				_size++;
				balance_after_insert(get_root(), nuovo);
				find_new_root(nuovo);
				return (iterator)nuovo;
			}
			else
				miao = insert(value);
		}
		else
		{
			if (hint.base()->right == nullptr) // e non ha figli di sinistra
			{
				_Node *nuovo = newnode(value);
				hint.base()->right = nuovo;
				nuovo->parent = hint.base();
				_size++;
				balance_after_insert(get_root(), nuovo);
				find_new_root(nuovo);
				return (iterator)nuovo;
			}
			else
				miao = insert(value);
		}
		return (miao.first);
	}


	template <class key_type>
	iterator 		find(const key_type& k)
	{
		iterator p = lower_bound(k);
		if (p != end() && !value_comp()(k, *p))
			return p;
		return end();
	}

	template <class key_type>
	const_iterator 	find(const key_type& k) const
	{
		const_iterator p = lower_bound(k);
		if (p != end() && !value_comp()(k, *p))
			return p;
		return end();
	}

	template <class key_type>
	size_type      	count(const key_type& k) const
	{
		nodeptr rt = get_root();
		while (rt != nullptr)
		{
			if (value_comp()(k, rt->pair))
			{
				rt = static_cast<nodeptr>(rt->left);
			}
			else if (value_comp()(rt->pair, k))
				rt = static_cast<nodeptr>(rt->right);
			else
				return 1;
		}
		return 0;
	}

	template <class key_type>
	iterator 		__lower_bound(const key_type& k, nodeptr start, nodeptr result)
	{
		while (start != nullptr && start != _end_node) // se la root esiste
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
	const_iterator 	__lower_bound(const key_type& k, nodeptr start, nodeptr result) const
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
		nodeptr result = get_end_node();
		return (iterator)__lower_bound(k, root, result);
	}

	template <class key_type>
	const_iterator 		lower_bound(const key_type& k) const
	{
		nodeptr result = get_end_node();
		return (const_iterator)__lower_bound(k, root, result);
	}
	

	template <class key_type>
	const_iterator	__upper_bound(const key_type& __v, nodeptr start, nodeptr result) const
	{
		while (start != nullptr)
		{
			if (value_comp()(__v, start->pair))
			{
				result = static_cast<nodeptr>(start);
				start = static_cast<nodeptr>(start->left);
			}
			else
				start = static_cast<nodeptr>(start->right);
		}
		return const_iterator(result);
	}

	template <class key_type>
	iterator	__upper_bound(const key_type& __v, nodeptr start, nodeptr result)
	{
		while (start != nullptr)
		{
			if (value_comp()(__v, start->pair))
			{
				result = static_cast<nodeptr>(start);
				start = static_cast<nodeptr>(start->left);
			}
			else
				start = static_cast<nodeptr>(start->right);
		}
		return iterator(result);
	}

	template <class key_type>
	iterator 		upper_bound(const key_type& k)
	{
		nodeptr root = get_root();
		nodeptr result = get_end_node();
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
		nodeptr root = get_root();
		nodeptr result = get_end_node();
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
		nodeptr result = get_end_node();
		nodeptr root = get_root();
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
		nodeptr result = get_end_node();
		nodeptr root = get_root();
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

	iterator __remove_node_nodeptr(pointer __ptr)
	{
		iterator __r(__ptr);
		++__r;
		if (get_begin_node() == __ptr)
			_begin_node = __r.base();
		find_new_root(__ptr);
		--_size;
		tree_remove(root, static_cast<nodeptr>(__ptr));
		find_new_root(_begin_node);
		return __r;
	}

};

}//namespace