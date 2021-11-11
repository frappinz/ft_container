#ifndef MAP_HPP
#define MAP_HPP

#include <map>
#include <__tree>
#include <memory>
#include "iterator.hpp"
#include "binary_tree.hpp"
#include <functional>
#include <utility>
#include <iostream>
#include <string>
#include "utils.hpp"
#include <exception>

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


	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<Node<pair<const Key, T> > > >
	class map
	{
		public:
			typedef Key                                      	key_type;
			typedef T                                        	data_type;
			typedef pair<const key_type, data_type>   			value_type;
			typedef Compare                                  	key_compare;
			typedef Allocator                                	allocator_type;
			typedef value_type&       							reference;
			typedef const value_type&     						const_reference;


		private:
			typedef _map_value_compare<key_type, value_type, key_compare> _vc;
			typedef Node<value_type>							_Node;
			typedef __tree<value_type, _Node, _vc, allocator_type>   	_base;

			_base _tree;
		public:
			/****************** MEMBER TYPES ******************/
			typedef typename allocator_type::pointer         	pointer;
			typedef typename allocator_type::const_pointer   	const_pointer;
			typedef typename allocator_type::size_type       	size_type;
			typedef typename allocator_type::difference_type 	difference_type;
			typedef typename _base::iterator					iterator;
			typedef typename _base::const_iterator				const_iterator;
			typedef ft::reverse_iterator<iterator>         		reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>    	const_reverse_iterator;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
				friend class map;
			protected:
				key_compare comp;
				value_compare(key_compare c) : comp(c) {}
			public:
				bool operator()(const value_type& x, const value_type& y) const {return comp(x.first, y.first);}
		}; //value compare


		class out_of_range: public std::out_of_range
		{
			friend class map;
			public:
				out_of_range(std::string msg) : std::out_of_range(msg) {};
		};

							/********************************    COSTRUCTORS    ********************************/

		public: 
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(_vc(comp)), _base::allocator_type(alloc) {}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& a = allocator_type()) : _tree(_vc(comp))
		{
			_tree.get_alloc() = a;
			insert(first, last);
		}
		map(const map& m) : _tree(m._tree) { insert(m.begin(), m.end()); }
		~map(){}
		map& operator=(const map& m)
		{
			if (this != &m)
			{
				_tree.clear();
				_tree.value_comp() = m._tree.value_comp();
				_tree.__node_alloc() = m._tree.__node_alloc();
				insert(m.begin(), m.end());
			}
			return *this;
		}

							/********************************      ITERATOR     ********************************/

		iterator 		begin(){ return (iterator)_tree.begin(); }
		const_iterator 	begin() const { return (const_iterator)_tree.cbegin(); }
		iterator 		end(){	return (iterator)_tree.end();}
		const_iterator 	end()   const {	return (const_iterator)_tree.end();}

		reverse_iterator 		rbegin() { return (reverse_iterator(_tree.end())); }
		const_reverse_iterator 	rbegin() const { return (const_reverse_iterator(_tree.end())); }
		reverse_iterator 		rend() 	{ return (reverse_iterator(_tree.begin())); }
		const_reverse_iterator	rend()   const { return (const_reverse_iterator(_tree.begin())); }


							/********************************      CAPACITY     ********************************/

		bool      empty()    const { return _tree.size() == 0; }
		size_type size()     const { return _tree.size(); }
		size_type max_size() const { return _tree.max_size(); }

							/********************************   ELEMENT ACCESS   ********************************/

		data_type& 		operator[](const key_type& k)
		{
			iterator i = find(k);
			if (i != end())
				return (*i).second;
			const std::pair<const key_type, data_type> miao;
			data_type d;

			_tree.insert(i, miao);
			return (*i).second;
		}

							/********************************   	MODIFIERS     ********************************/

		pair<iterator, bool> 	insert(const value_type& v) { return _tree.insert(v); }
		iterator 					insert(iterator position, const value_type& v) { return _tree.insert(position, v); }
		template <class InputIterator>
			void 					insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			{
				for (iterator i = end(); first != last; ++first)
					insert(i, *first);
			}

		void		erase(iterator position) { return _tree.erase(position); }
		size_type 	erase(const key_type& k) { return _tree.erase(k); }
		void		erase(iterator first, iterator last) { return _tree.erase(first, last); }
		void 		clear() { return _tree.clear(); }
		void 		swap (map& x) { return _tree.swap(x); }

							/********************************   	OBSERVER    ********************************/

		allocator_type get_allocator() const { return _tree.__node_alloc(); }
		key_compare    key_comp()      const { return key_comp(); }
		value_compare  value_comp()    const { return _tree.value_comp(); }

							/********************************    MAP OPERATIONS   ********************************/

		iterator 		find(const key_type& k) { return _tree.find(k); }
		const_iterator 	find(const key_type& k) const { return _tree.find(k); }

		size_type      	count(const key_type& k) const { return _tree.count(k); }

		iterator 		lower_bound(const key_type& k) { return (iterator)_tree.lower_bound(k); }
		const_iterator 	lower_bound(const key_type& k) const { return (const_iterator)_tree.lower_bound(k); }

		iterator 		upper_bound(const key_type& k) { return _tree.upper_bound(k); }
		const_iterator 	upper_bound(const key_type& k) const { return _tree.upper_bound(k); }


		pair<iterator,iterator>             equal_range(const key_type& k) { return _tree.equal_range(k); }
		pair<const_iterator,const_iterator> equal_range(const key_type& k) const { return _tree.equal_range(k); }

	}; //map

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator==(const map<Key, T, Compare, Allocator>& x,
			const map<Key, T, Compare, Allocator>& y)
	{
   		return x.size() == y.size() && (!ft::lexicographical_compare(x.begin(), x.end(), y.begin()));
	}

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator< (const map<Key, T, Compare, Allocator>& x,
			const map<Key, T, Compare, Allocator>& y)
	{
    	return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator!=(const map<Key, T, Compare, Allocator>& x,
			const map<Key, T, Compare, Allocator>& y)
	{
   		return !(x == y);
	}		

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator> (const map<Key, T, Compare, Allocator>& x,
			const map<Key, T, Compare, Allocator>& y)
	{
		return (y < x);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator>=(const map<Key, T, Compare, Allocator>& x,
			const map<Key, T, Compare, Allocator>& y)
	{
		return !(x < y);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator<=(const map<Key, T, Compare, Allocator>& x,
			const map<Key, T, Compare, Allocator>& y)
	{
		return !(y < x);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) { return x.swap(y); }


	//TODO fare pair e sostituire gli std


}



#endif