#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <exception>
#include <iterator>
#include <memory>
#include "iterator.hpp"
#include "utils.hpp"

namespace ft{

template <typename Iter>
class vecIter : public std::iterator<std::random_access_iterator_tag, Iter>{
	public:
		typedef Iter                                                      iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type        value_type;
		typedef ptrdiff_t   difference_type;
		typedef typename iterator_traits<iterator_type>::pointer           pointer;
		typedef typename iterator_traits<iterator_type>::reference         reference;
	private:
		pointer __i;
	public:
		vecIter(): __i(nullptr){}
		// vecIter(iterator_type it): __i(it) {}
		vecIter(const iterator_type it): __i(it){}
		template<typename It>
		vecIter(const vecIter<It> &iter): __i(iter.base()){}
		template<typename T>
		vecIter(typename enable_if< !is_integral < T >::value, T >::type &iter): __i(iter.base()) {}
		// iterator_type	base() const { return __i; }
		const iterator_type	base() const { return __i; }
		 
		//operator= 
		reference	operator*() { return *__i; }
		pointer		operator->() { return __i; }
		vecIter		&operator++() { ++__i; return *this; }
		vecIter		&operator--() { --__i; return *this; }
		vecIter		operator++(int) { vecIter tmp(*this); ++(*this); return tmp; }
		vecIter		operator--(int) { vecIter tmp(*this); --(*this); return tmp; }
		vecIter		operator+(difference_type n) { vecIter tmp(*this); tmp += n; return tmp; }
		vecIter		&operator+=(difference_type n) { __i += n; return *this;}
		vecIter		operator-(difference_type n) { vecIter tmp(*this); tmp -= n; return tmp; }
		vecIter		&operator-=(difference_type n) { __i -= n; return *this; }
		reference	operator[](difference_type n) { return __i[n]; /* return *(__i + n) */}
		//friend operators
		template < typename Iter1, typename Iter2 >
		friend bool operator==(const vecIter<Iter1> &lhs, const vecIter<Iter2> &rhs);
		template < typename Iter1, typename Iter2 >
		friend bool operator<(const vecIter<Iter1> &lhs, const vecIter<Iter2> &rhs);
		template < typename Iter1, typename Iter2 >
		friend bool operator!=(const vecIter<Iter1> &lhs, const vecIter<Iter2> &rhs);
		template < typename Iter1, typename Iter2 >
		friend bool operator>(const vecIter<Iter1> &lhs, const vecIter<Iter2> &rhs);
		template < typename Iter1, typename Iter2 >
		friend bool operator>=(const vecIter<Iter1> &lhs, const vecIter<Iter2> &rhs);
		template < typename Iter1, typename Iter2 >
		friend bool operator<=(const vecIter<Iter1> &lhs, const vecIter<Iter2> &rhs);
		template < typename Iter1>
		friend typename iterator_traits<Iter1>::difference_type operator-(const vecIter<Iter1> &lhs, const vecIter<Iter1> &rhs);
		template < typename Iter1 >
		friend	vecIter<Iter1> operator+(difference_type n, const vecIter<Iter1> &lhs){ vecIter<Iter1> tmp(lhs.base()); tmp += n; return tmp;}
};


template <typename Iter1, typename Iter2>
bool operator==(const vecIter<Iter1> &lhs, const vecIter<Iter2> &rhs){
		return lhs.base() == rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator<(const vecIter<Iter1> &lhs, const vecIter<Iter2> &rhs){
		return lhs.base() < rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator!=(const vecIter<Iter1> &lhs, const vecIter<Iter2> &rhs){
		return !(lhs == rhs);
}

template <typename Iter1, typename Iter2>
bool operator>(const vecIter<Iter1> &lhs, const vecIter<Iter2> &rhs){
		return rhs < lhs;
}

template <typename Iter1, typename Iter2>
bool operator>=(const vecIter<Iter1> &lhs, const vecIter<Iter2> &rhs){
		return !(lhs < rhs);
}

template <typename Iter1, typename Iter2>
bool operator<=(const vecIter<Iter1> &lhs, const vecIter<Iter2> &rhs){
		return !(lhs > rhs);
}

template < typename Iter1>
typename iterator_traits<Iter1>::difference_type operator-(const vecIter<Iter1> &lhs, const vecIter<Iter1> &rhs){
	return lhs.base() - rhs.base();
}


template<typename T, typename Alloc = std::allocator<T> >
class vector
{
	public:
		typedef	T										value_type;
		typedef	Alloc									allocator_type;
		typedef	typename	Alloc::reference			reference;
		typedef typename	Alloc::const_reference		const_reference;
		typedef typename	Alloc::size_type			size_type;
		typedef	typename	Alloc::difference_type		difference_type;
		typedef typename	Alloc::pointer				pointer;
		typedef	typename	Alloc::const_pointer		const_pointer;
		typedef	typename	ft::vecIter<T*>					iterator;
		typedef typename	ft::vecIter<const T*>				const_iterator;
		typedef typename	ft::reverse_iterator<iterator>	reverse_iterator;
		typedef typename	ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		//constructors 
		vector():ptr(nullptr), __size(0), cap(0), alloc(Alloc()){}
		vector( const Alloc &a): ptr(nullptr), __size(0), cap(0), alloc(a){};
		vector(size_type count, const T &value = T(), const Alloc &a = Alloc()): alloc(a){
			cap = size_to_alloc(count);
			ptr = alloc.allocate(cap);
			__size = 0;
			for(; __size < count; ++__size)
				alloc.construct(ptr + __size, value);
		}
		template < typename Input >
		vector(Input first, typename enable_if< !is_integral < Input >::value, Input >::type last, const Alloc &a = Alloc()): alloc(a)
		{
			cap = size_to_alloc(std::distance(first, last));
			ptr = alloc.allocate(cap);
			__size = 0;
			for (;first != last; ++first, ++__size)
				alloc.construct(ptr + __size, *first);
		}
		vector( const vector &obj): cap(obj.cap), alloc(obj.alloc)
		{
			ptr = alloc.allocate(cap);
			__size = 0;
			for(; __size < obj.__size; ++__size)
				alloc.construct(ptr + __size, obj[__size]);
		}
		~vector(){
			if(ptr != nullptr)
			{
				clear();
				alloc.deallocate(ptr, cap);
			}
		}
		vector &operator=( const vector &other){
			if(this != &other){
					my_clear();
					if(ptr != nullptr)//destroy
						alloc.deallocate(ptr, cap);
					cap = size_to_alloc(other.__size);
					ptr = alloc.allocate(cap);
					__size = 0;
					for(;__size < other.__size; ++__size)
						alloc.construct(ptr + __size, other[__size]);
			}
			return *this;
		}
		void	assign(size_type n, const value_type &x){
			my_clear();
			if(n >= cap && n)
			{
				if (ptr != nullptr)
					alloc.deallocate(ptr, cap);
				cap = size_to_alloc(n);
				ptr = alloc.allocate(cap);
			}
			__size = 0;
			for(; __size < n; ++__size)
				alloc.construct(ptr + __size, x);
		}
		template < typename Iter>
		void	assign(Iter first, Iter last, typename enable_if<!is_integral<Iter>::value, Iter>::type = NULL){
				my_clear();
			if ((size_type)std::distance(first, last) > cap){
				if (ptr != nullptr)
					alloc.deallocate(ptr, cap);
				cap = size_to_alloc(std::distance(first, last));
				ptr = alloc.allocate(cap);
			}
			__size = 0;
			for (; first != last; first++ , ++__size){
				alloc.construct(ptr + __size, *first);
			}
		}

		allocator_type	get_allocator() const { return alloc; }

		reference			at(size_type pos) {
			if (pos >= __size)
				throw std::out_of_range("out of range");
			return ptr[pos];
		}
		const_reference		at(size_type pos) const {
			if (pos >= __size)
				throw std::out_of_range("out of range");
			return ptr[pos];
		}
		reference			operator[](size_type n) { return ptr[n]; }
		const_reference		operator[](size_type n) const { return ptr[n]; }
		reference			front() { return *ptr; }
		const_reference		front() const { return *ptr; }
		reference			back() { return *(ptr + (__size - 1)); }
		const_reference		back() const { return *(ptr + (__size - 1)); }
		value_type*			data() { return ptr; }
		const value_type*	data() const { return ptr; }

		iterator		begin() { return iterator(ptr);}
		const_iterator	cbegin() const { return const_iterator(ptr); }
		const_iterator	begin() const { return const_iterator(ptr); }
		iterator		end() { return iterator(ptr + __size); }
		const_iterator	cend() const { return const_iterator(ptr + __size); }
		const_iterator	end() const { return const_iterator(ptr + __size); }

		reverse_iterator		rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator	crbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator		rend() { return reverse_iterator(begin()); }
		const_reverse_iterator	crend() const { return const_reverse_iterator(begin()); }

		size_type	size() const { return __size; }
		size_type	max_size() const { return alloc.max_size(); }
		size_type	capacity() const {return cap; }
		bool		empty() const { return (__size == 0); }
		void		reserve(size_type n){
			pointer tmp;
			size_type prvCap = cap;

			if (n > max_size())
				throw std::length_error("length error");
			if (n > cap){
				cap = size_to_alloc(n);
				try{
					tmp = alloc.allocate(cap);
					for (size_type i = 0 ; i < __size; ++i)
						alloc.construct(tmp + i, ptr[i]);
					my_clear();
					if (ptr != nullptr)
						alloc.deallocate(ptr, prvCap);
					ptr = tmp;
				}catch(std::exception &e){
					;//print error msg;
				}
			}
		}

		void	push_back(const value_type &x){
			try{
				if (__size + 1 > cap)
				{
					pointer tmp;
					size_type prvCap = cap;
					cap = size_to_alloc(__size + 1);// cap > max_size exception
					tmp = alloc.allocate(cap);
					for (size_type i = 0 ; i < __size; ++i)
						alloc.construct(tmp + i, ptr[i]);
					my_clear();
					if (ptr != nullptr)
						alloc.deallocate(ptr, prvCap);
					ptr = tmp;
				}
				alloc.construct(ptr + __size++, x);
				// ptr[__size++] = x;
			}catch(std::exception &){}
		}
		void	pop_back(){
			--__size;
			alloc.destroy(ptr + __size);
		}
		
		iterator	insert(const_iterator pos, const value_type &x){
			try{
				if (__size + 1 > cap)
				{
					pointer tmp;
					pointer ret;
					size_type prvCap = cap;
					iterator iter = begin();
					cap = size_to_alloc(__size + 1);
					tmp = alloc.allocate(cap);
					bool flag = 1;
					for (size_type i = 0 ; i < __size + 1; ++i){
						if(iter == pos && flag){
							alloc.construct(tmp + i, x);
							ret = tmp + i;
							flag = 0;
						}
						else{
							alloc.construct(tmp + i, *iter);
							iter++;
						}
					}
					my_clear();
					if (ptr != nullptr){
						alloc.deallocate(ptr, prvCap);
					}
					++__size;
					ptr = tmp;
					return ret;
				}
				}catch(std::exception &e){}
				difference_type dist = std::distance(cbegin(), pos);
				iterator iter = end();
				if (pos != end())
				{
					--iter;
					for(; iter != pos; --iter)
						*(iter + 1) = *iter;
					*(iter + 1) = *iter;}
				
				*iter = x;
				++__size;
				return ptr + dist;
		}
		iterator	insert(const_iterator pos, const size_type count, const value_type &x){
			if (__size + count > cap){
				pointer tmp;
				pointer ret;
				size_type prvCap = cap;
				iterator iter = begin();
				cap = size_to_alloc(__size + count);
				tmp = alloc.allocate(cap);
				bool flag = 1;
				for(size_type i = 0; i < __size + count; ++i){
					if (iter == pos && flag){
						ret = tmp + i;
						for (size_type j = 0; j < count; ++j, ++i)
							alloc.construct(tmp + i, x);
						--i;
						flag = 0;
					}
					else{
						alloc.construct(tmp + i, *iter);
						++iter;
					}
				}
				my_clear();
				if (ptr != nullptr){
					alloc.deallocate(ptr, prvCap);
				}
				ptr = tmp;
				__size += count;
				return iterator(ret);
			}
			iterator iter = end() - 1;
			if (pos != end()){
				for(; iter != pos; --iter)
					*(iter + count) = *iter;
				*(iter + count) = *iter;
				--iter;
			}
			for(size_type i = 0; i < count; ++i, --iter)
				*(iter + count) = x;
			__size += count;
			return iter;
		}
		template < typename Iter >
		iterator	insert(const_iterator pos, Iter first, Iter last,
					typename enable_if< !is_integral < Iter >::value, Iter >::type = typename enable_if< !is_integral < Iter >::value, Iter >::type()){
			if (std::distance(first, last) + __size > cap){
				pointer tmp;
				pointer ret;
				size_type prvCap = cap;
				iterator iter = begin();
				cap = size_to_alloc(__size + std::distance(first, last));
				tmp = alloc.allocate(cap);
				bool flag = 1;
				size_type dist = std::distance(first, last);
				for (size_type i = 0; i < __size + dist; ++i){
					if (iter == pos && flag){
						ret = tmp + i;
						for (; first != last; ++first, ++i)
							alloc.construct(tmp + i, *first);
						--i;
						flag = 0;
					}
					else{
						alloc.construct(tmp + i, *iter);
						++iter;
					}
				}
				my_clear();
				if (ptr != nullptr){
					alloc.deallocate(ptr, prvCap);
				}
				__size += dist;
				ptr = tmp;
				return iterator(ret);
			}
			iterator iter = end() - 1;
			size_type dist = std::distance(first, last);
			if (pos != end()){
				for(; iter != pos; --iter)
					*(iter + dist) = *iter;
				*(iter + dist) = *iter;
				--iter;
			--last;}
			for(size_type i = 0; i < dist; ++i, --iter, --last)
				*(iter + dist) = *last;
			__size += dist;
			return iter;
		}

		iterator	erase(iterator pos)
		{
			iterator iter = pos;// to remove the const
			++iter;
			for (; iter != end(); ++iter){
				*(iter - 1) = *iter;
			}
			pop_back();
			return pos;
		}
		iterator	erase(iterator first, iterator last){
			if (first == last)
				return last;
			iterator iter = last;
			for(; iter != end(); ++iter , ++first)
				*first = *iter;
			pointer tmp = first.base();
			for (;tmp != iter.base(); ++tmp, --__size){
				alloc.destroy(tmp);
			}
			return last.base();	
		}

		void		resize(size_type count, const value_type &x = T()){
			if (count < __size){
				for (; __size > count; --__size)
					alloc.destroy(ptr + (__size - 1));
			}
			else{
				if (count <= cap){
					for (; __size < count; ++__size)
						alloc.construct(ptr + __size, x);
				}
				else{
					for(size_type i = __size ; i < count; ++i)
						push_back(x);
				} 
			}
		}
		void		clear(){
			for (size_type i = 0; i < __size ; ++i)
				alloc.destroy(ptr + i);
			__size = 0;
		}
		void	swap(vector &other){
			pointer tmp;
			size_type count;

			count = __size;
			__size = other.__size;
			other.__size = count;
			count = cap;
			cap = other.cap;
			other.cap = count;
			tmp = ptr;
			ptr = other.ptr;
			other.ptr = tmp;
		}

	private:
		pointer			ptr;
		size_type		__size;
		size_type		cap;
		Alloc			alloc;
		//helper func
		size_type	size_to_alloc(size_type count){
			if (count > alloc.max_size())
				throw std::length_error("length error\n");
			if ((count * 2) > alloc.max_size())
				return max_size();
			return (count * 2);
		}
		void		my_clear(){
			for (size_type i = 0; i < __size; ++i)
				alloc.destroy(ptr + i);
		}
};

template <typename T, typename Alloc>
bool operator==(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs){
	if (lhs.size() != rhs.size())
		return false;
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T, typename Alloc>
bool operator<(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs){
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, typename Alloc>
bool operator!=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs){
		return !(lhs == rhs);
}

template <typename T, typename Alloc>
bool operator>(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs){
		return rhs < lhs;
}

template <typename T, typename Alloc>
bool operator>=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs){
		return !(lhs < rhs);
}

template <typename T, typename Alloc>
bool operator<=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs){
		return !(lhs > rhs);
}

//+++++++++++++++++++++++++++++ swap<vector> here +++++++++++++++++++++++++++++
template< class T, class Alloc >
void swap( ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs ){
	lhs.swap(rhs);
}
}
#endif
