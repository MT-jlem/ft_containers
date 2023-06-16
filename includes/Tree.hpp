#ifndef TREE_HPP
#define TREE_HPP

#include <functional>
#include <iostream>
#include <memory>
#include "pairs.hpp"
#include "util.h"

namespace ft {
#define RED true
#define BLACK false

template < typename Key, typename T>
struct  t_node
{
	t_node<Key, T>	*parent;
	t_node<Key, T>	*left;
	t_node<Key, T>	*right;
	pair<Key, T>	value;
	bool			color;

	t_node(): parent(nullptr), left(nullptr), right(nullptr), color(BLACK) {}
	t_node(const pair<Key, T> &data, t_node<Key, T> *nil): parent(nil), left(nil), right(nil), value(data), color(RED) {} 
};

template <typename Key, typename T,typename Comp, typename Alloc = std::allocator<t_node<Key, T> > >
class Tree{
	public:
		typedef	t_node<Key, T>						node_type;
		typedef	pair<Key, T>						value_type;
		typedef typename	Alloc::difference_type	difference_type;
		typedef node_type*							pointer;
	private:
		t_node<Key, T>	*root;
		t_node<Key, T>	*nil;
		Alloc			_alloc;
		size_t			_size;
		Comp			_comp;
	//helper functions
		bool siblingIsRed(t_node<Key, T> *n){
			if (n->parent == nil)
				return BLACK;
			if (n->parent->left == nil || n->parent->right == nil)
				return BLACK;
			if (n->parent->left != n)
				return n->parent->left->color;
			else
				return n->parent->right->color;
		}

		t_node<Key, T> *sibling(t_node<Key, T> *n){
			if (n->parent->left != n)
				return n->parent->left;
			return n->parent->right;
		}

		void rightRotate(t_node<Key, T> * x) {
			t_node<Key, T> * y = x->left;
			
			x->left = y->right;
			if (y->right != nil) {
				y->right->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == nil || x->parent == nullptr){
				this->root = y;
			} else if (x == x->parent->right) {
				x->parent->right = y;
			} else {
				x->parent->left = y;
			}
			y->right = x;
			x->parent = y;
		}

		void leftRotate(t_node<Key, T> * x) {
			t_node<Key, T> * y = x->right;

			x->right = y->left;
			if (y->left != nil) {
				y->left->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == nil || x->parent == nullptr){
				this->root = y;
			} else if (x == x->parent->left) {
				x->parent->left = y;
			} else {
				x->parent->right = y;
			}
			y->left = x;
			x->parent = y;
		}

		void	rebalance(t_node<Key, T> *n){
			t_node<Key, T> *k;;

			
			while (n != root && n->parent->color == RED)
			{
				if (siblingIsRed(n->parent)){
					k = sibling(n->parent);
					k->color = BLACK;
					n->parent->color = BLACK;
					n->parent->parent->color = RED;
					n = n->parent->parent;
				}
				else{
					if (n->parent->parent->left == n->parent){
						if (n->parent->right == n){
							n = n->parent;
							leftRotate(n);
						}
						n->parent->color = BLACK;
						n->parent->parent->color = RED;
						rightRotate(n->parent->parent);
					}
					else if (n->parent->parent->right == n->parent){
						if (n->parent->left == n){
							n = n->parent;
							rightRotate(n);
						}
						n->parent->color = BLACK;
						n->parent->parent->color = RED;
						leftRotate(n->parent->parent);
					}
				}
			}
			root->color = BLACK;
		}

		void	transplant(t_node<Key, T> *x, t_node<Key, T> *y){
			if (x->parent == nil)
				root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			y->parent = x->parent;
		}

