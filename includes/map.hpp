
#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <memory>
#include "pairs.hpp"
#include "util.h"
#include "Tree.hpp"
#include "iterator.hpp"
#include <iterator>



namespace ft{
//map iter line:775

template < typename Arg1, typename Arg2, typename Result >
struct binary_function {
	typedef	Arg1	first_argument_type;
	typedef	Arg2	second_argument_type;
	typedef	Result	result_type;
};


template < typename Key, typename T, typename Comp = std::less<Key>, typename Alloc = std::allocator< pair<const Key, T> > >
class  map
{
	private:
		Tree<Key, T, Comp>	 _tree;
		Alloc	_alloc;
		Comp	_comp;
	public:
		typedef	Key											key_type;
		typedef	T											mapped_type;
		typedef	pair<Key, T>								value_type;
		typedef	Comp										key_compare;
		typedef Alloc										allocator_type;
		typedef	typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;

		typedef typename ft::treeIter<Tree<Key, T, Comp> >		 iterator;
		typedef typename ft::treeIter<const Tree<Key, T, Comp> > const_iterator;
		typedef typename ft::reverse_iterator<iterator>			 reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	 const_reverse_iterator;
	
		template<typename> friend class treeIter;
		class value_compare : public binary_function< value_type, value_type, bool >
		{
			friend class map;
			protected:
			key_compare	comp;
			value_compare(Comp c) : comp(c) {}

			public:
			bool	operator()(const value_type &x, const value_type &y) const{
				return comp(x.first, y.first);
			}
		};


	public:
		map(){
			_alloc = Alloc();
			_comp = Comp();
		}
		explicit map(const Comp &comp, const Alloc &alloc = Alloc()){
			_alloc = alloc;
			_comp = comp;
		}
		template<typename Iter>
			map(Iter first, Iter last, const Comp &comp = Comp(), const Alloc &alloc = Alloc()){
				_alloc = alloc;
				_comp = comp;
				for (; first != last ; ++first){
					_tree.insertNode(*first);
				}
			}
		
		map(const map &other){
			*this = other;
		}

		~map(){ /* tree destructor should be called automatically*/ }

		map	&operator=(const map& other){
			if (this != &other){
				_alloc = other._alloc;
				_comp = other._comp;
				_tree = other._tree;
			}
			return *this;
		}

		allocator_type	get_allocator() const { return _alloc; }

		T		&at(const Key &key){
			t_node<Key, T> *tmp = _tree.findNode(key);
			
			if (tmp == _tree.getNil())
				throw std::out_of_range("map::at:  key not found");
			return tmp->value.second;
		}
		
		const T &at(const Key &key) const{
			t_node<Key, T> *tmp = _tree.findNode(key);
			
			if (tmp == _tree.getNil())
				throw std::out_of_range("map::at:  key not found");
			return tmp->value.second;
		}

		T		&operator[](const Key &key){
			t_node<Key, T> *tmp = _tree.findNode(key);
			if (tmp == _tree.getNil()){
				return (_tree.insertNode(ft::pair<Key, T>(key, T()))->value.second);
			}
			return tmp->value.second;
		}

		iterator				begin(){
			iterator it(_tree.min(_tree.getRoot()), _tree.getRoot(), _tree.getNil());
			return it;
		}
		const_iterator			begin() const{
			const_iterator it(_tree.min(_tree.getRoot()), _tree.getRoot(), _tree.getNil());
			return it;
		}
		iterator 				end(){
			iterator it(_tree.getNil(), _tree.getRoot(), _tree.getNil());
			return it;
		}
		const_iterator			end() const{
			const_iterator it(_tree.getNil(), _tree.getRoot(), _tree.getNil());
			return it;
		}
		reverse_iterator		rbegin(){
			return reverse_iterator(end());
		}
		const_reverse_iterator	rbegin() const{
			return const_reverse_iterator(end());
		}
		reverse_iterator		rend(){
			return reverse_iterator(++begin());
		}
		const_reverse_iterator	rend()	const{
			return const_reverse_iterator(++begin());
		}

		bool		empty() const {
			return _tree.empty();
		}

		size_type	size() const{
			return _tree.get_size();
		}
		size_type	max_size() const{
			return	_tree.max_size();
		}

		void	clear(){
			_tree.clear(_tree.getRoot());
		}
		pair<iterator, bool>	insert(const value_type &value){
			bool		found = (_tree.findNode(value.first) != _tree.getNil()) ? true : false;
			iterator	it(_tree.insertNode(value), _tree.getRoot(), _tree.getNil());
			return pair<iterator, bool> (it, !found);
		}

