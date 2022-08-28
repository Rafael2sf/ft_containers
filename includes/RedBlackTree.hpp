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

			void
			insert( value_type const& __pair )
			{
				node_pointer	tmp;

				if (!_count)
				{
					_root = _allocate_node(__pair);
					_root->color = black;
					_count++;
					return ;
				}
				tmp = _insert_find(_root, __pair.first);
				if (!tmp->right && __pair.first > tmp->data->first)
				{
					tmp->right = _allocate_node(__pair);
					tmp->right->parent = tmp;
					_insert_fix(tmp->right);
				}
				else if (!tmp->left)
				{
					tmp->left = _allocate_node(__pair);
					tmp->left->parent = tmp;
					_insert_fix(tmp->left);
				}
				_count++;
			}

			void
			print( void )
			{
				std::cout << " -- tree -- " << '\n';
				_in_order(_root);
			}

			void
			find( key_type const& __val )
			{
				node_pointer	f;
				f = this->_find(node_pointer(_root), __val);
				if (!f)
					std::cout << "not found" << '\n';
				else
					std::cout << f->data->second << '\n';
			}

			void
			erase( key_type const& __key )
			{
				node_pointer	del;
				node_pointer	tmp;

				if (!_count)
					return ;
				tmp = _find(node_pointer(_root), __key);
				if (!tmp)
					return ;
				del = _node_detach(tmp);
				if (del->color == red)
				{
					std::cout << "case 1" << '\n';
					_print_node("tmp", tmp);
					_print_node("del", del);
					_destroy(del);
				}
				else if (tmp && tmp->color == red)
				{
					std::cout << "case 2" << '\n';
					_print_node("tmp", tmp);
					_print_node("del", del);
					tmp->color = black;
				}
				else
				{
					std::cout << "case 3" << '\n';
					del->color = double_black;
					_print_node("tmp", tmp);
					_print_node("del", del);
					_erase_fix(del);
					_destroy(del);
				}
				_count--;
				// std::cout << "del: " << del->data->first << '\t';
				// if (del->parent)
				// 	std::cout << "p: " << del->parent->data->first;
				// std::cout << '\n';
				// if (tmp)
				// {
				// 	std::cout << "replaced: " << tmp->data->first << '\t';
				// 	if (tmp->parent)
				// 		std::cout << "p: " << tmp->parent->data->first;
				// 	std::cout << '\n';
				// }
			}

		private:

			void
			_erase_fix( node_pointer  __pos )
			{
				_print_node("fix", __pos->parent);
				node_pointer	sibling;

				while (__pos != _root && __pos->color == double_black)
				{
					if (! __pos->parent->left)
						sibling = __pos->parent->right;
					else
						sibling = __pos->parent->left;
					
					if (!sibling)
					{
						std::cout << "no sibling ... quiting \n";
						return ;
					}

					// case 3:
					if ((!sibling->left || sibling->left->color == black)
						&& (!sibling->left || sibling->right->color == black))
					{
						std::cout << "\tcase 3.0" << '\n';
						sibling->color = red;
						if (__pos->parent->color == red)
							__pos->parent->color = black;
						else
							__pos->parent->color = double_black;
					}
					__pos = __pos->parent;
					std::cout << "fix loop +\n";
				}
			}

			/* return the node to be deleted */
			node_pointer
			_node_detach( node_pointer & __pos )
			{
				node_pointer	tmp;

				if (!__pos->left)
				{
					if (__pos->parent)
					{
						if (__pos == __pos->parent->left)
							__pos->parent->left = __pos->right;
						else
							__pos->parent->right = __pos->right;
						if (__pos->right)
							__pos->right->parent = __pos->parent;
					}
					else
						_root = __pos->right;
					tmp = __pos;
					__pos = __pos->right;
					tmp->right = 0;
				}
				else if (!__pos->right)
				{
					if (__pos->parent)
					{
						if (__pos == __pos->parent->left)
							__pos->parent->left = __pos->left;
						else
							__pos->parent->right = __pos->left;
						if (__pos->left)
							__pos->left->parent = __pos->parent;
					}
					else
						_root = __pos->left;
					tmp = __pos;
					__pos = __pos->left;
					tmp->left = 0;
				}
				else
				{
					tmp = _max(__pos->left);
					_allocator.destroy(__pos->data);
					_allocator.construct(__pos->data, *tmp->data);
					__pos = tmp;
					tmp = _node_detach(__pos);
				}
				return (tmp);
			}

			void
			_insert_fix( node_pointer __pos )
			{
				/* check for violations as lon50g as parent color is red */
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

						else /* otherwise we must call the respective rotation */
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
						else /* otherwise we must call the respective rotation */
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
			_insert_find( node_pointer __curr, key_type const& __key )
			{
				if (!__curr)
					return (NULL);
				if (_compare( __curr->data->first, __key))
				{
					if (!__curr->right)
						return (__curr);
					return (_insert_find(__curr->right, __key));
				}
				if (!__curr->left)
					return (__curr);
				return (_insert_find(__curr->left, __key));
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

			node_pointer
			_find( node_pointer __pos, key_type const& val )
			{
				if (!__pos)
					return (NULL);
				if (_compare(val, __pos->data->first) 
					&& !_compare(__pos->data->first, val))
					return (_find(__pos->left, val));
				else if (_compare(__pos->data->first, val) 
					&& !_compare(val, __pos->data->first))
					return (_find(__pos->right, val));
				return (__pos);
			}

			node_pointer
			_min( node_pointer __pos )
			{
				if (!__pos)
					return NULL;
				while (__pos->left)
					__pos = __pos->left;
				return (__pos);
			}

			node_pointer
			_max( node_pointer __pos )
			{
				if (!__pos)
					return NULL;
				while (__pos->right)
					__pos = __pos->right;
				return (__pos);
			}

			void
			_print_node( std::string const& __s, node_pointer const& __node )
			{
				std::cout << __s << "\t";
				if (__node)
				{
					if (__node->color)
						std::cout << "black\t";
					else
						std::cout << "red\t";
					std::cout << __node->data->first << "\t\t";
					if (__node->parent)
						std::cout << __node->parent->data->first;
					else
						std::cout << "(nil)";
					std::cout << " ";
					if (__node->left)
						std::cout << __node->left->data->first;
					else
						std::cout << "(nil)";
					std::cout << " ";
					if (__node->right)
						std::cout << "\t" << __node->right->data->first;
					else
						std::cout << "(nil)";
				}
				else
					std::cout << "(nil)";
				std::cout << '\n';
			}
	};
}