		void	deleteFixUp(t_node<Key, T> *x){
			t_node<Key, T> *w;

			while (x != root && x->color == BLACK){
				if (x == x->parent->left){
					w = x->parent->right;
					if (w->color == RED){
						w->color = BLACK;
						x->parent->color = RED;
						leftRotate(x->parent);
						w = x->parent->right;
					}
					if (w->left->color == BLACK && w->right->color == BLACK){
						w->color  = RED;
						x = x->parent;
					}
					else{
						if (w->right->color == BLACK){
							w->left->color = BLACK;
							w->color = RED;
							rightRotate(w);
							w = x->parent->right;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->right->color = BLACK;
						leftRotate(x->parent);
						x = root;
					}
				}
				else{
					w = x->parent->left;
					if (w->color == RED){
						w->color = BLACK;
						x->parent->color = RED;
						rightRotate(x->parent);
						w = x->parent->left;
					}
					if (w->right->color == BLACK && w->left->color == BLACK){
						w->color = RED;
						x = x->parent;
					}
					else{
						if (w->left->color == BLACK){
							w->right->color = BLACK;
							w->color = RED;
							leftRotate(w);
							w = x->parent->left;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->left->color = BLACK;
						rightRotate(x->parent);
						x = root;
					}
				}
			}
			x->color = BLACK;
		}

	public:
		explicit Tree(): _alloc(Alloc()){
			nil = _alloc.allocate(1);
			nil->left = nil;
			nil->right = nil;
			nil->parent = nil;
			// _alloc.construct(nil);
			root = nil;
			_size = 0;
		}

		~Tree(){
			clear(root);
			// _alloc.destroy(nil);
			_alloc.deallocate(nil, 1);
		}

		Tree<Key, T, Comp> &operator=(const Tree<Key, T, Comp> &other){
			if (this != &other){
				clear(root);
				// _alloc.deallocate(nil, 1);
				// nil = _alloc.allocate(1);
				// nil = other.nil;
				root = clone(other.root, other);
				_alloc = other._alloc;
				_size = other._size;
			}
			return *this;
		}

		t_node<Key, T>	*insertNode(const pair<Key, T> &val){
			t_node<Key, T> *tmp = root;
			t_node<Key, T>	*n = _alloc.allocate(1);

			_alloc.construct(n, val, nil);
			if (root == nil){
				root = n;
				root->color = BLACK;
				++_size;
				return root;
			}
			while (tmp != nil)
			{
				if (_comp(val.first, tmp->value.first)){
					if (tmp->left == nil){
						tmp->left = n;
						n->parent = tmp;
						break;
					}
					else{
						tmp = tmp->left;
					}
				}
				else if (_comp(tmp->value.first, val.first)){
					if (tmp->right == nil){
						tmp->right = n;
						n->parent = tmp;
						break;
					}
					else{
						tmp = tmp->right;
					}
				}
				else{
					_alloc.destroy(n);
					_alloc.deallocate(n, 1);
					return tmp;
				}
			}
			++_size;
			rebalance(n);
			return n;
		}

		t_node<Key, T>	*deleteNode(t_node<Key, T> *node){
			if (node == nil)
				return nil;
			t_node<Key, T>	*y = node;
			t_node<Key, T>	*x = nullptr;
			bool		color = node->color; 			

			if (node->left == nil){
				x = node->right;
				transplant(node, node->right);
			}
			else if (node->right == nil){
				x = node->left;
				transplant(node, node->left);
			}
			else{
				y = min(node->right);
				color = y->color;
				x = y->right;
				if (y->parent == node)
					x->parent = node;
				else{
					transplant(y, y->right);
					y->right = node->right;
					y->right->parent = y;
				}
				transplant(node, y);
				y->left = node->left;
				y->left->parent = y;
				y->color = node->color;
			}
			if (color == BLACK)
				deleteFixUp(x);
			// std::cout << node->value.first << " deleted val " << node << " adder \n";
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
			--_size;

			return x;
		}

		t_node<Key, T>	*findNode(const Key &val) const {
			t_node<Key, T> *tmp = root;

			while (tmp != nil){
				if (val == tmp->value.first)
					return tmp;
				else if (_comp(val, tmp->value.first))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			return this->nil;
		}

		t_node<Key, T>	*min(t_node<Key, T> *node) const {
			t_node<Key, T> * tmp = node;
			if (node == nil)
				return nil;
			while (tmp->left != nil)
				tmp = tmp->left;
			return tmp;
		}

		t_node<Key, T>	*max(t_node<Key, T> *node){
			if (node == nil)
				return nil;
			while (node->right != nil)
				node = node->right;
			return node;
		}

		t_node<Key, T>	*successor(t_node<Key, T> *node){
			if (node == nil)
				return node;
			if (node->right != nil)
				return min(node->right);
			else{
				t_node<Key, T> *tmp = node;
				while (tmp != root){
					if (tmp->parent->left == tmp)
						return tmp->parent;
					tmp = tmp->parent;
				}
				return nil;
			}
		}

		t_node<Key, T>	*predecessor(t_node<Key, T> *node){
			if (node == nil)
				return node;
			if (node->left != nil)
				return max(node->left);
			else{
				t_node<Key, T> *tmp = node;
				while (tmp != root){
					if(tmp->parent->right == tmp)
						return tmp->parent;
					tmp = tmp->parent;
				}
				return nil;
			}
		}

		size_t		get_size() const {
			return _size;
		}
		
		bool 		empty() const {
			return root == nil;
		}

		void	clearHelper(t_node<Key, T>	*node){
			if (node == nil){
				return;
			}
			clearHelper(node->left);
			clearHelper(node->right);
			if (node != nil){
				_alloc.destroy(node);
				_alloc.deallocate(node, 1);
			}
		}

		void	clear(t_node<Key, T>	*node){
			if (node != nil && node != NULL)
				clearHelper(node);
			root = nil;
			_size = 0;
		}

		t_node<Key, T>	*clone(t_node<Key, T>	*node,const Tree<Key, T, Comp> &tree){
			if (node == tree.nil)
				return nil;
			t_node<Key, T>	*nwn = _alloc.allocate(1);
			_alloc.construct(nwn, node->value, nil);
			nwn->color = node->color;
			nwn->value = node->value;
			nwn->left = clone(node->left, tree);
			nwn->right = clone(node->right, tree);
			if (node->right != nil)
				nwn->right->parent = nwn;
			if (node->left != nil)
				nwn->left->parent = nwn;
			return nwn;
		}
		t_node<Key, T> *getNil() const {
			return nil;
		}
		t_node<Key, T> *getRoot() const {
			return root;
		}

		void	swap(Tree<Key, T, Comp> &other){
			t_node<Key, T>	*swapRoot = root;
			t_node<Key, T>	*swapNil = nil;
			Alloc			swapAlloc = _alloc;
			size_t			swapSize = _size;
			Comp			swapComp = _comp;

			root = other.root;
			nil = other.nil;
			_alloc = other._alloc;
			_size = other._size;
			_comp = other._comp;

			other.root = swapRoot;
			other.nil = swapNil;
			other._alloc = swapAlloc;
			other._size = swapSize;
			other._comp = swapComp;
		}

		void	inOrderTraversal(t_node<Key, T>	*n){

			if (n != nil){
				inOrderTraversal(n->left);
				if (n->color)
					std::cout << 'R';
				else
					std::cout << "B";
				std ::cout << "->" <<  n->value.first << ' ';
				inOrderTraversal(n->right);
			}
		}

		void	preOrderTraversal(t_node<Key, T>	*n){

			if (n != nil){
				if (n->color)
					std::cout << 'R';
				else
					std::cout << "B";
				std ::cout << "->" <<  n->value.first << ' ';
				preOrderTraversal(n->left);
				preOrderTraversal(n->right);
			}
		}
		size_t	max_size() const {
			return _alloc.max_size();
		}
};
}

#endif