		iterator 				insert(iterator pos, const value_type &value){
			(void)pos;
			iterator	it(_tree.insertNode(value), _tree.getRoot(), _tree.getNil());
			return it;
		}

		template < typename Iter >
		void					insert(Iter first, Iter last){
			for (; first != last; ++first){
				_tree.insertNode(*first);
			}
		}

		iterator 				erase(iterator pos){
			t_node<Key, T> *tmp = pos._curr;

			++pos;
			_tree.deleteNode(tmp);
			return pos;
		}

		iterator 				erase(iterator first, iterator last){
			while (first != last){
				first = erase(first);
			}
			return first;
		}

		size_type				erase(const Key& key){
			t_node<Key, T> *tmp = _tree.findNode(key);
			
			if (tmp != _tree.getNil())
				return _tree.deleteNode(tmp) , 1;
			return 0;
		}

		void	swap(map &other){
			_tree.swap(other._tree);

			Alloc swapAlloc = _alloc;
			Comp swapComp = _comp;

			_alloc = other._alloc;
			_comp = other._comp;
			other._alloc = swapAlloc;
			other._comp = swapComp;
		}

		size_type				count(const Key& key) const{
			t_node<Key, T> *tmp = _tree.findNode(key);
			
			if (tmp == _tree.getNil())
				return 0;
			return 1;
		}

		iterator 				find(const Key &key){
			iterator it (_tree.findNode(key), _tree.getRoot(), _tree.getNil());
			return it;
		}

		const_iterator 			find(const Key &key) const{
			const_iterator it(_tree.findNode(key), _tree.getRoot(), _tree.getNil());
			return it;
		}

		pair<iterator, iterator> 	equal_range(const Key &key){
			pair<iterator, iterator> tmp(lower_bound(key), upper_bound(key));
			return tmp;
		}

		pair<const_iterator, const_iterator> equal_range(const Key &key) const{
			pair<const_iterator, const_iterator> tmp(lower_bound(key), upper_bound(key));
			return tmp;
		}

		iterator 				lower_bound(const Key &key){
			iterator it = begin();
			iterator last = end();

			for (;it != last; ++it){
				if (it->first >= key)
					return it;
			}
			return last;
		}

		const_iterator 			lower_bound(const Key &key) const{
			const_iterator it = begin();
			const_iterator last = end();

			for (;it != last; ++it){
				if (it->first >= key)
					return it;
			}
			return last;
		}

		iterator 				upper_bound(const Key &key){
			iterator it = begin();
			iterator last = end();

			for (;it != last; ++it){
				if (it->first > key)
					return it;
			}
			return last;
		}

		const_iterator			upper_bound(const Key &key) const{
			const_iterator it = begin();
			const_iterator last = end();

			for (;it != last; ++it){
				if (it->first > key)
					return it;
			}
			return last;
		}

		key_compare			key_comp() const { return _comp; }
		map::value_compare	value_comp() const { return value_compare(_comp); }
};

template <typename Key, typename T, typename Comp, typename Alloc>
bool operator==(const map<Key, T, Comp, Alloc>& x, const map<Key, T, Comp, Alloc>& y){
	if (x.size() != y.size())
		return false;
	return equal(x.begin(), x.end(), y.begin());
}

template <typename Key, typename T, typename Comp, typename Alloc>
bool operator< (const map<Key, T, Comp, Alloc>& x, const map<Key, T, Comp, Alloc>& y){
	return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <typename Key, typename T, typename Comp, typename Alloc>
bool operator!=(const map<Key, T, Comp, Alloc>& x, const map<Key, T, Comp, Alloc>& y){
	return !(x == y);
}

template <typename Key, typename T, typename Comp, typename Alloc>
bool operator> (const map<Key, T, Comp, Alloc>& x, const map<Key, T, Comp, Alloc>& y){
	return y < x;
}

template <typename Key, typename T, typename Comp, typename Alloc>
bool operator>=(const map<Key, T, Comp, Alloc>& x, const map<Key, T, Comp, Alloc>& y){
	return !(x < y);
}

template <typename Key, typename T, typename Comp, typename Alloc>
bool operator<=(const map<Key, T, Comp, Alloc>& x, const map<Key, T, Comp, Alloc>& y){
	return !(x > y);
}

template <typename Key, typename T, typename Comp, typename Alloc>
void	swap(map<Key, T, Comp, Alloc>& x, map<Key, T, Comp, Alloc>& y){
	x.swap(y);
}

}
#endif
