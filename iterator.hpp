#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iostream>

namespace ft
{

	template <class Iterator> class iterator_traits{};

	template <class Iterator>
  	struct iterator_traits
  	{
		typedef Iterator::difference_type   value_type;
		typedef Iterator::value_type		difference_type;
		typedef Iterator::pointer   		pointer;
		typedef Iterator::reference 		reference;
		typedef Iterator::iterator_category iterator_category;
  	};

	template <class T>
	class iterator_traits<T*>
	{
		typedef T         value_type;
		typedef ptrdiff_t  difference_type;
		typedef T*  pointer;
		typedef T& reference;
		typedef Iterator::random_access_iterator_tag  iterator_category;
	};

	template <class T>
	class iterator_traits<const T*>
	{
		typedef T         value_type;
		typedef ptrdiff_t  difference_type;
		typedef const T*  pointer;
		typedef const T& reference;
		typedef Iterator::random_access_iterator_tag  iterator_category;

	};
}

#endif