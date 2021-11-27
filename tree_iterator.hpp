#pragma once

#include <iostream>
#include <__tree>
//#include "binary_tree.hpp"

#include "tree_algorithm.hpp"

#define nullptr 0


namespace ft
{

	// struct input_iterator_tag  {};
	// struct output_iterator_tag {};
	// struct forward_iterator_tag       : public input_iterator_tag         {};
	// struct bidirectional_iterator_tag : public forward_iterator_tag       {};
	// struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	// template <class Iterator>
	// struct iterator_traits
	// {
	// 	typedef typename Iterator::difference_type 				difference_type;
	// 	typedef typename Iterator::value_type 					value_type;
	// 	typedef typename Iterator::pointer 						pointer;
	// 	typedef typename Iterator::reference 					reference;
	// 	typedef typename Iterator::iterator_category 			iterator_category;
	// };

	// template<class T> struct iterator_traits<T*>
	// {
	// 	typedef ptrdiff_t 					difference_type;
	// 	typedef T 							value_type;
	// 	typedef T* 							pointer;
	// 	typedef T& 							reference;
	// 	typedef random_access_iterator_tag 	iterator_category;
	// };
	
	// template<class Category, class T, class Distance = ptrdiff_t,
    //      class Pointer = T*, class Reference = T&>
	// struct iterator
	// {
	// 	typedef T         value_type;
	// 	typedef Distance  difference_type;
	// 	typedef Pointer   pointer;
	// 	typedef Reference reference;
	// 	typedef Category  iterator_category;
	// };

		/******************************* CLASSE TREE_ITERATOR *******************************/
	
	template <class T> struct Node;
	template <class _Tp> //pair
	class tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, _Tp>
	{
		typedef struct  Node<_Tp>		_Node;
		typedef _Node*				nodeptr;
		nodeptr 					current;
	public:
    	//typedef bidirectional_iterator_tag     	iterator_category;
		typedef _Tp                             value_type;
		typedef _Tp&                  			reference;
		typedef _Tp*							pointer;
		//typedef typename std::allocator<_Tp>::difference_type	difference_type;
		//typedef typename iterator_traits<_Tp>::difference_type std::allocator<_Tp>::difference_type;
		//typedef _Tp*						const_pointer;
		//typedef _Tp&						const_reference;
	
		tree_iterator() : current(nullptr) {}
		explicit tree_iterator(const nodeptr& __p) : current(__p) {} //forse anche qui guai
		tree_iterator(const tree_iterator& u) : current(u.base()) {}
		tree_iterator(tree_iterator& u) : current(u.base()) {}
	

		tree_iterator& operator=(const _Node& u) { current = u; return *this; }
		tree_iterator& operator=(const tree_iterator& u) { current = u.base(); return *this; }
		nodeptr base() const { return (nodeptr)current; }
		reference operator*() const { return  current->pair; }
		pointer operator->() const { return &(operator*()); }
		tree_iterator& operator++()
		{ 
			current = static_cast<nodeptr>(next_iter(current));
			return *this;
		}
		tree_iterator operator++(int)
		{
			tree_iterator __t(*this); ++(*this); return __t;
		}
		tree_iterator& operator--()
		{
			current = prev_iter(current);
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

	template <class _Tp> //pair
	class const_tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, _Tp>
	{
		typedef Node<_Tp> 					_Node;
		typedef const _Node*				nodeptr;
		nodeptr 							current;
	public:
		typedef _Tp                             value_type;
		typedef _Tp&                  			reference;
		typedef const _Tp*						const_pointer; //potrebbe causare guai //o forse no
		typedef const _Tp&						const_reference;
	
		const_tree_iterator() : current(nullptr) {}
		const_tree_iterator(nodeptr &__p) : current(__p) {} //forse anche qui guai
		const_tree_iterator(_Node* __p) : current(__p) {} //forse anche qui guai

		const_tree_iterator(const const_tree_iterator& u) : current(u.base()) {}
		const_tree_iterator(const tree_iterator<_Tp>& u) : current(u.base()) {}

		const_tree_iterator& operator=(const _Node& u) { current = u.base(); return *this; }

		
		nodeptr base() const { return current; }
		nodeptr	base(){ return current; }
		const_reference operator*() const { return  current->pair; }
		const_pointer operator->() const { return  &(operator*()); }
		const_tree_iterator& operator++()
		{
			current = static_cast<nodeptr>(next_iter(current));
			return *this;
		}
		const_tree_iterator operator++(int)
		{
			const_tree_iterator __t(*this); ++(*this); return __t;
		}
		const_tree_iterator& operator--()
		{
			current = static_cast<nodeptr>(prev_iter(current));
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
			{return !(__x == __y);}
		~const_tree_iterator(){}
	};

} 