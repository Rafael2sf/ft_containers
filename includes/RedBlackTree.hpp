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
		red = false,
		black = true
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

		private:
			typedef RbtNode<value_type>							node;
			typedef RbtNode<value_type> const					const_node;
			typedef RbtNode<value_type> *						node_pointer;
			typedef RbtNode<value_type> const*					const_node_pointer;
			typedef std::allocator<node>						node_allocator;

			node_pointer	_root;
			size_type		_count;
			allocator_type	_allocator;
			node_allocator	_node_allocator;
			Compare			_compare;

		public:
			~RedBlackTree()
			{
				this->_destroy(node_pointer(_root));
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

			void\
			insert( value_type const& __pair )
			{
				node_pointer	tmp;

				if (!_count)
				{
					_empty_insert(__pair);
					return ;
				}
				tmp = _find_insert_position_of(_root, __pair.first);
				if (!tmp->right && __pair.first > tmp->data->first)
				{
					tmp->right = _allocate_node(__pair);
					tmp->right->parent = tmp;
					_insert_fix(tmp->right);
				}
				else
				{
					tmp->left = _allocate_node(__pair);
					tmp->left->parent = tmp;
					_insert_fix(tmp->left);
				}
				_count++;
			}

			node_pointer
			getRoot( void ) const { return (_root); }

			void
			printTree( void )
			{
				std::cout << " -- tree -- " << '\n';
				_in_order(_root);
			}

		private:

			void
			_insert_fix( node_pointer __pos )
			{
				/* check for violations as long as parent color is red */
				while (__pos != _root 
					&& __pos->parent->color == red)
				{
					/* if parent is left of grandparent */
					if (__pos->parent->parent
						&& __pos->parent == __pos->parent->parent->left)
					{
						/* if uncle of node is red, a color swap is enough to fix */
						if (__pos->parent->parent->right
							&& __pos->parent->parent->right->color == red)
						{
							_insert_color_swap(__pos, true);
						}
						/* otherwise we must call the respective rotation */
						else
						{
							/* in case pos is right of parent we must do a left-right rotation
								to put it in place for a left-left rotation */
							if (__pos == __pos->parent->right)
								_insert_lr_rotate(__pos);
							_insert_ll_rotate(__pos);
						}
					}
					/* parent is right of grandparent */
					else if (__pos->parent->parent)
					{
						/* if uncle of node is red, a color swap is enough to fix */
						if (__pos->parent->parent->left 
							&& __pos->parent->parent->left->color == red)
						{
							_insert_color_swap(__pos, false);
						}
						/* otherwise we must call the respective rotation */
						else
						{
							/* in case pos is right of parent we must do a right-left rotation
								to put it in place for a right-right rotation */
							if (__pos == __pos->parent->left)
								_insert_rl_rotate(__pos);
							_insert_rr_rotate(__pos);
						}
					}
				}
				_root->color = black;
			}

			void
			_empty_insert( value_type const& __pair )
			{
				_root = _allocate_node(__pair);
				_root->color = black;
				_count++;
			}

			void
			_insert_ll_rotate( node_pointer & __pos )
			{
				node_pointer	tmp;

				__pos = __pos->parent;
				tmp = __pos->parent;
				tmp->left = __pos->right;
				if (tmp->left)
					tmp->left->parent = tmp;
				if (tmp->parent)
				{
					if (tmp == tmp->parent->left)
						tmp->parent->left = __pos;
					else
						tmp->parent->right = __pos;
					__pos->parent = tmp->parent;
				}
				else
				{
					_root = __pos;
					_root->parent = 0;
				}
				__pos->right = tmp;
				tmp->parent = __pos;
				tmp->color = red;
				__pos->color = black;
				__pos = tmp;
			}

			void
			_insert_lr_rotate( node_pointer & __pos )
			{
				node_pointer	tmp;

				tmp = __pos;
				__pos = __pos->parent;
				__pos->parent->left = tmp;
				tmp->parent = __pos->parent;
				__pos->right = tmp->left;
				if (tmp->left)
					tmp->left->parent = __pos;
				tmp->left = __pos;
				__pos->parent = tmp;
			}

			void
			_insert_rr_rotate( node_pointer & __pos )
			{
				node_pointer	tmp;

				__pos = __pos->parent;
				tmp = __pos->parent;
				tmp->right = __pos->left;
				if (tmp->right)
					tmp->right->parent = tmp;
				if (tmp->parent)
				{
					if (tmp == tmp->parent->right)
						tmp->parent->right = __pos;
					else
						tmp->parent->left = __pos;
					__pos->parent = tmp->parent;
				}
				else
				{
					_root = __pos;
					_root->parent = 0;
				}
				__pos->left = tmp;
				tmp->parent = __pos;
				tmp->color = red;
				__pos->color = black;
				__pos = tmp;
			}

			void
			_insert_rl_rotate( node_pointer & __pos )
			{
				node_pointer	tmp;

				tmp = __pos;
				__pos = __pos->parent;
				__pos->parent->right = tmp;
				tmp->parent = __pos->parent;
				__pos->left = tmp->right;
				if (tmp->right)
					tmp->right->parent = __pos;
				tmp->right = __pos;
				__pos->parent = tmp;
			}

			void
			_insert_color_swap( node_pointer & __pos, bool __left_swap )
			{
				__pos->parent->color = black;
				__pos->parent->parent->color = red;
				if (__left_swap)
					__pos->parent->parent->right->color = black;
				else
					__pos->parent->parent->left->color = black;
				__pos = __pos->parent->parent;
			}

			node_pointer
			_allocate_node( value_type const& __pair )
			{
				node_pointer tmp = _node_allocator.allocate(1);
				_node_allocator.construct(tmp, node());
				tmp->data = _allocator.allocate(1);
				_allocator.construct(tmp->data, __pair);
				return tmp;
			}

			node_pointer
			_find_insert_position_of( node_pointer __curr, key_type const& __key )
			{
				if (!__curr)
					return (NULL);
				if (_compare( __curr->data->first, __key))
				{
					if (!__curr->right)
						return (__curr);
					return (_find_insert_position_of(__curr->right, __key));
				}
				if (!__curr->left)
					return (__curr);
				return (_find_insert_position_of(__curr->left, __key));
			}

			void
			_in_order( node_pointer __curr )
			{
				if (!__curr)
					return ;
				_in_order(__curr->left);
				std::cout << __curr->data->first;
				if (__curr->color == red)
					std::cout << "\tred";
				else
					std::cout << "\tblack";
				std::cout << "\tl:: ";
				if (__curr->left) 
					std::cout << __curr->left->data->first; 
				else
					std::cout << "-";
				std::cout << "\tr:: ";
				if (__curr->right)
					std::cout << __curr->right->data->first;
				else
					std::cout << "-";
				std::cout << "\tp:: ";
				if (__curr->parent) 
					std::cout << __curr->parent->data->first;
				else
					std::cout << "-";
				std::cout << std::endl;
				_in_order(__curr->right);
			}

			void
			_destroy( node_pointer __pos )
			{
				if (!__pos)
					return ;
				_destroy(__pos->left);
				_destroy(__pos->right);
				_allocator.destroy(__pos->data);
				_allocator.deallocate(__pos->data, 1);
				_node_allocator.destroy(__pos);
				_node_allocator.deallocate(__pos, 1);
			}
	};
}
