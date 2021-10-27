#ifndef MAP_HPP
#define MAP_HPP

#include <map>
#include <memory>
#include "iterator.hpp"
#include "map_iterator.hpp"
#include <functional>

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
				{return static_cast<const _Compare&>(*this)(_x._get_value().first, _y._get_value().first);}
			bool operator()(const _CP& _x, const _Key& _y) const
				{return static_cast<const _Compare&>(*this)(_x._get_value().first, _y);}
			bool operator()(const _Key& _x, const _CP& _y) const
				{return static_cast<const _Compare&>(*this)(_x, _y._get_value().first);}
			void swap(_map_value_compare&_y)
			{
				std::swap(static_cast<_Compare&>(*this), static_cast<_Compare&>(_y));
			}
	};




	template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<std::pair<const Key, T> > >
	class map
	{
		public:
			/****************** MEMBER TYPES ******************/
			typedef Key                                      key_type;
			typedef T                                        mapped_type;
			typedef std::pair<const key_type, mapped_type>   value_type;
			typedef Compare                                  key_compare;
			typedef Allocator                                allocator_type;
			typedef typename allocator_type::reference       reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer         pointer;
			typedef typename allocator_type::const_pointer   const_pointer;
			typedef typename allocator_type::size_type       size_type;
			typedef typename allocator_type::difference_type difference_type;

			typedef ft::map_iterator<pointer>				iterator;
			typedef ft::map_const_iterator<const_pointer>	const_iterator;
			typedef ft::reverse_iterator<iterator>         	reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
				friend class map;
			protected:
				key_compare comp;
				value_compare(key_compare c) : comp(c) {}
			public:
				bool operator()(const value_type& x, const value_type& y) const {return comp(x.first, y.first);}
		}; //value compare

		private:
			typedef value_type            	_value_type;
			typedef _map_value_compare<key_type, _value_type, key_compare> _vc;
			//typedef typename std::_rebind_alloc_helper<std::allocator_traits<allocator_type>, _value_type>::type _allocator_type;		C++11
			typedef _tree<value_type, _vc, allocator_type>   	_base;
			typedef typename _base::_node_traits                _node_traits;
			typedef allocator_traits<allocator_type>            _alloc_traits;

			size_t 	_size;
			_base _tr ee;


							/********************************    COSTRUCTORS    ********************************/


		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& a = allocator_type());
		map(const map& m);
		~map();
		map& operator=(const map& m);

							/********************************      ITERATOR     ********************************/

		iterator 		begin();
		const_iterator 	begin() const;
		iterator 		end();
		const_iterator 	end()   const;

		reverse_iterator 		rbegin();
		const_reverse_iterator 	rbegin() const;
		reverse_iterator 		rend();
		const_reverse_iterator	rend()   const;


							/********************************      CAPACITY     ********************************/

		bool      empty()    const;
		size_type size()     const;
		size_type max_size() const;

							/********************************   ELEMENT ACCESS   ********************************/

		mapped_type& 		operator[](const key_type& k);
		mapped_type& 		at (const key_type& k);
		const mapped_type& 	at (const key_type& k) const;

							/********************************   	MODIFIERS     ********************************/

		std::pair<iterator, bool> 	insert(const value_type& v);
		iterator 					insert(const_iterator position, const value_type& v);
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