#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iostream>

namespace ft
{

template <class Category,              // iterator::iterator_category
          class T,                     // iterator::value_type
          class Distance = ptrdiff_t,  // iterator::difference_type
          class Pointer = T*,          // iterator::pointer
          class Reference = T&         // iterator::reference
          > 
class iterator
{
	typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;

};


template <class InputIterator, class Distance>
	void advance (InputIterator& it, Distance n)
  {
	  for (int i = 0; i < n; i++)
	  	it++;
  }

template<class InputIterator>
  typename std::iterator_traits<InputIterator>::difference_type
    distance (InputIterator first, InputIterator last) {return (last - first);}

}

#endif