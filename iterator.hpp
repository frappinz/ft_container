#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iostream>

namespace ft
{

	// template <class Iterator> class iterator_traits{};

	// template <class Iterator>
  	// struct iterator_traits
  	// {
	// 	typedef Iterator::difference_type   value_type;
	// 	typedef Iterator::value_type		difference_type;
	// 	typedef Iterator::pointer   		pointer;
	// 	typedef Iterator::reference 		reference;
	// 	typedef Iterator::iterator_category iterator_category;
  	// };

	// template <class T>
	// class iterator_traits<T*>
	// {
	// 	typedef T         value_type;
	// 	typedef ptrdiff_t  difference_type;
	// 	typedef T*  pointer;
	// 	typedef T& reference;
	// 	typedef Iterator::random_access_iterator_tag  iterator_category;
	// };

	// template <class T>
	// class iterator_traits<const T*>
	// {
	// 	typedef T         value_type;
	// 	typedef ptrdiff_t  difference_type;
	// 	typedef const T*  pointer;
	// 	typedef const T& reference;
	// 	typedef Iterator::random_access_iterator_tag  iterator_category;

	// };

#include <compare>
#include <concepts>
 
namespace ft {
  template<class T> using /*with-reference*/ = T&;  // exposition only
  template<class T> concept /*can-reference*/       // exposition only
    = requires { typename /*with-reference*/<T>; };
  template<class T> concept /*dereferenceable*/     // exposition only
    = requires(T& t) {
      { *t } -> /*can-reference*/;  // not required to be equality-preserving
    };
 
  // associated types
  // incrementable traits
  template<class> struct incrementable_traits;
  template<class T>
    using iter_difference_t = /* see description */;
 
  // indirectly readable traits
  template<class> struct indirectly_readable_traits;
  template<class T>
    using iter_value_t = /* see description */;
 
  // iterator traits
  template<class I> struct iterator_traits;
  template<class T> requires is_object_v<T> struct iterator_traits<T*>;
 
  template</*dereferenceable*/ T>
    using iter_reference_t = decltype(*declval<T&>());
 
  namespace ranges {
    // customization point objects
    inline namespace /* unspecified */ {
      // ranges​::​iter_move
      inline constexpr /* unspecified */ iter_move = /* unspecified */;
 
      // ranges​::​iter_swap
      inline constexpr /* unspecified */ iter_swap = /* unspecified */;
    }
  }
 
  template</*dereferenceable*/ T>
    requires requires(T& t) {
      { ranges::iter_move(t) } -> /*can-reference*/;
    }
  using iter_rvalue_reference_t
    = decltype(ranges::iter_move(declval<T&>()));
 
  // iterator concepts
  // concept indirectly_readable
  template<class In>
    concept indirectly_readable = /* see description */;
 
  template<indirectly_readable T>
    using iter_common_reference_t =
      common_reference_t<iter_reference_t<T>, iter_value_t<T>&>;
 
  // concept indirectly_writable
  template<class Out, class T>
    concept indirectly_writable = /* see description */;
 
  // concept weakly_incrementable
  template<class I>
    concept weakly_incrementable = /* see description */;
 
  // concept incrementable
  template<class I>
    concept incrementable = /* see description */;
 
  // concept input_or_output_iterator
  template<class I>
    concept input_or_output_iterator = /* see description */;
 
  // concept sentinel_for
  template<class S, class I>
    concept sentinel_for = /* see description */;
 
  // concept sized_sentinel_for
  template<class S, class I>
    inline constexpr bool disable_sized_sentinel_for = false;
 
  template<class S, class I>
    concept sized_sentinel_for = /* see description */;
 
  // concept input_iterator
  template<class I>
    concept input_iterator = /* see description */;
 
  // concept output_iterator
  template<class I, class T>
    concept output_iterator = /* see description */;
 
  // concept forward_iterator
  template<class I>
    concept forward_iterator = /* see description */;
 
  // concept bidirectional_iterator
  template<class I>
    concept bidirectional_iterator = /* see description */;
 
  // concept random_access_iterator
  template<class I>
    concept random_access_iterator = /* see description */;
 
  // concept contiguous_iterator
  template<class I>
    concept contiguous_iterator = /* see description */;
 
