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
#include "iterator.hpp"

  
//ti amo non dovresti lavorare con me sei troppo brava lascia peppolone e scappiamo

 /*.,,-~&,               ,~"~.
 { /`,__\`.             > ::::
{ `}'~.~/\ \           <, ?::;
{`}'\._/  ) }           l_  f
 ,__/ l_,'`/          ,__}--{_.
{  `.__.' (          /         }
 \ \    )  )        /          !
  \'\`-'`-'        /  ,    1  J;
   \ \___l,-_,___.'  /1    !  Y
    k____-~'-l_____.' |    l /
   /===#=l            l     f
  f      8            I===I=I
  t    ! 8            f     }
   Y    \l            |     }
    \    \            l    Y;
     `.   \           }    |
      !`,  \          |    |
      l /   }        ,1    |
      l/   /         !l   ,l
      /  ,'          ! \    \
     /  /!           !  \    \
    /_,f_l           l___j.   \
   (_ \l_ `_     ,.-'`--(  `.,'`.
    Y\__Y`--'    `-'~x__J    j'  >
                           ,/ ,^'
                          f__J
						  
						        ,;;;;;,
       ,;;;;;;;;,
       ;;;'____ ;
       ;;;(\\\\\;
       `/'((|||||
    ___<  C))||||
  ,'    \__(((||),
  |    \  _)))))))\,_
 /|    |/"\`\`""""' |)
;  \    \  ) \_____/_|
|  |\    \'    _.,-' |
|  ' \    \.,-'   _./ |
(  _,-\      _.-''  |  ;
 "'|___\__.-'       ;  )
    |----|   _.--,;'   ;
   ,'  , | (     __.,-'
   | ,' ,'  `""''   `.
   |    ;            )
   `,   (            )
    |   (           ,'
    |   |           (
    |   |           |
    |   |           |
    |   |___________|
    |   |      |    |
	
	         .,,,,,,,,,,.
         ,;;;;;;;;;;;;;;,
       ,;;;;;;;;;;;)));;(((,,;;;,,_
      ,;;;;;;;;;;'      |)))))))))))\\
      ;;;;;;/ )''    - /,)))((((((((((\
      ;;;;' \        ~|\  ))))))))))))))
      /     /         |   ((((((((((((((
    /'      \      _/~'    ')|()))))))))
  /'         `\   />     o_/)))((((((((
 /          /' `~~(____ /  ()))))))))))
|     ---,   \        \     ((((((((((
          `\   \~-_____|      ))))))))
            `\  |      |_.---.  \*/


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
		typedef ft::base_iterator<pointer>					iterator;
		typedef ft::base_iterator<const_pointer>			const_iterator;
		typedef ft::reverse_iterator<iterator>    			const_reverse_iterator;
		typedef typename allocator_type::difference_type 	difference_type;
		typedef ft::reverse_iterator<iterator>         		reverse_iterator;

		class out_of_range : public std::exception
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
		{
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
		vector (const vector& x){ *this = x; }
		~vector()
		{
			if (_begin != nullptr && *_begin != 0)
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

		iterator begin() {
			return iterator(_begin + 1); //da controllare sta roba che é una cafonata
		}
		const_iterator begin() const {};
		iterator end(){
			return iterator(_begin + _size + 1); // e pure questa
		}
		const_iterator end() const{}
		reverse_iterator rbegin() {}
		const_reverse_iterator rbegin() const {}
		reverse_iterator rend() {}
		const_reverse_iterator rend() const {}


		/***** CAPACITY *****/	
		bool empty() const { return(_capacity == 0); }
		size_t size() const { return (_size); }
		size_type max_size() const { return ( _alloc.max_size()); }
		void reserve( size_type n )
		{
			if (n > _capacity && _begin!= nullptr)
			{
				pointer tmp;
				tmp = _begin;
				_alloc.deallocate(_begin,_capacity);
				_capacity = n;
				_begin = _alloc.allocate(_capacity);
	
				for(size_t i = 0; i < _size; i++)
					_begin[i] = tmp[i];
			}
			else
			{
				_begin = _alloc.allocate(n);
				_capacity = n;
			}

		}
		size_t capacity() const { return (_capacity); }


		/***** ELEMENT ACCESS ****/
		reference operator[]( size_type pos )  { return (this->_begin[pos]); }
		const_reference operator[]( size_type pos ) const { return (this->_begin[pos]); }
      	reference at (size_type n){
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
		const_reference front() const { return _begin[0]; }
		reference back(){ return _begin[_size - 1]; }
		const_reference back() const { return _begin[_size - 1]; }


		/***** 	MODIFIERS ****/

		// void assign (InputIterator first, InputIterator last)
		// {

		// }
		void assign (size_type n, const value_type& val)
		{
			if (n > _capacity)
				reserve(n * 2);
			_size = n;
			for (size_t i = 0; i < _size; i++)
				_begin[i] = val;
		}
		void push_back (const value_type& val)
		{
			_size++;
			if (_size > _capacity)
				reserve(_size * 2);
			_begin[_size - 1] = val;
		}
		void pop_back(){ _size--; }
		void resize (size_type n, value_type val = value_type())
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

		// iterator insert (iterator position, const value_type& val);
		// void insert (iterator position, size_type n, const value_type& val);
		// template <class InputIterator>
    	// 	void insert (iterator position, InputIterator first, InputIterator last);
		// iterator erase (iterator position);
		// iterator erase (iterator first, iterator last);

		void swap (vector& x){
			ft::vector<T> tmp;
			tmp._begin = this->_begin;
			tmp._alloc = this->_alloc;
			tmp._size = this->_size;
			tmp._capacity = this->_capacity;
			this->_begin = x._begin;
			this->_alloc = x._alloc;
			this->_size = x._size;
			this->_capacity = x._capacity;
			x._begin = tmp._begin;
			x._alloc = tmp._alloc;
			x._size = tmp._size;
			x._capacity = tmp._capacity;
		}
		void clear(){this->_size = 0;}

		allocator_type get_allocator() const { return this->_alloc; }
	private:
		size_t _size;
		size_t _capacity;
		pointer _begin;
		pointer _end;
		Allocator _alloc;
  	};
	
	
	template <class T, class Alloc> void swap (vector<T,Alloc>& x, vector<T,Alloc>& y){ x.swap(y); }
	

	/************* OPERATOR OVERLOAD ************/

	template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			if (lhs.size() == rhs.size())
			{
				for (size_t i = 0; i < lhs.size(); i++)
				{
					if (lhs.at(i) != rhs.at(i))
						return (false);
				}
				return (true);
			}
			return (false);
		}

	template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){ return (!(lhs == rhs)); }

	template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() < rhs.size())
			return true;
		if (lhs.size() > rhs.size())
			return false;
		
		for (size_t i = 0; i < lhs.size(); i++)
		{
			if (lhs.at(i) >= rhs.at(i))
				return (false);
		}
		return (true);
	}

	template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() > rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); i++)
		{
			if (lhs.at(i) > rhs.at(i))
				return (false);
		}
		return (true);
	}
		
	template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs <= rhs)); }
		
	template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs < rhs)); }
		
} // namespace ft


#endif