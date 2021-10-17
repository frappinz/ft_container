#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iostream>
#include <iterator>

namespace ft
{
public:
	template< class Category, class T,  class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& > 
	struct iterator;
	template <class I>
	  struct iterator_traits {
    typedef Category	iterator_category ;
    typedef T			value_type        ;
    typedef Distance	difference_type   ;
    typedef T*			pointer           ;
    typedef T&			reference         ;


}
#endif