#pragma once

#include <iostream>
#include <memory>
#include <__tree>
#include "tree_algorithm.hpp"
//#include <map>
namespace ft
{


	template <class _Tp, class _Compare, class _Allocator> class __tree;
	template <class _Tp, class Iterator, class _DiffType> class tree_iterator;
		
		
	// /**********************  STRUTTURA NODI **********************/
	// template<class T>
	// struct Node
	// {
	// 	typedef struct Node* pointer;
	// 	pointer left;
	// 	pointer right;
	// 	pointer parent;
	// 	bool	__is_black;
	// 	T		_data;

	// }; //nodo



// BST node
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
				is_black = false;
			}
			Node(T data) : key(data)
			{
				left = nullptr;
				right = nullptr;
				is_black = false;
			}
			// Node* newNode(T data)
			// {
			// 	Node* temp = new Node;
			
			// 	temp->key = data;
			
			// 	temp->left = NULL;
			// 	temp->right = NULL;
			
			// 	return temp;
			// }
			Node* insert(Node* root, T data)
			{
				Node* newnode = new Node(data);
				Node* x = root;
				Node* y = NULL;
				while (x != NULL) //se la root esiste
				{
					y = x; //y punta a root
					if (key < x->key) //se nuovo nodo é minore della root
						x = x->left; // ci spostiamo a sinistra
					else
						x = x->right;//altrimenti ci spostiamo a destra
				}
				if (y == NULL) // se é il primo nodo creato (root) entrerá qui
					y = newnode;
				else if (key < y->key)
					y->left = newnode;
				else
					y->right = newnode;
				newnode->parent = y;
				return y;
			}

	};


/******************************** CLASSE TREE ********************************/


template <class _Tp, class _Compare, class Allocator >
//<tp = pair, compare = key, pair, compare; allocator 
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
    pointer __end_node() { return end_node; }
   // Iterator __end_node() const { return __end_node; }
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
    __tree(const __tree& __t) 
	{} // da fare
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
	} // da fare
    ~__tree() {}

          iterator begin()  {return       iterator(__begin_node());}
    const_iterator begin() const {return const_iterator(__begin_node());}
          iterator end() {return       iterator(__end_node());}
    const_iterator end() const {return const_iterator(__end_node());}

    size_type max_size() const { return __alloc.max_size(); }

    void clear()
	{
		__alloc.destroy(__root());
		__size = 0;
		begin_node = end_node;
		end_node->left = nullptr;
		
	}

    void swap(__tree& __t)
	{
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
    iterator erase(const_iterator __p)
	{
		pointer __np = __p.__get_np();
		iterator __r = __remove_node_pointer(__np);
		Allocator& __na = __node_alloc();
		__alloc.destroy(__na, __get_ptr(const_cast<pointer>(*__p)));
		__alloc.deallocate(__na, __np, 1);
		return __r;
	}

    iterator erase(const_iterator __f, const_iterator __l)
	{
		while (__f != __l)
			__f = erase(__f);
		return iterator(__l.__ptr_);
	}


	std::pair<iterator, bool> insert( const value_type& value ) //std::pair 
	{
		_Node *a = new _Node;
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
			a = __root();
		pointer r = a;
		if (a == nullptr)
		{
			a->insert(__root(), value);
			balance_after_insert(__root(), a);
			inserted = true;
		
		}
		std::pair<iterator,bool> miao;
		return std::pair<iterator,bool>((iterator)r, inserted);
		

		//value = std::pair<iterator,bool>;
		// tree_min(end_node);
		// _Node *a = new _Node;
		// a->left = nullptr;
		// a->right = nullptr;
		// //_Node x = end_node;
		// _Node *x = end_node.left; //stiamo alla root
		// while (true)
		// {
		// 	if ((value.first, x->left) && x->left != nullptr)
		// 		x = x->left;
		// 	if (value.first > x->right && x->right != nullptr)
		// 		x = x->right;
		// 	break;
		// }
		// a->parent = x->parent;
		// a->_key = value.first;
		// a->_data = value.second;
		// balance_after_insert(__root(), a);



		
		// std::pair<iterator,bool> la;
		// return la;
	}
	iterator insert( iterator hint, const value_type& value )
	{
		// parentpointer __parent;
		// __node_base_pointer& __child = __find_leaf(__p, __parent, _NodeTypes::__get_key(__v));
		// __node_holder __h = __construct_node(__v);
		// __insert_node_at(__parent, __child, static_cast<__node_base_pointer>(__h.get()));
		// return iterator(__h.release());
	}
    //iterator find(const _Key& __v);


	template <class key_type>
	iterator 		find(const key_type& k); 
	template <class key_type>
	const_iterator 	find(const key_type& k) const;

	template <class key_type>
	size_type      	count(const key_type& k) const;

	template <class key_type>
	iterator 		lower_bound(const key_type& k);
	template <class key_type>
	const_iterator 	lower_bound(const key_type& k) const;
	template <class key_type>
	iterator 		upper_bound(const key_type& k);
	template <class key_type>
	const_iterator 	upper_bound(const key_type& k) const;

	template <class key_type>
	std::pair<iterator,iterator>             equal_range(const key_type& k);
	template <class key_type>
	std::pair<const_iterator,const_iterator> equal_range(const key_type& k) const;

    // template <class, class, class, class> friend class map;
    // template <class, class, class, class> friend class multimap;
	//template <class _Tp, class _Compare, class _Allocator>
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
		//class _tree;
		typedef Iterator                                       	pointer;
		pointer __ptr_;

	public:
		//struct Node;
		//class _tree;
		//typedef bidirectional_iterator_tag                     iterator_category;
		typedef _Tp                                            value_type;
		typedef _DiffType                                      difference_type;
		typedef value_type&                                    reference;
	
		tree_iterator() : __ptr_() {}
		reference operator*() const { return static_cast<reference>(*__ptr_); }  
		pointer operator->() const { return __ptr_; }

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