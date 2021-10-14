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
   	 	/****************** MEMBER TYPES ******************/
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



		/****************** MEMBER FUNCTIONS ******************/
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
			if (n > 0)
			{
				_capacity = _size*2;
				_begin = _alloc.allocate(_capacity);
				std::cout << "siamo entrati \n";
				for(size_t i = 0; i < n; i++)
					_begin[i] = val;
			}
		}
		// template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
		// {

		// }
		vector (const vector& x){}
		~vector()
		{
			std::cout << "distruttore";
			if (_begin != nullptr)
				this->_alloc.deallocate(_begin, _capacity);
		}

		vector& operator=( const vector& other ){ 
			_begin = other._begin;
			_alloc = other._alloc;
			_end = other._end;
			_size = other._size;
			_capacity = other._capacity; 
			return(*this);
		}

		/***** ITERATOR *****/
		// iterator begin() {};
		// const_iterator begin() const {};
		// iterator end(){}
		// const_iterator end() const{}
		// reverse_iterator rbegin() {}
		// const_reverse_iterator rbegin() const {}
		// reverse_iterator rend() {}
		// const_reverse_iterator rend() const {}


		/***** CAPACITY *****/	
		size_t size() { return (_size); }
		size_type max_size() const { return ( _alloc.max_size()); }
		void resize (size_type n, value_type val = value_type()) //da rivedere quando facciamo append
		{
			if (n >= _size)
			{
				if (!val)
					val = 0;
				for (size_t i = _size; i < n; i++)
					_begin[i] = val;
			}
			_size = n;
		}
		size_t capacity() { return (_capacity); }
		bool empty() const { return(_capacity == 0); }
		void reserve( size_type n )
		{
			if (n > _capacity)
			{
				pointer tmp;
				tmp = _begin;
				_alloc.deallocate(_begin,_capacity);
				_capacity = n*2;
				_begin = _alloc.allocate(_capacity);
	
				for(size_t i = 0; i < _size; i++)
					_begin[i] = tmp[i];
				std::cout<< "distrutto\n";
			}
		}


		/***** ELEMENT ACCESS ****/
		reference operator[]( size_type pos )  { return (this->_begin[pos]); }
		const_reference operator[]( size_type pos ) const { return (this->_begin[pos]); }
      	reference at (size_type n){}
		const_reference at (size_type n) const{}		

		


		/***** 	MODIFIERS ****/
		void clear(){this->_size = 0;}


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
		// {
	
		// 	//If new_cap is greater than capacity(), all iterators, including the past-the-end iterator, 
		// 	//and all references to the elements are invalidated. Otherwise, no iterators or references are invalidated.
		// }
		
		// COSTRUTTORIIIIIIIIIII

	private:
		size_t _size;
		size_t _capacity;
		pointer _begin;
		pointer _end;
		Allocator _alloc;

	};


} // namespace ft












#endif