  // indirect callable requirements
  // indirect callables
  template<class F, class I>
    concept indirectly_unary_invocable = /* see description */;
 
  template<class F, class I>
    concept indirectly_regular_unary_invocable = /* see description */;
 
  template<class F, class I>
    concept indirect_unary_predicate = /* see description */;
 
  template<class F, class I1, class I2>
    concept indirect_binary_predicate = /* see description */;
 
  template<class F, class I1, class I2 = I1>
    concept indirect_equivalence_relation = /* see description */;
 
  template<class F, class I1, class I2 = I1>
    concept indirect_strict_weak_order = /* see description */;
 
  template<class F, class... Is>
    requires (indirectly_readable<Is> && ...) && invocable<F, iter_reference_t<Is>...>
      using indirect_result_t = invoke_result_t<F, iter_reference_t<Is>...>;
 
  // projected
  template<indirectly_readable I, indirectly_regular_unary_invocable<I> Proj>
    struct projected;
 
  template<weakly_incrementable I, class Proj>
    struct incrementable_traits<projected<I, Proj>>;
 
  // common algorithm requirements
  // concept indirectly_movable
  template<class In, class Out>
    concept indirectly_movable = /* see description */;
 
  template<class In, class Out>
    concept indirectly_movable_storable = /* see description */;
 
  // concept indirectly_copyable
  template<class In, class Out>
    concept indirectly_copyable = /* see description */;
 
  template<class In, class Out>
    concept indirectly_copyable_storable = /* see description */;
 
  // concept indirectly_swappable
  template<class I1, class I2 = I1>
    concept indirectly_swappable = /* see description */;
 
  // concept indirectly_comparable
  template<class I1, class I2, class R, class P1 = identity, class P2 = identity>
    concept indirectly_comparable = /* see description */;
 
  // concept permutable
  template<class I>
    concept permutable = /* see description */;
 
  // concept mergeable
  template<class I1, class I2, class Out,
      class R = ranges::less, class P1 = identity, class P2 = identity>
    concept mergeable = /* see description */;
 
  // concept sortable
  template<class I, class R = ranges::less, class P = identity>
    concept sortable = /* see description */;
 
  // primitives
  // iterator tags
  struct input_iterator_tag { };
  struct output_iterator_tag { };
  struct forward_iterator_tag: public input_iterator_tag { };
  struct bidirectional_iterator_tag: public forward_iterator_tag { };
  struct random_access_iterator_tag: public bidirectional_iterator_tag { };
  struct contiguous_iterator_tag: public random_access_iterator_tag { };
 
  // iterator operations
  template<class InputIt, class Distance>
    constexpr void advance(InputIt& i, Distance n);
  template<class InputIt>
    constexpr typename iterator_traits<InputIt>::difference_type
      distance(InputIt first, InputIt last);
  template<class InputIt>
    constexpr InputIt
      next(InputIt x, typename iterator_traits<InputIt>::difference_type n = 1);
  template<class BidirIt>
    constexpr BidirIt
      prev(BidirIt x, ypename iterator_traits<BidirIt>::difference_type n = 1);
 
  // range iterator operations
  namespace ranges {
    // ranges​::​advance
    template<input_or_output_iterator I>
      constexpr void advance(I& i, iter_difference_t<I> n);
    template<input_or_output_iterator I, sentinel_for<I> S>
      constexpr void advance(I& i, S bound);
    template<input_or_output_iterator I, sentinel_for<I> S>
      constexpr iter_difference_t<I> advance(I& i, iter_difference_t<I> n, S bound);
 
    // ranges​::​distance
    template<input_or_output_iterator I, sentinel_for<I> S>
      constexpr iter_difference_t<I> distance(I first, S last);
    template<range R>
      constexpr range_difference_t<R> distance(R&& r);
 
    // ranges​::​next
    template<input_or_output_iterator I>
      constexpr I next(I x);
    template<input_or_output_iterator I>
      constexpr I next(I x, iter_difference_t<I> n);
    template<input_or_output_iterator I, sentinel_for<I> S>
      constexpr I next(I x, S bound);
    template<input_or_output_iterator I, sentinel_for<I> S>
      constexpr I next(I x, iter_difference_t<I> n, S bound);
 
