#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
	template< bool B, class T = void >
	struct enable_if{};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template <class _Tp> struct is_integral                     : public std::false_type {};
	template <>          struct is_integral<bool>               : public std::true_type {};
	template <>          struct is_integral<char>               : public std::true_type {};
	template <>          struct is_integral<signed char>        : public std::true_type {};
	template <>          struct is_integral<unsigned char>      : public std::true_type {};
	template <>          struct is_integral<wchar_t>            : public std::true_type {};
	template <>          struct is_integral<char16_t>           : public std::true_type {};
	template <>          struct is_integral<char32_t>           : public std::true_type {};
	template <>          struct is_integral<short>              : public std::true_type {};
	template <>          struct is_integral<unsigned short>     : public std::true_type {};
	template <>          struct is_integral<int>                : public std::true_type {};
	template <>          struct is_integral<unsigned int>       : public std::true_type {};
	template <>          struct is_integral<long>               : public std::true_type {};
	template <>          struct is_integral<unsigned long>      : public std::true_type {};
	template <>          struct is_integral<long long>          : public std::true_type {};
	template <>          struct is_integral<unsigned long long> : public std::true_type {};
	template <>          struct is_integral<__int128_t>         : public std::true_type {};
	template <>          struct is_integral<__uint128_t>        : public std::true_type {};

	template< class InputIt1, class InputIt2 >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 )
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) 
		{
			if (*first1 < *first2) 
				return true;
			if (*first2 < *first1) 
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template< class InputIt1, class InputIt2, class Compare >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp )
	{
    	for (; first2 != last2; ++first1, (void) ++first2)
		{
			if (first1 == last1 || comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
   		}
    	return false;
	}

} //namespace



#endif