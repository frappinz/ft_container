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

namespace ft
{
			typedef typename allocator_type::pointer	pointer;
			typedef	T											value_type;
			typedef	Alloc										allocator_type;
			typedef	typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef	vector_iterator<pointer>					iterator;
			typedef	vector_iterator<const_pointer>				const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef std::ptrdiff_t								difference_type;
			typedef size_t										size_type;
	template <class T, class Alloc = std::allocator<T>>
	class vector
	{
		private:
			size_t _size;
			size_t _capacity;
			pointer _vector;
			Alloc _alloc;
			std::iterator it;
		public:
/*default*/ vector(const allocator_type& alloc = allocator_type()))
			{
				
			}
/*fill*/	explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
/*range*/	template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
/*copy*/	vector (const vector& x);
	};


} // namespace ft












#endif