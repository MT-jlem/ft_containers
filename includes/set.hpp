#ifndef SET_HPP
#define SET_HPP

#include "SetTree.hpp"
#include "iterator.hpp"
#include "pairs.hpp"
#include <memory>

namespace ft{

template <typename Key, typename Compare = std::less<Key>, typename Allocator = std::allocator<Key> >
class set
{
	public:
		typedef Key                                      key_type;
		typedef key_type                                 value_type;
		typedef Compare                                  key_compare;
		typedef key_compare                              value_compare;
		typedef Allocator                                allocator_type;
		typedef Key&					        		 reference;
		typedef const Key&								 const_reference;
		typedef typename allocator_type::size_type       size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;

		typedef treeIter< SetTree<Key, Compare> >		iterator;
		typedef	treeIter< SetTree<Key, Compare> >		const_iterator;
		typedef std::reverse_iterator<iterator>			reverse_iterator;
		typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

		template<typename> friend class treeIter;
	
		set(): _tree(SetTree<Key, Compare>()), _alloc(Allocator()), _comp(Compare()){}
		explicit set(const Compare &comp, const Allocator &alloc = Allocator()){
			_comp = comp;
			_alloc = alloc;
		}
		template < typename InputIt>
		set(InputIt first, InputIt last, const Compare &comp = Compare(), const Allocator &alloc = Allocator()){
			_alloc = alloc;
			_comp = comp;
			for (; first != last; ++first)
				_tree.insertNode(*first);
		}
		set( const set &other){
			*this = other;
		}
		~set(){/* tree destructor should be called automatically */}

		set	&operator=(const set &other){
			if (this != &other){
				_alloc = other._alloc;
				_comp = other._comp;
				_tree = other._tree;
			}
			return *this;
		}
		allocator_type	get_allocator() const { return _alloc; }

		iterator begin(){
			iterator it(_tree.min(_tree.getRoot()), _tree.getRoot(), _tree.getNil());
			return it;
		}
		const_iterator begin() const{
			const_iterator it(_tree.min(_tree.getRoot()), _tree.getRoot(), _tree.getNil());
			return it;
		}
		iterator end(){
		iterator it(_tree.getNil(), _tree.getRoot(), _tree.getNil());
			return it;
		}
		const_iterator end() const{
			const_iterator it(_tree.getNil(), _tree.getRoot(), _tree.getNil());
			return it;
		}
		reverse_iterator rbegin(){
			return reverse_iterator(end());
		}
		const_reverse_iterator rbegin() const{
			return const_reverse_iterator(end());
		}
		reverse_iterator rend(){
			return reverse_iterator(++begin());
		}
		const_reverse_iterator rend() const{
			return const_reverse_iterator(++begin());
		}

		bool	empty() const{
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
		pair<iterator, bool> insert(const value_type &value){
			bool		found = (_tree.findNode(value) != _tree.getNil()) ? true : false;
			iterator	it(_tree.insertNode(value), _tree.getRoot(), _tree.getNil());
			return pair<iterator, bool> (it, !found);
		}
		iterator	insert(iterator pos, const value_type &value){
			(void)pos;
			iterator	it(_tree.insertNode(value), _tree.getRoot(), _tree.getNil());
			return it;
		}
		template < typename InputIt >
		void	insert(InputIt first, InputIt last){
			for (; first != last; ++first){
				_tree.insertNode(*first);
			}
		}

		iterator	erase(iterator pos){
			s_node<Key> *tmp = pos._curr;

			++pos;
			_tree.deleteNode(tmp);
			return pos;
		}
		iterator	erase(iterator first, iterator last){
			while (first != last){
				first = erase(first);
			}
			return first;
		}
		size_type	erase(const Key &key){
			s_node<Key> *tmp = _tree.findNode(key);
			
			if (tmp != _tree.getNil())
				return _tree.deleteNode(tmp) , 1;
			return 0;
		}
		void	swap(set &other){
			_tree.swap(other._tree);

			Allocator swapAlloc = _alloc;
			Compare swapComp = _comp;

			_alloc = other._alloc;
			_comp = other._comp;
			other._alloc = swapAlloc;
			other._comp = swapComp;
		}

		size_type count(const Key &key){
			s_node<Key> *tmp = _tree.findNode(key);
			
			if (tmp == _tree.getNil())
				return 0;
			return 1;
		}
		iterator find(const Key &key){
			iterator it (_tree.findNode(key), _tree.getRoot(), _tree.getNil());
			return it;
		}
		const_iterator find(const Key &key) const {
			const_iterator it(_tree.findNode(key), _tree.getRoot(), _tree.getNil());
			return it;
		}

		pair<iterator, iterator> equal_range(const Key &key){
			pair<iterator, iterator> tmp(lower_bound(key), upper_bound(key));
			return tmp;
		}
		pair<const_iterator, const_iterator> equal_range(const Key &key) const{
			pair<const_iterator, const_iterator> tmp(lower_bound(key), upper_bound(key));
			return tmp;
		}

		iterator lower_bound(const Key &key){
			iterator it = begin();
			iterator last = end();

			for (;it != last; ++it){
				if (*it >= key)
					return it;
			}
			return last;
		}
		const_iterator lower_bound(const Key &key) const {
			const_iterator it = begin();
			const_iterator last = end();

			for (;it != last; ++it){
				if (*it >= key)
					return it;
			}
			return last;}

		iterator upper_bound(const Key &key){
			iterator it = begin();
			iterator last = end();

			for (;it != last; ++it){
				if (*it > key)
					return it;
			}
			return last;
		}
		const_iterator upper_bound(const Key &key) const {
			const_iterator it = begin();
			const_iterator last = end();

			for (;it != last; ++it){
				if (*it > key)
					return it;
			}
			return last;
		}

		key_compare key_comp() const { return _comp; }
		set::value_compare value_comp() const { return value_compare(); }

	private:
		SetTree<Key, Compare>	_tree;
		Allocator				_alloc;
		Compare					_comp;
};

template <typename Key, typename Comp, typename Alloc>
bool operator==(const set<Key, Comp, Alloc>& x, const set<Key, Comp, Alloc>& y){
	if (x.size() != y.size())
		return false;
	return equal(x.begin(), x.end(), y.begin());
}

template <typename Key, typename Comp, typename Alloc>
bool operator< (const set<Key, Comp, Alloc>& x, const set<Key, Comp, Alloc>& y){
	return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <typename Key, typename Comp, typename Alloc>
bool operator!=(const set<Key, Comp, Alloc>& x, const set<Key, Comp, Alloc>& y){
	return !(x == y);
}

template <typename Key, typename Comp, typename Alloc>
bool operator> (const set<Key, Comp, Alloc>& x, const set<Key, Comp, Alloc>& y){
	return y < x;
}

template <typename Key, typename Comp, typename Alloc>
bool operator>=(const set<Key, Comp, Alloc>& x, const set<Key, Comp, Alloc>& y){
	return !(x < y);
}

template <typename Key, typename Comp, typename Alloc>
bool operator<=(const set<Key, Comp, Alloc>& x, const set<Key, Comp, Alloc>& y){
	return !(x > y);
}

template <typename Key, typename Comp, typename Alloc>
void	swap(set<Key, Comp, Alloc>& x, set<Key, Comp, Alloc>& y){
	x.swap(y);
}

}
#endif