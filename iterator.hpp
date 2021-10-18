#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iostream>
#include <iterator>

namespace ft
{

	struct input_iterator_tag  {};
	struct output_iterator_tag {};
	struct forward_iterator_tag       : public input_iterator_tag         {};
	struct bidirectional_iterator_tag : public forward_iterator_tag       {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class Iterator> 
	struct iterator_traits
	{
		typedef typename Iterator::difference_type 				difference_type;
		typedef typename Iterator::value_type 					value_type;
		typedef typename Iterator::pointer 						pointer;
		typedef typename Iterator::reference 					reference;
		typedef typename Iterator::iterator_category 			iterator_category;
	};

	template<class T> struct iterator_traits<T*>
	{
		typedef ptrdiff_t 					difference_type;
		typedef T 							value_type;
		typedef T* 							pointer;
		typedef T& 							reference;
		typedef random_access_iterator_tag 	iterator_category;
	};
	
	template<class Category, class T, class Distance = ptrdiff_t,
         class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

	/**************** REVERSE ITERATOR ****************/

	template <class Iterator>
	class reverse_iterator
		: public iterator<typename iterator_traits<Iterator>::iterator_category,
						typename iterator_traits<Iterator>::value_type,
						typename iterator_traits<Iterator>::difference_type,
						typename iterator_traits<Iterator>::pointer,
						typename iterator_traits<Iterator>::reference>
	{
	protected:
		Iterator current;
	public:
		typedef Iterator                                            iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::reference       reference;
		typedef typename iterator_traits<Iterator>::pointer         pointer;

		reverse_iterator() : current() {}
		explicit reverse_iterator(Iterator x) : current(x) {}
		template <class U> reverse_iterator(const reverse_iterator<U>& u) : current(u.base()) {}
		template <class U> reverse_iterator& operator=(const reverse_iterator<U>& u) { current = u.current; return *this; }
		Iterator base() const { return current; };
		reference operator*() const { Iterator tmp = current; return *--tmp; };
		pointer   operator->() const { return &(operator*()); }
		reverse_iterator& operator++() {  --current; return *this; }
		reverse_iterator  operator++(int) { reverse_iterator __tmp(*this); --current; return __tmp; }
		reverse_iterator& operator--() { ++current; return *this; }
		reverse_iterator  operator--(int) { reverse_iterator __tmp(*this); ++current; return __tmp; }
		reverse_iterator  operator+ (difference_type n) const { return reverse_iterator(current - n); }
		reverse_iterator& operator+=(difference_type n) { current -= n; return *this; }
		reverse_iterator  operator- (difference_type n) const { return reverse_iterator(current + n);}
		reverse_iterator& operator-=(difference_type n) { current += n; return *this; }
		reference         operator[](difference_type n) const { return *(*this + n); }
	};
	template <class Iterator>
  	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() == rhs.base();}
	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() != rhs.base(); }
	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() > rhs.base(); }
	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() >= rhs.base(); }
	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() < rhs.base(); }
	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() <= rhs.base(); }
	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n,const reverse_iterator<Iterator>& rev_it)
	{
		return reverse_iterator<Iterator>(rev_it.base() - n);
	}
	template <class Iterator> 
	typename reverse_iterator<Iterator>::difference_type
	operator-(const reverse_iterator<Iterator>& __x, const reverse_iterator<Iterator>& __y)
	{
		return __y.base() - __x.base();
	}



	/**************** ITERATOR ****************/
	template <class Iterator>
	class base_iterator
		: public iterator<typename iterator_traits<Iterator>::iterator_category,
						typename iterator_traits<Iterator>::value_type,
						typename iterator_traits<Iterator>::difference_type,
						typename iterator_traits<Iterator>::pointer,
						typename iterator_traits<Iterator>::reference>
	{
	protected:
		Iterator current;
	public:
		typedef Iterator                                            iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::reference       reference;
		typedef typename iterator_traits<Iterator>::pointer         pointer;

		base_iterator() : current(nullptr) {}
		explicit base_iterator(Iterator x) : current(x) {}
		template <class U> base_iterator(const base_iterator<U>& u) : current(u.base()) {}
		template <class U> base_iterator& operator=(const base_iterator<U>& u) { current = u.current; return *this; }
		Iterator base() const { return current; };
		reference operator*() const { Iterator tmp = current; return *--tmp; }; //??
		pointer   operator->() const { return &(operator*()); }
		base_iterator& operator++() {  ++current; return *this; } //fatto
		base_iterator  operator++(int) { base_iterator __tmp(*this); ++current; return __tmp; } //fatto
		base_iterator& operator--() { --current; return *this; } //fatto
		base_iterator  operator--(int) { base_iterator __tmp(*this); --current; return __tmp; } //fatto
		base_iterator  operator+ (difference_type n) const { return base_iterator(current + n); }
		base_iterator& operator+=(difference_type n) { current += n; return *this; }
		base_iterator  operator- (difference_type n) const { return base_iterator(current - n);}
		base_iterator& operator-=(difference_type n) { current -= n; return *this; }
		reference operator[](difference_type n) const { return *(*this + n); }
	};
	template <class Iterator>
  	bool operator== (const base_iterator<Iterator>& lhs, const base_iterator<Iterator>& rhs) { return lhs.base() == rhs.base();}
	template <class Iterator>
	bool operator!= (const base_iterator<Iterator>& lhs, const base_iterator<Iterator>& rhs) { return lhs.base() != rhs.base(); }
	template <class Iterator>
	bool operator<  (const base_iterator<Iterator>& lhs, const base_iterator<Iterator>& rhs) { return lhs.base() > rhs.base(); }
	template <class Iterator>
	bool operator<= (const base_iterator<Iterator>& lhs, const base_iterator<Iterator>& rhs) { return lhs.base() >= rhs.base(); }
	template <class Iterator>
	bool operator>  (const base_iterator<Iterator>& lhs, const base_iterator<Iterator>& rhs) { return lhs.base() < rhs.base(); }
	template <class Iterator>
	bool operator>= (const base_iterator<Iterator>& lhs, const base_iterator<Iterator>& rhs) { return lhs.base() <= rhs.base(); }
	template <class Iterator>
	base_iterator<Iterator> operator+ (typename base_iterator<Iterator>::difference_type n,const base_iterator<Iterator>& rev_it)
	{
		return base_iterator<Iterator>(rev_it.base() + n);
	}
	template <class Iterator> 
	typename base_iterator<Iterator>::difference_type
	operator-(const base_iterator<Iterator>& __x, const base_iterator<Iterator>& __y)
	{
		return __y.base() - __x.base();
	}
	
} //namespace ft
#endif