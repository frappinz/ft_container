#ifndef MAP_HPP
#define MAP_HPP

#include <map>
//#include <__tree>
#include <memory>
#include "iterator.hpp"
#include "binary_tree.hpp"
#include <functional>
#include <utility>
#include <iostream>

namespace ft
{

	template <class _Key, class _CP, class _Compare >
	class _map_value_compare : private _Compare
	{
		public:
			_map_value_compare() : _Compare() {}
			_map_value_compare(_Compare c) : _Compare(c) {}
			const _Compare& key_comp() const {return *this;}
			bool operator()(const _CP& _x, const _CP& _y) const
				{return static_cast<const _Compare&>(*this)(_x.first, _y.first);}
			bool operator()(const _CP& _x, const _Key& _y) const
				{return static_cast<const _Compare&>(*this)(_x.first, _y);}
			bool operator()(const _Key& _x, const _CP& _y) const
				{return static_cast<const _Compare&>(*this)(_x, _y.first);}
			void swap(_map_value_compare&_y)
			{
				std::swap(static_cast<_Compare&>(*this), static_cast<_Compare&>(_y));
			}
	};


	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<Node <std::pair<const Key, T> > > >
	class map
	{
		public:
			/****************** MEMBER TYPES ******************/
			typedef Key                                      	key_type;
			typedef T                                        	data_type;
			typedef std::pair<const key_type, data_type>   		pair;
			typedef Compare                                  	key_compare;
			typedef Allocator                                	allocator_type;
			typedef typename allocator_type::reference       	reference;
			typedef typename allocator_type::const_reference 	const_reference;
			typedef typename allocator_type::pointer         	pointer;
			typedef typename allocator_type::const_pointer   	const_pointer;
			typedef typename allocator_type::size_type       	size_type;
			typedef typename allocator_type::difference_type 	difference_type;

			typedef typename ft::__tree<pair, key_compare, Allocator>::iterator				iterator;
			typedef typename ft::__tree<pair, key_compare, Allocator>::iterator				const_iterator;

			// typedef ft::reverse_iterator<iterator>         	reverse_iterator;
			// typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

		class value_compare : public std::binary_function<pair, pair, bool>
		{
				friend class map;
			protected:
				key_compare comp;
				value_compare(key_compare c) : comp(c) {}
			public:
				bool operator()(const pair& x, const pair& y) const {return comp(x.first, y.first);}
		}; //value compare

		private:
			typedef pair            	_pair;
			typedef _map_value_compare<key_type, _pair, key_compare> _vc;
			typedef __tree<pair, _vc, allocator_type>   	_base;
			//typedef typename _base::_node_traits                _node_traits;

			size_t 	_size;
			_base _tree;
							/********************************    COSTRUCTORS    ********************************/

		public: 
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _size(0)
		{ std::cout << "chiamato\n";}
		template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& a = allocator_type());
		map(const map& m);
		~map(){}
		map& operator=(const map& m);

							/********************************      ITERATOR     ********************************/

		iterator 		begin(){ return (iterator)_tree.__begin_node(); }
		const_iterator 	begin() const;
		iterator 		end();
		const_iterator 	end()   const;

		// reverse_iterator 		rbegin();
		// const_reverse_iterator 	rbegin() const;
		// reverse_iterator 		rend();
		// const_reverse_iterator	rend()   const;


							/********************************      CAPACITY     ********************************/

		bool      empty()    const;
		size_type size()     const;
		size_type max_size() const;

							/********************************   ELEMENT ACCESS   ********************************/

		data_type& 		operator[](const key_type& k);
		data_type& 		at (const key_type& k);
		const data_type& 	at (const key_type& k) const;

							/********************************   	MODIFIERS     ********************************/

		std::pair<iterator, bool> 	insert(const pair& v)
		{
			//mymap.insert ( std::pair<char,int>('a',100) );
			return _tree.insert(v);

		}
		iterator 					insert(const_iterator position, const pair& v);
		template <class InputIterator>
			void 					insert(InputIterator first, InputIterator last);

		void		erase(iterator position);
		size_type 	erase(const key_type& k);
		void		erase(iterator first, iterator last);
		void 		clear();
		void 		swap (map& x);

							/********************************   	OBSERVER    ********************************/

		allocator_type get_allocator() const;
		key_compare    key_comp()      const;
		value_compare  value_comp()    const;

							/********************************    MAP OPERATIONS   ********************************/

		iterator 		find(const key_type& k);
		const_iterator 	find(const key_type& k) const;

		size_type      	count(const key_type& k) const;

		iterator 		lower_bound(const key_type& k);
		const_iterator 	lower_bound(const key_type& k) const;

		iterator 		upper_bound(const key_type& k);
		const_iterator 	upper_bound(const key_type& k) const;


		std::pair<iterator,iterator>             equal_range(const key_type& k);
		std::pair<const_iterator,const_iterator> equal_range(const key_type& k) const;

	}; //map

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator==(const map<Key, T, Compare, Allocator>& x,
			const map<Key, T, Compare, Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator< (const map<Key, T, Compare, Allocator>& x,
			const map<Key, T, Compare, Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator!=(const map<Key, T, Compare, Allocator>& x,
			const map<Key, T, Compare, Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator> (const map<Key, T, Compare, Allocator>& x,
			const map<Key, T, Compare, Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator>=(const map<Key, T, Compare, Allocator>& x,
			const map<Key, T, Compare, Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator<=(const map<Key, T, Compare, Allocator>& x,
			const map<Key, T, Compare, Allocator>& y);

	// specialized algorithms:
	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y);


	//TODO fare pair e sostituire gli std


}



#endif