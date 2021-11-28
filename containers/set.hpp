#pragma once

#include "../containers/RBtree.hpp"

#include <set>
​
namespace ft
{
	template<typename _Key, typename _Compare = std::less<_Key>, class Allocator = std::allocator<_Key> >
	class set
	{
		public:
		typedef _Key     value_type;
		typedef _Compare key_compare;
		typedef _Compare value_compare;
		typedef Allocator   allocator_type;

		private:
			typedef _tree<value_type, key_compare, allocator_type> base;
			base				tree;
	​
		public:
		typedef typename allocator_type::pointer		 	pointer;
		typedef typename allocator_type::const_pointer	 	const_pointer;
		typedef typename allocator_type::reference		 	reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename base::iterator	 					iterator;
		typedef typename base::const_iterator	 			const_iterator;
		typedef typename base::const_reverse_iterator 		reverse_iterator;
		typedef typename base::const_reverse_iterator 		const_reverse_iterator;
		typedef typename base::size_type		 			size_type;
		typedef typename base::difference_type	 			difference_type;
	​
		explicit set(const _Compare& __comp, const allocator_type& __a = allocator_type())
		: tree(__comp, allocator_type(__a)) { }
	​
		template<typename _InputIterator>
		set(_InputIterator __first, _InputIterator __last, const _Compare& __comp, const allocator_type& __a = allocator_type())
		: tree(__comp, allocator_type(__a))
		{ tree.insert(__first, __last); }
	​
		~set() {};
	​
		set( const set& other )
		{
			*this = other;
		}
	​
		set&operator=(const set &other): 
		{
			tree = other.tree;
		}
​
	
		iterator 		begin()	{ return (iterator)tree.begin(); }
		const_iterator 	begin() const { return (const_iterator)tree.cbegin(); }
		iterator 		end(){	return (iterator)tree.end();}
		const_iterator 	end()   const {	return (const_iterator)tree.cend();}

		reverse_iterator 		rbegin() { return (reverse_iterator(tree.end())); }
		const_reverse_iterator 	rbegin() const { return (const_reverse_iterator(tree.cend())); }
		reverse_iterator 		rend() 	{ return (reverse_iterator(tree.begin())); }
		const_reverse_iterator	rend()   const { return (const_reverse_iterator(tree.cbegin())); }


							/********************************      CAPACITY     ********************************/

		bool      empty()    const { return tree.size() == 0; }
		size_type size()     const { return tree.size(); }
		size_type max_size() const { return tree.max_size(); }

							/********************************   	MODIFIERS     ********************************/

		pair<iterator, bool> 	insert(const value_type& v) { return tree.insert(v); }
		iterator 					insert(iterator position, const value_type& v) { return tree.insert(position, v); }
		template <class InputIterator>
			void insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			{
				for (; first != last; ++first)
					insert(*first);
			}

		void		erase(iterator position) { tree.erase_position(position); }
		size_type 	erase(const key_type& k) { return tree.erase_key(k); }
		void		erase(iterator first, iterator last) { tree.erase_range(first, last); }
		void 		clear() { return tree.clear(); }
		void 		swap (map& x) { return tree.swap(x.tree); }

							/********************************   	OBSERVER    ********************************/

		allocator_type get_allocator() const { return tree.__node_alloc(); }
		key_compare    key_comp()      const { return tree.value_comp().key_comp(); }
		value_compare  value_comp()    const { return value_compare(tree.value_comp().key_comp()); }

							/********************************    SET OPERATIONS   ********************************/

		iterator 		find(const key_type& k) { return tree.find(k); }
		const_iterator 	find(const key_type& k) const { return tree.find(k); }

		size_type      	count(const key_type& k) const { return tree.count(k); }

		iterator 		lower_bound(const key_type& k) { return (iterator)tree.lower_bound(k); }
		const_iterator 	lower_bound(const key_type& k) const { return (const_iterator)tree.lower_bound(k); }

		iterator 		upper_bound(const key_type& k) { return tree.upper_bound(k); }
		const_iterator 	upper_bound(const key_type& k) const { return tree.upper_bound(k); }


		pair<iterator,iterator>             equal_range(const key_type& k) { return tree.equal_range(k); }
		pair<const_iterator,const_iterator> equal_range(const key_type& k) const { return tree.equal_range(k); }

	}; //set

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator< (const set<_Key, _Compare, Allocator>& x, const set<_Key, _Compare, Allocator>& y)
	{
    	return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator==(const set<_Key, _Compare, Allocator>& x,
			const set<_Key, _Compare, Allocator>& y)
	{
   		return x.size() == y.size() && !(x<y) && !(y<x);
	}


	template <class Key, class T, class Compare, class Allocator>
	bool
	operator!=(const set<_Key, _Compare, Allocator>& x,
			const set<_Key, _Compare, Allocator>& y)
	{
   		return !(x == y);
	}		

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator> (const set<_Key, _Compare, Allocator>& x,
			const set<_Key, _Compare, Allocator>& y)
	{
		return (y < x);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator>=(const set<_Key, _Compare, Allocator>& x,
			const set<_Key, _Compare, Allocator>& y)
	{
		return !(x < y);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator<=(const set<_Key, _Compare, Allocator>& x,
			const set<_Key, _Compare, Allocator>& y)
	{
		return !(y < x);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) { return x.swap(y); }
​
}//namespace