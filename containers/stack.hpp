#ifndef STACK_HPP
#define STACK_HPP


#include "vector.hpp"
#include <stack>
namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef Container                                container_type;
		typedef typename container_type::value_type      value_type;
		typedef typename container_type::reference       reference;
		typedef typename container_type::const_reference const_reference;
		typedef typename container_type::size_type       size_type;

	protected:
		container_type _c;

	public:
		stack() : _c() {}
		explicit stack(const container_type& c) : _c(c){}
		~stack() {}

		stack(const stack& q) : _c(q._c) {}

		stack& operator=(const stack& q) { _c = q._c; return *this;}
 
		bool empty() const { return _c.empty(); }
		size_type size() const { return _c.size(); }
		reference top() { return _c.back(); }
		const_reference top() const { return _c.back(); }

		void push(const value_type& x) { _c.push_back(x); }
		void pop() { _c.pop_back(); }
		template <class T1, class _C1>
		friend bool operator==(const stack<T1, _C1>& __x, const stack<T1, _C1>& __y);

		template <class T1, class _C1>
		friend bool operator< (const stack<T1, _C1>& __x, const stack<T1, _C1>& __y);
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container>& x, const stack<T, Container>& y)
	{
		return (x._c == y._c);
	}
	template <class T, class Container>
	bool operator< (const stack<T, Container>& x, const stack<T, Container>& y)
	{
		return (x._c < y._c);
	}
	template <class T, class Container>
	bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y)
	{
		return (!(x == y));
	}
	template <class T, class Container>
	bool operator> (const stack<T, Container>& x, const stack<T, Container>& y)
	{
		return (y < x);
	}
	template <class T, class Container>
	bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y)
	{
		return (!(x < y));
	}
	template <class T, class Container>
	bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y)
	{
		return (!(y < x));
	}

} //namespace




#endif