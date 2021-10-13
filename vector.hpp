#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <algorithm>
#include <memory>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <iterator>
#include <vector>
  



namespace ft 
{
  template < class T, class Allocator = std::allocator<T> > 
  class vector 
  {
  	public:
   	 	// types
		typedef T                                        	value_type;
		typedef Allocator                                	allocator_type;
		typedef typename allocator_type::reference       	reference;
		typedef typename allocator_type::const_reference 	const_reference;
		typedef typename allocator_type::pointer         	pointer;
		typedef typename allocator_type::const_pointer  	const_pointer;
		typedef typename allocator_type::size_type       	size_type;
		//typedef vector_iterator<pointer>					iterator;
		//typedef vector_iterator <const_pointer>				const_iterator;
		//typedef std::reverse_iterator<iterator>    			const_reverse_iterator;
		typedef typename allocator_type::difference_type 	difference_type;
		//typedef std::reverse_iterator<iterator>         	reverse_iterator;

		const_reference operator[]( size_type pos ) const { return (this->_begin[pos]); }
		reference operator[]( size_type pos )  { return (this->_begin[pos]); }

		size_t size() { return (_size); }
		size_t capacity() { return (_capacity); }
		bool empty() const { return(_capacity == 0); }
		// vector<_Tp, _Allocator>::resize(size_type __sz)
		// {
		// 	size_type __cs = size();
		// 	if (__cs < __sz) // size < nuova capacity
		// 		this->__append(__sz - __cs);
		// 	else if (__cs > __sz)
		// 		this->__destruct_at_end(this->__begin_ + __sz);
		// }

		//template <class _Tp, class _Allocator>
		// void vector<_Tp, _Allocator>::reserve(size_type __n)
		// {
		// 	if (__n > capacity())
		// 	{
		// 		allocator_type& __a = this->__alloc();
		// 		__split_buffer<value_type, allocator_type&> __v(__n, size(), __a);
		// 		__swap_out_circular_buffer(__v);
		// 	}
		// }
		// void reserve( size_type new_cap )
		// {
		// 	if (new_cap > _capacity)
		// 	{
		// 		_capacity = new_cap;

		// 	}
	
		// 	//If new_cap is greater than capacity(), all iterators, including the past-the-end iterator, 
		// 	//and all references to the elements are invalidated. Otherwise, no iterators or references are invalidated.
		// }
		//size_type max_size() const{ return (std::distance(begin(), end())); }
		
		// COSTRUTTORIIIIIIIIIII
		explicit vector(const allocator_type& alloc = allocator_type())
			:	_size(0),
				_capacity(0),
				_begin(nullptr),
				_end(nullptr),
				_alloc(alloc)
		{
		}
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _size(n), _alloc(alloc)
		{
			allocator_type cicc;
			Allocator cc;
			
			if (n > 0)
			{
				_capacity = _size*2;
				_begin = _alloc.allocate(_capacity);
				for(size_t i = 0; i < n; i++)
					_begin[i] = val;
			}
	
		}
		// template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
		// {

		// }
		vector (const vector& x)
		{

		}

	private:
		size_t _size;
		size_t _capacity;
		pointer _begin;
		pointer _end;
		Allocator _alloc;

	};


} // namespace ft












#endif