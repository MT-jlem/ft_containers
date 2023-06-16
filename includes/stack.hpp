#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {
	
template < typename T, typename Container = ft::vector<T> >
class stack {
	public:
	typedef	Container					container_type;
	typedef typename	Container::value_type		value_type;
	typedef	typename	Container::size_type		size_type;
	typedef	typename	Container::reference		reference;
	typedef	typename	Container::const_reference	const_reference;
	protected:
		container_type c;
	public:
		explicit stack(const Container &cont = Container()): c(cont){}
		stack(const stack &other):c(other.c) {}
		~stack() { }
	stack	&operator=(const stack	other){
		if(this != &other){
			c = other.c;
		}
		return *this;
	}
	reference	top(){ return *(c.end() - 1); }
	bool	empty() const { return c.empty(); }
	size_type	size() { return c.size(); }
	void	push(const value_type &value) { c.push_back(value); }
	void	pop() {	c.pop_back(); }

	template< class Ty, class Cont >
	friend bool operator==( const ft::stack<Ty, Cont>& lhs, const ft::stack<Ty, Cont>& rhs ){
		return lhs.c == rhs.c;
	}
	template< class Ty, class Cont >
	friend bool operator!=( const ft::stack<Ty, Cont>& lhs, const ft::stack<Ty, Cont>& rhs ){
		return lhs.c != rhs.c;
	}
	template< class Ty, class Cont >
	friend bool operator< ( const ft::stack<Ty, Cont>& lhs, const ft::stack<Ty, Cont>& rhs ){
		return lhs.c < rhs.c;
	}
	template< class Ty, class Cont >
	friend bool operator<=( const ft::stack<Ty, Cont>& lhs, const ft::stack<Ty, Cont>& rhs ){
		return lhs.c <= rhs.c;
	}
	template< class Ty, class Cont >
	friend bool operator> ( const ft::stack<Ty, Cont>& lhs, const ft::stack<Ty, Cont>& rhs ){
		return lhs.c > rhs.c;
	}
	template< class Ty, class Cont >
	friend bool operator>=(const ft::stack<Ty, Cont>& lhs, const ft::stack<Ty, Cont>& rhs ){
		return lhs.c >= rhs.c;
	}
};


}

#endif