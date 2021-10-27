#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

//#include "map.hpp"
#include "iterator.hpp"

namespace ft
{	
		
	//TODO= ALBERELLO
	template <class TreeIterator>
	class map_iterator
	{
			//typedef typename TreeIterator::pointer_traits			pointer_traits;     C++11
			typedef typename TreeIterator::value_type				value_type;
			typedef typename TreeIterator::pointer 					pointer;

			TreeIterator _it;

		public:
			typedef bidirectional_iterator_tag						iterator_category;
			typedef typename TreeIterator::difference_type          difference_type;
			typedef value_type& 									reference;

		
			map_iterator()  {}

		
			map_iterator(TreeIterator i)  : _it(i) {}

		
			reference operator*() const {return static_cast<reference>(*(_it));} //forse non funziona cosí 
		
			pointer operator->() const { return (pointer)_it;}

		
			map_iterator& operator++() {++_it; return *this;}
		
			map_iterator operator++(int)
			{
				map_iterator t(*this);
				++(*this);
				return t;
			}

		
			map_iterator& operator--() {--_it; return *this;}
		
			map_iterator operator--(int)
			{
				map_iterator t(*this);
				--(*this);
				return t;
			}

			friend
			bool operator==(const	map_iterator& x, const	map_iterator& y)
				{return x._it == y._it;}
			friend
		
			bool operator!=(const	map_iterator& x, const	map_iterator& y)
				{return x._it != y._it;}

			template <class, class, class, class> friend class map;
			template <class, class, class, class> friend class multimap;
			template <class> friend class map_const_iterator;

	}; //map_iterator

	template <class TreeIterator>
	class map_const_iterator
	{
		typedef typename TreeIterator::_NodeTypes                   _NodeTypes;
		//typedef typename TreeIterator::pointer_traits             	pointer_traits; 	C++11

		TreeIterator _it;

	public:
		typedef bidirectional_iterator_tag                          iterator_category;
		typedef typename _NodeTypes::map_value_type                	value_type;
		typedef typename TreeIterator::difference_type              difference_type;
		typedef const value_type&                                   reference;
		typedef typename _NodeTypes::const_map_value_type_pointer  	pointer;

	
		map_const_iterator()  {}

	
		map_const_iterator(TreeIterator i)  : _it(i) {}
	
		map_const_iterator(map_iterator <typename TreeIterator::non_const_iterator> i) 
			: _it(i._it) {}

	
		reference operator*() const {return static_cast<reference> (_it);}
	
		pointer operator->() const {return _it;}

	
		map_const_iterator& operator++() {++_it; return *this;}
	
		map_const_iterator operator++(int)
		{
			map_const_iterator t(*this);
			++(*this);
			return t;
		}

	
		map_const_iterator& operator--() {--_it; return *this;}
	
		map_const_iterator operator--(int)
		{
			map_const_iterator t(*this);
			--(*this);
			return t;
		}

		friend
		bool operator==(const map_const_iterator& x, const map_const_iterator& y)
			{return x._it == y._it;}
		friend
		bool operator!=(const map_const_iterator& x, const map_const_iterator& y)
			{return x._it != y._it;}

		template <class, class, class, class> friend class map;
		template <class, class, class, class> friend class multimap;
		template <class, class, class> friend class tree_const_iterator;
	};
} //namespace

#endif