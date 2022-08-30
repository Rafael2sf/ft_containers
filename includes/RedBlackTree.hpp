#pragma once

#include <functional>
#include <memory>
#include "utility.hpp"
#include "type_traits.hpp"
#include "RbtIterator.hpp"
#include <iostream>

namespace ft
{
	enum RbtColor {
		red = 0,
		black = 1,
		double_black = 2
	};

	template <class T>
	struct RbtNode
	{
		typedef RbtNode<T> *		node_pointer;
		typedef RbtNode<T> const*	const_node_pointer;

		T				*data;
		RbtColor		color;
		node_pointer	left;
		node_pointer	right;
		node_pointer	parent;

		RbtNode( void )
		: color(red), left(0), right(0), parent(0)
		{}
	};

 	// struct	RbtNode : RbtBaseNode
	// {
	// 	typedef RbtNode<T>*			link_type;
	// 	T	data;
	// };

	template	<class Key,
				class T,
				class Compare = std::less<Key>,
				class Alloc = std::allocator<pair<Key,T> >
	> class RedBlackTree
	{
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef pair<key_type, mapped_type>					value_type;
			typedef Compare										key_compare;
			// typedef Compare									value_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef size_t										size_type;
			// iterators + ptrdiff

		protected:
			typedef RbtNode<value_type>							node;
			typedef RbtNode<value_type> const					const_node;
			typedef RbtNode<value_type> *						node_pointer;
			typedef RbtNode<value_type> const*					const_node_pointer;
			typedef std::allocator<node>						node_allocator;

			node_pointer	_root;
			size_type		_count;

		private:
			allocator_type	_allocator;
			node_allocator	_node_allocator;
			Compare			_compare;

		public:

			~RedBlackTree()
			{
				this->_n_destroy(node_pointer(_root));
				_root = 0;
				_count = 0;
			}

			RedBlackTree( void )
			: _root(0), _count(0)
			{}

			RedBlackTree( RedBlackTree const& __other )
			: _root(0), _count(0)
			{ (void)__other; }

			// range constructor
			// operator=

			void
			insert( value_type const& __pair )
			{
				if (!_count)
				{
					_root = _n_allocate(__pair);
					_root->color = black;
				}
				else
					_n_insert(_root, __pair);
				_count++;
			}

			void
			print( void )
			{
				std::cout << "TREE\nname |\tcolor |\tkey |\t~\tparent|\tleft|\tright|" << '\n';
				_in_order(_root);
			}

			// node_pointer
			// nodeFind( key_type const& __val )
			// {
			// 	return _n_find(node_pointer(_root), __val);
			// }

			void
			erase( key_type const& __key )
			{
				node_pointer	del;
				node_pointer	rep;

				if (!_count)
					return ;
				del = _n_find(node_pointer(_root), __key);
				if (!del)
					return ;
				rep = _n_erase_sucessor(del);
				/* double black requires tree rebalance */
				if (del->color == black && (!rep || rep->color == black))
					_n_erase_balance(del);
				_n_remove(del);
				/* Bring blackness to root or replacer node  */
				if (rep && (rep == _root || (rep->color == red && del->color == black)))
					rep->color = black;
				_n_destroy(del);
				_count--;
			}

			// void
			// all_black( void )
			// {
			// 	_in_order_black(node_pointer(_root));
			// }

			bool
			isValid( void )
			{
				size_type	max_h, min_h;

				if (!_root)
					return true;
				if (_root->color != black)
					return false;
				return _n_verify_balance(_root, max_h, min_h);
			}

			bool
			inOrder( void )
			{

				if (!_root)
					return true;
				return _n_order(_root);
			}

		private:

			node_pointer
			_n_erase_sucessor( node_pointer & __n )
			{
				node_pointer	tmp;

				if (!__n)
					return NULL;
				if (__n->left && __n->right)
				{
					tmp = _n_max(__n->left);
					_allocator.destroy(__n->data);
					_allocator.construct(__n->data, *tmp->data);
					__n = tmp;
					tmp = _n_erase_sucessor(__n);
				}
				if (!__n->left)
					return __n->right;
				if (!__n->right)
					return __n->left;
				return NULL;
			}

			void
			_n_erase_balance( node_pointer __d )
			{
				node_pointer	s;
				node_pointer	i;

				i = __d;
				i->color = double_black;
				/* loop as long as i is not root and i is a double black node, in order to
					balance the tree the db node must be removed */
				while (i != _root && i->color == double_black)
				{
					/* the sibling node will be used to decide which "case"
						to call, a sibling is guaranted to exist */
					if (i == i->parent->left)
						s = i->parent->right;
					else
						s = i->parent->left;
					/* if sibling and his children are black, then do a
						"color swap" and repeat as long as parent is also black */
					if (s->color == black && ((!s->left || s->left->color == black)
						&& (!s->right || s->right->color == black)))
					{
						i->color = black;
						s->color = red;
						if (s->parent->color == black)
							s->parent->color = double_black;
						else
							s->parent->color = black;
						i = i->parent;
					}
					/* if sibling is red, swap color with parent and
						rotate db in oposite direction */
					else if (s->color == red)
					{
						std::swap(s->color, s->parent->color);
						if (s == s->parent->right)
							_n_rotate_rr(s, false);
						else
							_n_rotate_ll(s, false);
					}
					else if (i == i->parent->left)
					{
						/* if the near child of s from i is red, swap s color with s near child
							and call the respective rotation */
					 	if (s->left && s->left->color == red
							&& (!s->right || s->right->color == black))
						{
							std::swap(s->color, s->left->color);
							_n_rotate_ll(s->left, false);
						}
						/* if the far child of s from i is red, swap s color with s parent
							and call the respective rotation */
						if (s->right && s->right->color == red)
						{
							std::swap(s->parent->color, s->color);
							_n_rotate_rr(s, false);
							i->color = black;
							s->right->color = black;
							return ;
						}
					}
					/* same as above but for opossite side */
					else 
					{
						if (i == i->parent->right && s->right && s->right->color == red
								&& (!s->left || s->left->color == black))
						{
							std::swap(s->color, s->right->color);
							_n_rotate_rr(s->right, false);
						}
						if (s->left && s->left->color == red)
						{
							std::swap(s->parent->color, s->color);
							_n_rotate_ll(s, false);
							i->color = black;
							s->left->color = black;
							return ;
						}
					}
				}
				_root->color = black;
			}

			void
			_n_remove( node_pointer __n )
			{
				if (!__n)
					return ;
				if (!__n->left)
				{
					if (__n->parent)
					{
						if (__n == __n->parent->left)
							__n->parent->left = __n->right;
						else
							__n->parent->right = __n->right;
						if (__n->right)
							__n->right->parent = __n->parent;
					}
					else
					{
						//_n_print("root_replace", __n);
						_root = __n->right;
						if (_root)
							_root->parent = 0;
					}
					__n->right = 0;
				}
				else if (!__n->right)
				{
					if (__n->parent)
					{
						if (__n == __n->parent->left)
							__n->parent->left = __n->left;
						else
							__n->parent->right = __n->left;
						if (__n->left)
							__n->left->parent = __n->parent;
					}
					else
					{
						_root = __n->left;
						_root->parent = 0;
					}
					__n->left = 0;
				}
			}

			void
			_n_insert_balance( node_pointer __n )
			{
				/* check for violations as long as parent color is red */
				while (__n != _root 
					&& __n->parent->color == red)
				{
					/* if parent is left of grandparent */
					if (__n->parent->parent
						&& __n->parent == __n->parent->parent->left)
					{
						/* if uncle of node is red, a color swap is enough to fix */
						if (__n->parent->parent->right
							&& __n->parent->parent->right->color == red)
						{
							_n_insert_cswap(__n, true);
						}
						/* otherwise rotations are require */
						else
						{
							if (__n == __n->parent->right)
								_n_rotate_lr(__n);
							__n = __n->parent;
							__n = _n_rotate_ll(__n, true);
						}
					}
					/* parent is right of grandparent */
					else if (__n->parent->parent)
					{
						/* if uncle of node is red, a color swap is enough to fix */
						if (__n->parent->parent->left 
							&& __n->parent->parent->left->color == red)
						{
							_n_insert_cswap(__n, false);
						}
						/* otherwise rotations are require */
						else
						{
							if (__n == __n->parent->left)
								_n_rotate_rl(__n);
							__n = __n->parent;
							__n = _n_rotate_rr(__n, true);
						}
					}
				}
				_root->color = black;
			}

			node_pointer
			_n_rotate_ll( node_pointer __n, bool __recolor )
			{
				node_pointer	tmp;

				tmp = __n->parent;
				tmp->left = __n->right;
				if (tmp->left)
					tmp->left->parent = tmp;
				if (tmp->parent)
				{
					if (tmp == tmp->parent->left)
						tmp->parent->left = __n;
					else
						tmp->parent->right = __n;
					__n->parent = tmp->parent;
				}
				else
				{
					_root = __n;
					_root->parent = 0;
				}
				__n->right = tmp;
				tmp->parent = __n;
				if (__recolor)
				{
					tmp->color = red;
					__n->color = black;
				}
				__n = tmp;
				return __n;
			}

			void
			_n_rotate_lr( node_pointer & __n )
			{
				node_pointer	tmp;

				tmp = __n;
				__n = __n->parent;
				__n->parent->left = tmp;
				tmp->parent = __n->parent;
				__n->right = tmp->left;
				if (tmp->left)
					tmp->left->parent = __n;
				tmp->left = __n;
				__n->parent = tmp;
			}

			node_pointer
			_n_rotate_rr( node_pointer __n, bool __recolor )
			{
				node_pointer	tmp;

				tmp = __n->parent;
				tmp->right = __n->left;
				if (tmp->right)
					tmp->right->parent = tmp;
				if (tmp->parent)
				{
					if (tmp == tmp->parent->right)
						tmp->parent->right = __n;
					else
						tmp->parent->left = __n;
					__n->parent = tmp->parent;
				}
				else
				{
					_root = __n;
					_root->parent = 0;
				}
				__n->left = tmp;
				tmp->parent = __n;
				if (__recolor)
				{
					tmp->color = red;
					__n->color = black;
				}
				__n = tmp;
				return __n;
			}

			void
			_n_rotate_rl( node_pointer & __n )
			{
				node_pointer	tmp;

				tmp = __n;
				__n = __n->parent;
				__n->parent->right = tmp;
				tmp->parent = __n->parent;
				__n->left = tmp->right;
				if (tmp->right)
					tmp->right->parent = __n;
				tmp->right = __n;
				__n->parent = tmp;
			}

			void
			_n_insert_cswap( node_pointer & __n, bool __left_swap )
			{
				__n->parent->color = black;
				__n->parent->parent->color = red;
				if (__left_swap)
					__n->parent->parent->right->color = black;
				else
					__n->parent->parent->left->color = black;
				__n = __n->parent->parent;
			}

			node_pointer
			_n_insert( node_pointer __n, value_type const& __pair )
			{
				if (!__n)
					return (NULL);
				if (_compare( __n->data->first, __pair.first))
				{
					if (!__n->right)
					{
						__n->right = _n_allocate(__pair);
						__n->right->parent = __n;
						_n_insert_balance(__n->right);
						return (__n);
					}
					return (_n_insert(__n->right, __pair));
				}
				if (!__n->left)
				{
					__n->left = _n_allocate(__pair);
					__n->left->parent = __n;
					_n_insert_balance(__n->left);
					return (__n);
				}
				return (_n_insert(__n->left, __pair));
			}

			node_pointer
			_n_allocate( value_type const& __pair )
			{
				node_pointer tmp = _node_allocator.allocate(1);
				_node_allocator.construct(tmp, node());
				tmp->data = _allocator.allocate(1);
				_allocator.construct(tmp->data, __pair);
				return tmp;
			}

			// void
			// _in_order( node_pointer __curr )
			// {
			// 	if (!__curr)
			// 		return ;
			// 	_in_order(__curr->left);
			// 	_n_print("", __curr);
			// 	_in_order(__curr->right);
			// }

			// void
			// _in_order_black( node_pointer __curr )
			// {
			// 	if (!__curr)
			// 		return ;
			// 	_in_order_black(__curr->left);
			// 	__curr->color = black;
			// 	_in_order_black(__curr->right);
			// }

			void
			_n_destroy( node_pointer __n )
			{
				if (!__n)
					return ;
				_n_destroy(__n->left);
				_n_destroy(__n->right);
				_allocator.destroy(__n->data);
				_allocator.deallocate(__n->data, 1);
				_node_allocator.destroy(__n);
				_node_allocator.deallocate(__n, 1);
			}

			node_pointer
			_n_find( node_pointer __n, key_type const& val )
			{
				if (!__n)
					return (NULL);
				if (_compare(val, __n->data->first) 
					&& !_compare(__n->data->first, val))
					return (_n_find(__n->left, val));
				else if (_compare(__n->data->first, val) 
					&& !_compare(val, __n->data->first))
					return (_n_find(__n->right, val));
				return (__n);
			}

			node_pointer
			_n_min( node_pointer __n )
			{
				if (!__n)
					return NULL;
				while (__n->left)
					__n = __n->left;
				return (__n);
			}

			node_pointer
			_n_max( node_pointer __n )
			{
				if (!__n)
					return NULL;
				while (__n->right)
					__n = __n->right;
				return (__n);
			}

			void
			_n_print( std::string const& __s, node_pointer const& __n )
			{
				std::cout << __s << "\t";
				if (__n)
				{
					if (__n->color == black)
						std::cout << "black\t";
					else if (__n->color == double_black)
						std::cout << "d_black\t";
					else
						std::cout << "red\t";
					std::cout << __n->data->first << "\t\t";
					if (__n->parent)
						std::cout << __n->parent->data->first;
					else
					{
						if (__n == _root)
							std::cout << "root";
						else
							std::cout << "nil";
					}
					std::cout << "\t";
					if (__n->left)
						std::cout << __n->left->data->first;
					else
						std::cout << "nil";
					std::cout << "\t";
					if (__n->right)
						std::cout << __n->right->data->first;
					else
						std::cout << "nil";
				}
				else
					std::cout << "nil";
				std::cout << '\n';
			}

			bool
			_n_verify_balance( node_pointer __n, size_type & __max_h, size_type & __min_h )
			{
				size_type	lmax_h = 0, lmin_h = 0, rmax_h = 0, rmin_h = 0;

				if (!__n)
				{
					__max_h = __min_h = 0;
					return true;
				}

				if (__n->color == red
					&& ((__n->left && __n->left->color == red) 
						|| (__n->right && __n->right->color == red)
						|| (__n->parent && __n->parent->color == red)))
				{
					std::cout << "bad red node" << std::endl;
					return false;
				}
				if (_n_verify_balance(__n->left, lmax_h, lmin_h) == false)
				{
					return false;
				}
				if (_n_verify_balance(__n->right, rmax_h, rmin_h) == false)
				{
					return false;
				}
				__max_h = std::max(lmax_h, rmax_h) + 1;
				__min_h = std::min(lmin_h, rmin_h) + 1;
				if (__max_h <= 2 * __min_h)
					return true;
				return false;
			}

			size_type
			_n_verify_colors( node_pointer __n )
			{
				if (!__n)
					return 1;
				if (__n->color == red
					&& ((__n->left && __n->left->color == red) 
						|| (__n->right && __n->right->color == red)
						|| (__n->parent && __n->parent->color == red)))
				{
					std::cout << "bad red node" << std::endl;
					return false;
				}
				return (_n_verify_colors(__n->left) + _n_verify_colors(__n->right) + (__n->color == black));
			}

			bool _n_order(node_pointer node)
			{
				if (node == NULL)
					return 1;

				if (node->left != NULL && node->left->data->first > node->data->first)
					return 0;

				if (node->right != NULL && node->right->data->first < node->data->first)
					return 0;

				if (!_n_order(node->left) || !_n_order(node->right))
					return 0;

				return 1;
			}
	};
}
