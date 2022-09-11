#pragma once

#include <functional>
#include <memory>
#include "utility.hpp"
#include "type_traits.hpp"
#include "RbtIterator.hpp"
#include <iostream>

/**
 *	TODO:
		multiple insert/erase templates
		iterators
		value_compare
 */

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
		typedef T					value_type;
		typedef RbtNode<T> *		node_pointer;
		typedef RbtNode<T> const*	const_node_pointer;

		T				data;
		RbtColor		color;
		node_pointer	left;
		node_pointer	right;
		node_pointer	parent;

		RbtNode( value_type const& __val )
		: color(red), left(0), right(0), parent(0)
		{
			data = __val;
		}
	};

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
			typedef Compare										value_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef size_t										size_type;
			typedef RbtIterator<value_type>						iterator;
			typedef RbtIterator<const value_type>				const_iterator;
			// typedef ft::reverse_iterator<iterator>				reverse_iterator;
			// typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type
																difference_type;

		protected:
			typedef RbtNode<value_type>							node;
			typedef RbtNode<value_type> const					const_node;
			typedef RbtNode<value_type> *						node_pointer;
			typedef RbtNode<value_type> const*					const_node_pointer;
			typedef typename Alloc::template rebind<RbtNode<value_type> >::other
																node_allocator;

			node_pointer	_root;
			size_type		_count;
			key_compare		_compare;
			allocator_type	_allocator;
			node_allocator	_node_allocator;

		public:

			~RedBlackTree()
			{
				if (_count)
					_n_destroy(node_pointer(_root));
				_count = 0;
			}

			explicit
			RedBlackTree( key_compare const& __comp = key_compare(),
				allocator_type const& __alloc = allocator_type() )
			: _root(0), _count(0), _compare(__comp),
				_allocator(__alloc),  _node_allocator()
			{}

			template <class InputIterator>
			RedBlackTree( InputIterator __first, InputIterator __last,
				key_compare const& __comp = key_compare(),
				allocator_type const& __alloc = allocator_type() )
			: _root(0), _count(0), _compare(__comp),
				_allocator(__alloc), _node_allocator()
			{
				_n_range(__first, __last);
			}

			RedBlackTree( RedBlackTree const& __other )
			: _root(0), _count(0), _compare(),
				_allocator(),  _node_allocator()
			{
				_n_range(__other.begin(), __other.end());
			}

			RedBlackTree &
			operator=( RedBlackTree const& __rhs )
			{
				this->clear();
				_n_range(__rhs.begin(), __rhs.end());
				return *this;
			}

			key_compare
			key_comp( void ) const
			{
				return key_compare();
			}

			value_compare
			value_comp( void ) const
			{
				return value_compare();
			}

			/* iterators */

			iterator
			begin( void )
			{
				return iterator(&_root, _n_min(_root));
			}

			const_iterator
			begin( void ) const
			{
				return const_iterator(&_root, _n_min(_root));
			}

			iterator
			end( void )
			{
				return iterator(&_root);
			}

			const_iterator
			end( void ) const
			{
				return const_iterator(node_pointer(&_root)); // sadly not working
			}

			// reverse_iterator
			// rbegin( void )
			// {
			// 	return reverse_iterator(iterator(&_root, _n_max(_root)));
			// }

			// const_reverse_iterator
			// rbegin( void ) const
			// {
			// 	return const_reverse_iterator(
			// 		const_iterator(&_root, _n_max(_root)));
			// }

			// reverse_iterator
			// rend( void )
			// {
			// 	return reverse_iterator(iterator(&_root));
			// }

			// const_reverse_iterator
			// rend( void ) const
			// {
			// 	return const_reverse_iterator(const_iterator(&_root));
			// }

			/* element acess */

			allocator_type 
			get_allocator() const
			{
				return _allocator;
			}

			mapped_type & 
			operator[]( Key const& __key )
			{
				return (_n_insert(_root,
					make_pair(__key, mapped_type())).first->second);
			}

			mapped_type & 
			at( key_type const& __key )
			{
				iterator	n;

				n = _n_find(_root, __key);
				if (n == this->end())
					throw std::out_of_range("RedBlackTree: at()");
				return n->second;
			}

			mapped_type const& 
			at( key_type const& __key ) const
			{
				iterator	n;

				n = this->find(__key);
				if (n == this->end())
					throw std::out_of_range("RedBlackTree: at()");
				return n->second;
			}

			/* Capacity */

			bool
			empty( void ) const
			{
				return _count == 0;
			}

			size_type
			size( void ) const
			{
				return _count;
			}

			size_type
			max_size( void ) const
			{
				return _node_allocator.max_size();
			}

			/* modifiers */

			void
			clear( void )
			{
				if (_count)
					_n_destroy(_root);
				_count = 0;
			}

			pair<iterator, bool>
			insert( value_type const& __val )
			{
				return _n_insert(_root, __val);
			}

			iterator
			insert( iterator __position, value_type const& __val )
			{
				return (_n_insert(__position._M_node, __val)).first;
			}

			template <class InputIterator>
			void
			insert(InputIterator __first, InputIterator __last )
			{
				_n_range(__first, __last);
			}

			void
			erase( iterator __pos )
			{
				if (__pos != this->end())
					_n_erase(__pos._M_node, __pos->first);
			}

			size_type
			erase( key_type const& __key )
			{
				return _n_erase(_root, __key);
			}

			void
			erase(iterator __first, iterator __last)
			{
				while (__first != __last)
				{
					_n_erase(__first._M_node, __first->key);
					__first++;
				}
			}

			void
			swap( RedBlackTree & __other )
			{
				std::swap(this->_count, __other._count);
				std::swap(this->_root, __other._root);
				// undefined behavior
				std::swap(this->_allocator, __other._allocator);
				std::swap(this->_node_allocator, __other._node_allocator);
				std::swap(this->_compare, __other._compare);
			}

			/* operations */

			iterator
			find( const key_type& k )
			{
				return this->find(k);
			}

			const_iterator
			find( const key_type& k ) const
			{
				return this->find(k);
			}

			size_type
			count( key_type const& __key ) const
			{
				try { this->at(__key); }
				catch ( std::out_of_range const& ) {
					return false;
				}
				return true;
			}

			void
			print( void )
			{
				std::cout << "TREE (" << _count << ")" << '\n';
				std::cout << "name |\tcolor |\tkey |\t~\tparent|\tleft|\tright|" << '\n';
				_in_order(_root);
			}

		private:

			void
			_in_order( node_pointer __curr )
			{
				if (!__curr)
					return ;
				_in_order(__curr->left);
				_n_print("", __curr);
				_in_order(__curr->right);
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
					std::cout << __n->data.first << "\t\t";
					if (__n->parent)
						std::cout << __n->parent->data.first;
					else
					{
						if (__n == _root)
							std::cout << "root";
						else
							std::cout << "nil";
					}
					std::cout << "\t";
					if (__n->left)
						std::cout << __n->left->data.first;
					else
						std::cout << "nil";
					std::cout << "\t";
					if (__n->right)
						std::cout << __n->right->data.first;
					else
						std::cout << "nil";
				}
				else
					std::cout << "nil";
				std::cout << '\n';
			}

			/* erase */

			bool
			_n_erase( node_pointer __hint, key_type const& __key )
			{
				iterator		pos;
				node_pointer	del;
				node_pointer	rep;

				if (!_count)
					return false;
				pos = _n_find(node_pointer(__hint), __key);
				if (pos == this->end())
					return false;
				del = pos._M_node;
				rep = _n_erase_sucessor(del);
				/* double black requires tree rebalance */
				if (del->color == black && (!rep || rep->color == black))
					_n_erase_balance(del);
				_n_remove(del);
				/* Bring blackness to root or replacer node  */
				if (rep && (rep == _root
					|| (rep->color == red && del->color == black)))
					rep->color = black;
				_n_destroy(del);
				_count--;
				return true;
			}

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
						if (s->right && s->right->color == red
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

			/* insert a element incrementing size and balancing the red-black tree
				return a iterator to the inserted element on sucess otherwise end() */
			pair<iterator, bool>
			_n_insert( node_pointer __hint, value_type const& __pair )
			{
				pair<iterator, bool> tmp;

				if (!_count)
				{
					_root = _n_allocate(__pair);
					_root->color = black;
					tmp = make_pair(iterator(&_root, _root), true);
				}
				else
				{
					if (!__hint)
						__hint = _root;
					while (__hint->parent && _compare(__hint->data.first, __pair.first))
						__hint = __hint->parent;
					tmp = _n_insert_find(__hint, __pair);
				}
				if (tmp.second)
					_count++;
				return tmp;
			}

			/* recursevly find the insert position or duplicated */
			pair<iterator, bool>
			_n_insert_find( node_pointer __n, value_type const& __pair )
			{
				if (_compare(__n->data.first, __pair.first))
				{
					if (!__n->right)
					{
						__n->right = _n_allocate(__pair);
						__n->right->parent = __n;
						__n = __n->right;
						_n_insert_balance(__n);
						return make_pair(iterator(&_root, __n), true);
					}
					return (_n_insert_find(__n->right, __pair));
				}
				else if (_compare(__pair.first, __n->data.first))
				{
					if (!__n->left)
					{
						__n->left = _n_allocate(__pair);
						__n->left->parent = __n;
						__n = __n->left;
						_n_insert_balance(__n);
						return make_pair(iterator(&_root, __n), true);
					}
					return (_n_insert_find(__n->left, __pair));
				}
				return make_pair(iterator(&_root, __n), false);
			}

			/* insert_balance performs the required operations to balance the tree */
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
					/* same as above but for oposite side  */
					else if (__n->parent->parent)
					{
						if (__n->parent->parent->left 
							&& __n->parent->parent->left->color == red)
						{
							_n_insert_cswap(__n, false);
						}
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

			/* insert_balance helper swaps color with uncle node */
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

			/* red-black tree rotations ( similar to a BST )
				ll = left-left / rr = right-right 
				lr = left-right / rl = right-left */

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

			/* detach a node and remove it */
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

			/* allocate a node using the given allocator
				but rebinded to a new type (node_pointer) */
			node_pointer
			_n_allocate( value_type const& __pair )
			{
				node_pointer tmp = _node_allocator.allocate(1);
				_node_allocator.construct(tmp, node(__pair));
				// tmp->data = _allocator.allocate(1);
				// _allocator.construct(tmp->data, __pair);
				return tmp;
			}

			/* destroy a node and all its children */
			void
			_n_destroy( node_pointer __n )
			{
				if (!__n)
					return ;
				_n_destroy(__n->left);
				_n_destroy(__n->right);
				// _allocator.destroy(__n->data);
				// _allocator.deallocate(__n->data, 1);
				_node_allocator.destroy(__n);
				_node_allocator.deallocate(__n, 1);
			}

			/* recursevly search for a key and
				return it on sucess otherwise end() */
			iterator
			_n_find( node_pointer __n, key_type const& val )
			{
				if (!__n)
					return (this->end());
				if (_compare(val, __n->data.first) 
					&& !_compare(__n->data.first, val))
					return (_n_find(__n->left, val));
				else if (_compare(__n->data.first, val) 
					&& !_compare(val, __n->data.first))
					return (_n_find(__n->right, val));
				return (iterator(&_root, __n));
			}

			node_pointer
			_n_min( node_pointer __n ) const
			{
				if (!__n)
					return NULL;
				while (__n->left)
					__n = __n->left;
				return (__n);
			}

			node_pointer
			_n_max( node_pointer __n ) const
			{
				if (!__n)
					return NULL;
				while (__n->right)
					__n = __n->right;
				return (__n);
			}

			/* other */

			template <class InputIterator>
			void
			_n_range(InputIterator __first, InputIterator __last)
			{
				while (__first != __last)
					_n_insert(_root, *__first++);
			}
	};
}
