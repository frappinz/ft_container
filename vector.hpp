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
		size_t size() { return (_size);}
		size_t capacity() {return (_capacity);}
		bool empty() const {
			if (_capacity == 0)
				return (true);
			return(false);
		}
		void reserve( size_type new_cap ){
			_capacity = new_cap; 
			//If new_cap is greater than capacity(), all iterators, including the past-the-end iterator, 
			//and all references to the elements are invalidated. Otherwise, no iterators or references are invalidated.
		}
		size_type max_size() const{ return (std::distance(begin(), end())); }
		explicit vector(const allocator_type& alloc = allocator_type()):  _vector(nullptr), _size(0), _capacity(0){};
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		{

		}
		template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
		{

		}
		vector (const vector& x)
		{

		}

	private:
		size_t _size;
		size_t _capacity;
		pointer _vector;
		Allocator _alloc;
		//iterator it;

	};


} // namespace ft












#endif