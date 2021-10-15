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
#include <stdexcept>

  



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

		class out_of_range : public std::exception 														//creato error (funzione at)
		{
			public:
				const char * what () const throw () { return ("out_of_range"); }
		};

		/****************** MEMBER FUNCTIONS ******************/

		explicit vector(const allocator_type& alloc = allocator_type())
			:	_size(0),
				_begin(nullptr),
				_capacity(0),
				_end(nullptr),
				_alloc(alloc)
		{ //cambiata l'allocazione di uno a buffo
		}
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _size(n), _alloc(alloc)
		{	
			if (n > 0)
			{
				_capacity = _size;
				_begin = _alloc.allocate(_capacity);
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
			if (n > _capacity && _begin!= nullptr) 									//aggiunta la seconda condizione
			{
				pointer tmp;
				tmp = _begin;
				_alloc.deallocate(_begin,_capacity);
				_capacity = n;
				_begin = _alloc.allocate(_capacity);
	
				for(size_t i = 0; i < _size; i++)
					_begin[i] = tmp[i];
			}
			else																	//e questo
				_begin = _alloc.allocate(n);

		}


		/***** ELEMENT ACCESS ****/
		reference operator[]( size_type pos )  { return (this->_begin[pos]); }
		const_reference operator[]( size_type pos ) const { return (this->_begin[pos]); }
      	reference at (size_type n){														//fatti questi tre
			if(n >= _size)
				throw(out_of_range());
			return (_begin[n]);
		}
		const_reference at (size_type n) const{
			if(n >= _size)
				throw(out_of_range());
			return (_begin[n]);
		}
		reference front(){ return _begin[0]; }
		const_reference front() const{ return _begin[0]; }


		/***** 	MODIFIERS ****/
		void clear(){this->_size = 0;}

		void push_back (const value_type& val) 										//modificata questa
		{
			_size++;
			if (_size > _capacity)
				reserve(_size * 2);
			_begin[_size - 1] = val;

			// size_t peppolonetiamoseilamiavita = _capacity;
			// if(_capacity -1 == _size)
			// 	_capacity = _capacity*2;
			
			// _size = _size + 1;
			// pointer tmp;

			// tmp = _alloc.allocate(_capacity);
			// for(int i =0; i < _size; i++)
			// {
			// 	tmp[i] = _begin[i]; 
			// }
			// tmp[_size] = val;
			// _alloc.deallocate(_begin, peppolone);
			// _begin = tmp;
		}


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
		

	private:
		size_t _size;
		size_t _capacity;
		pointer _begin;
		pointer _end;
		Allocator _alloc;

	};


} // namespace ft












#endif