    // ranges​::​prev
    template<bidirectional_iterator I>
      constexpr I prev(I x);
    template<bidirectional_iterator I>
      constexpr I prev(I x, iter_difference_t<I> n);
    template<bidirectional_iterator I>
      constexpr I prev(I x, iter_difference_t<I> n, I bound);
  }
 
  // predefined iterators and sentinels
  // reverse iterators
  template<class It> class reverse_iterator;
 
  template<class It1, class It2>
    constexpr bool operator==(const reverse_iterator<It1>& x,
                              const reverse_iterator<It2>& y);
  template<class It1, class It2>
    constexpr bool operator!=(const reverse_iterator<It1>& x,
                              const reverse_iterator<It2>& y);
  template<class It1, class It2>
    constexpr bool operator<(const reverse_iterator<It1>& x,
                             const reverse_iterator<It2>& y);
  template<class It1, class It2>
    constexpr bool operator>(const reverse_iterator<It1>& x,
                             const reverse_iterator<It2>& y);
  template<class It1, class It2>
    constexpr bool operator<=(const reverse_iterator<It1>& x,
                              const reverse_iterator<It2>& y);
  template<class It1, class It2>
    constexpr bool operator>=(const reverse_iterator<It1>& x,
                              const reverse_iterator<It2>& y);
  template<class It1, three_way_comparable_with<It1> It2>
    constexpr compare_three_way_result_t<It1, It2>
      operator<=>(const reverse_iterator<It1>& x, const reverse_iterator<It2>& y);
 
  template<class It1, class It2>
    constexpr auto operator-(const reverse_iterator<It1>& x,
                             const reverse_iterator<It2>& y)
      -> decltype(y.base() - x.base());
  template<class It>
    constexpr reverse_iterator<It> operator+(iter_difference_t<It> n,
                                             const reverse_iterator<It>& x);
 
  template<class It>
    constexpr reverse_iterator<It> make_reverse_iterator(It i);
 
  template<class It1, class It2>
      requires (!sized_sentinel_for<It1, It2>)
    inline constexpr bool disable_sized_sentinel_for<reverse_iterator<It1>,
                                                     reverse_iterator<It2>> = true;
 
  // insert iterators
  template<class Container> class back_insert_iterator;
  template<class Container>
    constexpr back_insert_iterator<Container> back_inserter(Container& x);
 
  template<class Container> class front_insert_iterator;
  template<class Container>
    constexpr front_insert_iterator<Container> front_inserter(Container& x);
 
  template<class Container> class insert_iterator;
  template<class Container>
    constexpr insert_iterator<Container>
      inserter(Container& x, ranges::iterator_t<Container> i);
 
  // move iterators and sentinels
  template<class It> class move_iterator;
 
  template<class It1, class It2>
    constexpr bool operator==(const move_iterator<It1>& x, const move_iterator<It2>& y);
  template<class It1, class It2>
    constexpr bool operator<(const move_iterator<It1>& x, const move_iterator<It2>& y);
  template<class It1, class It2>
    constexpr bool operator>(const move_iterator<It1>& x, const move_iterator<It2>& y);
  template<class It1, class It2>
    constexpr bool operator<=(const move_iterator<It1>& x, const move_iterator<It2>& y);
  template<class It1, class It2>
    constexpr bool operator>=(const move_iterator<It1>& x, const move_iterator<It2>& y);
  template<class It1, three_way_comparable_with<It1> It2>
    constexpr compare_three_way_result_t<It1, It2>
      operator<=>(const move_iterator<It1>& x, const move_iterator<It2>& y);
 
  template<class It1, class It2>
    constexpr auto operator-(const move_iterator<It1>& x, const move_iterator<It2>& y)
      -> decltype(x.base() - y.base());
  template<class It>
    constexpr move_iterator<It>
      operator+(iter_difference_t<It> n, const move_iterator<It>& x);
 
  template<class It>
    constexpr move_iterator<It> make_move_iterator(It i);
 
  template<semiregular S> class move_sentinel;
 
  // common iterators
  template<input_or_output_iterator I, sentinel_for<I> S>
    requires (!same_as<I, S> && copyable<I>)
      class common_iterator;
 
