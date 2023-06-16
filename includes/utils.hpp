#ifndef UTILS_HPP
#define UTILS_HPP

#include <iterator>
#include "iterator.hpp"
namespace ft{
template <typename Iter>
class vecIter;
template <bool , typename T>
struct enable_if {};

template <typename T>
struct enable_if<true, T>{
	typedef T type;
};

template <typename T, T v>
struct integral_constant
{
	static const T value = v;
    typedef T value_type;
    typedef integral_constant<T,v> type;
    operator T() const { return value; }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template <typename T> struct is_integral                  : public false_type {};
template <>           struct is_integral<bool>               : public true_type {};
template <>           struct is_integral<char>               : public true_type {};
template <>           struct is_integral<signed char>        : public true_type {};
template <>           struct is_integral<unsigned char>      : public true_type {};
template <>           struct is_integral<wchar_t>            : public true_type {};
template <>           struct is_integral<char16_t>           : public true_type {};
template <>           struct is_integral<char32_t>           : public true_type {};
template <>           struct is_integral<short>              : public true_type {};
template <>           struct is_integral<unsigned short>     : public true_type {};
template <>           struct is_integral<int>                : public true_type {};
template <>           struct is_integral<unsigned int>       : public true_type {};
template <>           struct is_integral<long>               : public true_type {};
template <>           struct is_integral<unsigned long>      : public true_type {};
template <>           struct is_integral<long long>          : public true_type {};
template <>           struct is_integral<unsigned long long> : public true_type {};
template <>           struct is_integral<__int128_t>         : public true_type {};
template <>           struct is_integral<__uint128_t>        : public true_type {};

template < typename Iter1, typename Iter2 >
bool    equal(Iter1 first1, Iter1 last1, Iter2 first2){
    for(; first1 != last1; ++first1 , ++first2){
        if (!(*first1 == *first2))
            return false;
    }
    return true;
}

template < typename Iter1, typename Iter2 , typename BP >
bool    equal(Iter1 first1, Iter1 last1, Iter2 first2, BP pred){
    for(; first1 != last1; ++first1 , ++first2){
        if (!pred(*first1, *first2))
            return false;
    }
    return true;
}

template < typename Iter1, typename Iter2 >
bool	lexicographical_compare(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2){
	for(;(first1 != last1) && (first2 != last2); ++first1, ++first2){
		if (*first1 < *first2)
			return true;
		if (*first2 < *first1)
			return false;
	}
	return (first1 == last1) && (first2 != last2);
}

template < typename Iter1, typename Iter2, typename Comp>
bool    lexicographical_compare(Iter1 first1, Iter1 last1,
                                Iter2 first2, Iter2 last2, Comp compare){
	for(;(first1 != last1) && (first2 != last2); ++first1, first2){
		if (compare(*first1 , *first2))
			return true;
		if (compare(*first2 , *first1))
			return true;
	}
	return (first1 == last1) && (first2 != last2);
}

// template < typename T, typename U>
// struct is_same{
// 	static const bool value = false;
// };

// template < typename T>
// struct is_same<T, T>{
// 	static const bool value = true;
// };


}

#endif