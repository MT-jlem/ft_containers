#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iterator>
namespace ft
{

template < typename Tr>
class treeIter
{
	public:
		typedef std::bidirectional_iterator_tag								iterator_category;
		typedef typename Tr::value_type        								value_type;
		typedef typename Tr::difference_type  								difference_type;
		typedef typename Tr::value_type*           							pointer;
		typedef typename Tr::value_type&							        reference;
		typedef typename Tr::node_type*										node_ptr;

		template < typename, typename, typename, typename> friend class map;
		template < typename, typename, typename> friend class set;
	private:
		node_ptr	_curr;
		node_ptr	_root;
		node_ptr	_nil;
		
		node_ptr	min(node_ptr node){
			if (node == _nil)
				return _nil;
			while (node->left != _nil)
				node = node->left;
			return node;
		}

		node_ptr	max(node_ptr node){
			if (node == _nil)
				return _nil;
			while (node->right != _nil)
				node = node->right;
			return node;
		}

		node_ptr	successor(node_ptr node){
			if (node == _nil)
				return node;
			if (node->right != _nil){
				return min(node->right);
			}
			else{

				node_ptr tmp = node;
				while (tmp != _root && tmp != _nil){
					if (tmp->parent->left != _nil && tmp->parent->left == tmp){
						return tmp->parent;
					}
					tmp = tmp->parent;
				}
				return _nil;
			}
		}

		node_ptr predecessor(node_ptr node){
			if (node == _nil)
				return node;
			if (node->left != _nil){
				return max(node->left);
			}
			else{

				node_ptr tmp = node;
				while (node != _root){
					if (tmp->parent->right != _nil && tmp->parent->right == tmp){
						return tmp->parent;
					}
					tmp = tmp->parent;
				}
				return _nil;
			}
		}

	public:
		treeIter(): _curr(NULL), _root(NULL), _nil(NULL){}
		treeIter(node_ptr curr, node_ptr root, node_ptr nil): _curr(curr), _root(root), _nil(nil){}
		treeIter(const treeIter &other): _curr(other._curr), _root(other._root), _nil(other._nil){}

		treeIter	&operator=(const treeIter &iter){
			if (this != &iter){
					_curr = iter._curr;
					_root = iter._root;
					_nil = iter._nil;
			}
			return *this;
		}
		operator treeIter<const Tr>() const{
			return treeIter<const Tr> (_curr, _root, _nil);
		}

		reference operator*() { return (_curr->value); }
		pointer	  operator->() { return &(_curr->value); }
		treeIter	  &operator++(){
			if (_curr != _nil)
				_curr = successor(_curr);
			return *this;
		}
		treeIter	operator++(int){
			treeIter tmp(*this);
			++(*this);
			return tmp;
		}

		treeIter &operator--(){
			if (_curr == _nil){
				_curr = max(_root);
				return *this;
			}
			_curr = predecessor(_curr);
			return *this;
		}

		treeIter operator--(int){
			treeIter tmp(*this);
			--(*this);
			return tmp;
		}

		friend bool operator==(const treeIter &x, const treeIter &y){
			return x._curr == y._curr;
		}
		
		friend bool operator!=(const treeIter &x, const treeIter &y){
			return (x._curr != y._curr);
		}
};

template <
	typename Category,
	typename T,
	typename Distance = ptrdiff_t,
	typename Pointer = T*,
	typename Reference = T&
	>
struct iterator{
	typedef Category	iterator_category;
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer	pointer;
	typedef Reference	reference;
};


// iterator_traits for any iter type
template < typename T >
struct iterator_traits {
	typedef typename T::iterator_category	iterator_category;
	typedef typename T::value_type			value_type;
	typedef typename T::difference_type		difference_type;
	typedef typename T::pointer				pointer;
	typedef typename T::reference			reference;
	
};

//iterator_trait for pointer types;
template < typename T >
struct iterator_traits<T*> {
	typedef std::random_access_iterator_tag	iterator_category;
	typedef T							value_type;
	typedef ptrdiff_t					difference_type;
	typedef T*							pointer;
	typedef T&							reference;
};

//reverse_iter (take iter and make it reverse_iter);
template < typename T>
class reverse_iterator {
	protected:
		T current;
	public:
		typedef	T					iterator_type;
		typedef typename iterator_traits<T>::iterator_category	iterator_category;
		typedef typename iterator_traits<T>::difference_type	value_type;
		typedef typename iterator_traits<T>::difference_type	difference_type;
		typedef typename iterator_traits<T>::pointer	pointer;
		typedef typename iterator_traits<T>::reference	reference;

	//constructor && assignment
	reverse_iterator():current() {}
	reverse_iterator(iterator_type	x): current(x){}
	reverse_iterator(const reverse_iterator<T> &iter): current(iter.base()) {}
	reverse_iterator &operator=(const reverse_iterator<T> &iter){
		if (this != &iter)
			current = iter.base();
		return *this;}
	template<typename It>
	reverse_iterator(const reverse_iterator<It> &iter): current(iter.base()){}
	operator reverse_iterator<const T> (){	return current; }
	//member-func
	iterator_type base() const { return current; }
	//operators
	reference	operator*() const { T tmp = current; return *--tmp; }
	pointer		operator->() const {return &this->operator*();}
	reference	operator[](difference_type n) const { return *(*this + n);}
	reverse_iterator	&operator++(){ --current; return *this; }
	reverse_iterator	operator++(int)
		{ reverse_iterator tmp(*this); --current; return tmp;}
	reverse_iterator	&operator--() 
		{++current; return *this;}
	reverse_iterator	operator--(int) 
		{ reverse_iterator tmp(*this); ++current; return tmp;}
	reverse_iterator	operator+(difference_type n) 
		{return reverse_iterator(current - n);}
	reverse_iterator	operator-(difference_type n)
		{ return reverse_iterator(current + n);}
	reverse_iterator	&operator+=(difference_type n)
		{ current -= n; return *this; }
	reverse_iterator	&operator-=(difference_type n)
		{ current += n; return *this; }
};

template < typename iter1, typename iter2>
bool operator==(const reverse_iterator<iter1> &lhs, const reverse_iterator<iter2> &rhs){
	return lhs.base() == rhs.base();
}

template < typename iter1, typename iter2>
bool operator!=(const reverse_iterator<iter1> &lhs, const reverse_iterator<iter2> &rhs){
	return lhs.base() != rhs.base();
}

template < typename iter1, typename iter2>
bool operator>(const reverse_iterator<iter1> &lhs, const reverse_iterator<iter2> &rhs){
	return lhs.base() > rhs.base();
}

template < typename iter1, typename iter2>
bool operator>=(const reverse_iterator<iter1> &lhs, const reverse_iterator<iter2> &rhs){
	return lhs.base() >= rhs.base();
}

template < typename iter1, typename iter2>
bool operator<(const reverse_iterator<iter1> &lhs, const reverse_iterator<iter2> &rhs){
	return lhs.base() < rhs.base();
}

template < typename iter1, typename iter2>
bool operator<=(const reverse_iterator<iter1> &lhs, const reverse_iterator<iter2> &rhs){
	return lhs.base() <= rhs.base();
}

template < typename iter1, typename iter2 >
typename reverse_iterator<iter1>::difference_type operator-(
		const reverse_iterator<iter1> &lhs, const reverse_iterator<iter2> &rhs){
			return rhs.base() - lhs.base();
		}
template < typename iter>
reverse_iterator<iter>	operator+(
	typename reverse_iterator<iter>::difference_type n, const reverse_iterator<iter> &it)
	{ return reverse_iterator<iter>(it.base() - n);	}
}

#endif