  template<class I, class S>
    struct incrementable_traits<common_iterator<I, S>>;
 
  template<input_iterator I, class S>
    struct iterator_traits<common_iterator<I, S>>;
 
  // default sentinel
  struct default_sentinel_t;
  inline constexpr default_sentinel_t default_sentinel{};
 
  // counted iterators
  template<input_or_output_iterator I> class counted_iterator;
 
  template<input_iterator I>
    requires /* see description */
    struct iterator_traits<counted_iterator<I>>;
 
  // unreachable sentinel
  struct unreachable_sentinel_t;
  inline constexpr unreachable_sentinel_t unreachable_sentinel{};
 
  // stream iterators
  template<class T, class CharT = char, class Traits = char_traits<CharT>,
           class Distance = ptrdiff_t>
  class istream_iterator;
  template<class T, class CharT, class Traits, class Distance>
    bool operator==(const istream_iterator<T, CharT, Traits, Distance>& x,
                    const istream_iterator<T, CharT, Traits, Distance>& y);
 
  template<class T, class CharT = char, class traits = char_traits<CharT>>
      class ostream_iterator;
 
  template<class CharT, class Traits = char_traits<CharT>>
    class istreambuf_iterator;
  template<class CharT, class Traits>
    bool operator==(const istreambuf_iterator<CharT, Traits>& a,
                    const istreambuf_iterator<CharT, Traits>& b);
 
  template<class CharT, class Traits = char_traits<CharT>>
    class ostreambuf_iterator;
 
  // range access
  template<class C> constexpr auto begin(C& c) -> decltype(c.begin());
  template<class C> constexpr auto begin(const C& c) -> decltype(c.begin());
  template<class C> constexpr auto end(C& c) -> decltype(c.end());
  template<class C> constexpr auto end(const C& c) -> decltype(c.end());
  template<class T, size_t N> constexpr T* begin(T (&a)[N]) noexcept;
  template<class T, size_t N> constexpr T* end(T (&a)[N]) noexcept;
  template<class C> constexpr auto cbegin(const C& c) noexcept(noexcept(std::begin(c)))
    -> decltype(std::begin(c));
  template<class C> constexpr auto cend(const C& c) noexcept(noexcept(std::end(c)))
    -> decltype(std::end(c));
  template<class C> constexpr auto rbegin(C& c) -> decltype(c.rbegin());
  template<class C> constexpr auto rbegin(const C& c) -> decltype(c.rbegin());
  template<class C> constexpr auto rend(C& c) -> decltype(c.rend());
  template<class C> constexpr auto rend(const C& c) -> decltype(c.rend());
  template<class T, size_t N> constexpr reverse_iterator<T*> rbegin(T (&a)[N]);
  template<class T, size_t N> constexpr reverse_iterator<T*> rend(T (&a)[N]);
  template<class E> constexpr reverse_iterator<const E*> rbegin(initializer_list<E> il);
  template<class E> constexpr reverse_iterator<const E*> rend(initializer_list<E> il);
  template<class C> constexpr auto crbegin(const C& c) -> decltype(std::rbegin(c));
  template<class C> constexpr auto crend(const C& c) -> decltype(std::rend(c));
 
  template<class C> constexpr auto size(const C& c) -> decltype(c.size());
  template<class T, size_t N> constexpr size_t size(const T (&a)[N]) noexcept;
  template<class C> constexpr auto ssize(const C& c)
    -> common_type_t<ptrdiff_t, make_signed_t<decltype(c.size())>>;
  template<class T, ptrdiff_t N> constexpr ptrdiff_t ssize(const T (&a)[N]) noexcept;
  template<class C> [[nodiscard]] constexpr auto empty(const C& c) -> decltype(c.empty());
  template<class T, size_t N> [[nodiscard]] constexpr bool empty(const T (&a)[N]) noexcept;
  template<class E> [[nodiscard]] constexpr bool empty(initializer_list<E> il) noexcept;
  template<class C> constexpr auto data(C& c) -> decltype(c.data());
  template<class C> constexpr auto data(const C& c) -> decltype(c.data());
  template<class T, size_t N> constexpr T* data(T (&a)[N]) noexcept;
  template<class E> constexpr const E* data(initializer_list<E> il) noexcept;
}



}

#endif