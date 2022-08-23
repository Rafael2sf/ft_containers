#pragma once

#include <functional>
#include <memory>
#include "utility.hpp"
#include "type_traits.hpp"
#include "RbtIterator.hpp"

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

		T				data;
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

		private:
			node_pointer	_root;
			size_type		_count;
			allocator_type	_allocator;
			node_allocator	_node_allocator;

		public:
			~RedBlackTree()
			{}

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
				if (!tmp->left && __pair.first < tmp->data.first)
				{
					tmp->left = _allocate_node(__pair);
					tmp->left->parent = tmp;
					std::cout << "inserted " << __pair.first << std::endl;
					_insert_fix(tmp->left);
				}
				else
				{
					tmp->right = _allocate_node(__pair);
					tmp->right->parent = tmp;
					std::cout << "inserted " << __pair.first << std::endl;
					_insert_fix(tmp->right);
				}
				_count++;
			}

			node_pointer	getRoot( void ) const { return (_root); }

			void			printTree( void )
			{
				_in_order(_root);
			}

		private:

			void\
			_insert_fix( node_pointer __pos )
			{
				node_pointer	tmp;

				while (__pos != _root && __pos->parent->color == red)
				{
					// parent is left of gp
					if (__pos->parent->parent && __pos->parent == __pos->parent->parent->left)
					{
						// if uncle is red do color swap
						if (__pos->parent->parent->right && __pos->parent->parent->right->color == red)
						{
							std::cout << "left color-swap" << '\n';
							__pos->parent->color = black;
							__pos->parent->parent->color = red;
							__pos->parent->parent->right->color = black;
							__pos = __pos->parent->parent;
							continue ;
						}
						else
						{
							// node is right of parent
							if (__pos == __pos->parent->right)
							{
								std::cout << "(left)-right rotation" << '\n';
								// left  rotation (to do right)
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
							// left-right rotation (left is alredy done)
							std::cout << "left-(right) rotation" << '\n';
							__pos = __pos->parent;
							tmp = __pos->parent;
							tmp->left = __pos->right;
							if (tmp->left)
								tmp->left->parent = tmp;
							if (tmp->parent)
							{
								// gp is left of parent
								if (tmp == tmp->parent->left)
									tmp->parent->left = __pos;
								else
									tmp->parent->right = __pos;
								__pos->parent = tmp->parent;
							}
							else
								_root = __pos;
							__pos->right = tmp;
							tmp->parent = __pos;
							// recolor
							std::cout << "recolor" << '\n';
							tmp->color = red;
							__pos->color = black;
							//__pos = tmp;
						}
					}
					else if (__pos->parent->parent) // parent is right of gp and exits
					{
						// if uncle is red color swap
						if (__pos->parent->parent->left && __pos->parent->parent->left->color == red)
						{
							std::cout << "right color-swap" << '\n';
							__pos->parent->color = black;
							__pos->parent->parent->color = red;
							__pos->parent->parent->left->color = black;
							__pos = __pos->parent->parent;
							continue ;
						}
						else
						{
							// node is left of parent
							if (__pos == __pos->parent->left)
							{
								std::cout << "(right)-left rotation" << '\n';
								// // right  rotation (to do left)
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
							// left-right rotation (left is alredy done)
							std::cout << "right-(left) rotation" << '\n';
							__pos = __pos->parent;
							tmp = __pos->parent;
							tmp->right = __pos->left;
							if (tmp->right)
								tmp->right->parent = tmp;
							if (tmp->parent)
							{
								// gp is left of parent
								if (tmp == tmp->parent->right)
									tmp->parent->right = __pos;
								else
									tmp->parent->left = __pos;
								__pos->parent = tmp->parent;
							}
							else
							{
								_root = __pos;
								__pos->parent = NULL;
							}
							__pos->left = tmp;
							tmp->parent = __pos;
							// recolor
							std::cout << "recolor" << '\n';
							tmp->color = red;
							__pos->color = black;
							//__pos = tmp;
						}
					}
					std::cout << "loop" << '\n';
					__pos = __pos->parent;
				}
				_root->color = black;
			}

			// void
			// _insert_fix( node_pointer __pos )
			// {
			// 	while (__pos->parent && __pos->parent->color == red)
			// 	{
			// 		// case 1, x-p is gp-lc and gp-rc is red
			// 		if (__pos->parent->parent
			// 			&& __pos->parent == __pos->parent->parent->left)
			// 		{
			// 			if	(__pos->parent->parent->right
			// 				&& __pos->parent->parent->right->color == red)
			// 			{
			// 				__pos->parent->color = black;
			// 				__pos->parent->parent->color = red;
			// 				__pos->parent->parent->right->color = black;
			// 				__pos = __pos->parent;
			// 				std::cout << "left recolor" << std::endl;
			// 			}
			// 		}
			// 		// x is rc of p
			// 		else if (__pos == __pos->parent->right)
			// 		{
			// 			__pos = __pos->parent;
			// 			_left_rotate(__pos);
			// 			std::cout << "left rotate" << std::endl;
			// 			continue ;
			// 		}
			// 		else
			// 		{
			// 			if	(__pos->parent->parent->left
			// 				&& __pos->parent->parent->left->color == red)
			// 			{
			// 				__pos->parent->color = black;
			// 				__pos->parent->parent->color = red;
			// 				__pos->parent->parent->left->color = black;
			// 				__pos = __pos->parent;
			// 				std::cout << "right recolor" << std::endl;
			// 			}
			// 		}
			// 		__pos = __pos->parent;
			// 	}
			// }

			void\
			_left_rotate( node_pointer __pos )
			{
				node_pointer	tmp;

				if (!__pos->parent)
					return ;
				tmp = __pos->right;
				// set parent of current node
				if (__pos->parent)
				{
					tmp->parent = __pos->parent;
					if (__pos == __pos->parent->left)
						__pos->parent->left = __pos;
					else
						__pos->parent->right = __pos;
				}
				else
					__pos->parent = 0;

				// set right node of current
				__pos->right = tmp->left;
				if (tmp->left)
					tmp->left->parent = __pos;

				tmp->left = __pos;
				__pos->parent = tmp;
			}

			void\
			_empty_insert( value_type const& __pair )
			{
				_root = _allocate_node(__pair);
				_root->color = black;
				_count++;
			}

			node_pointer\
			_allocate_node( value_type const& __pair )
			{
				node_pointer tmp = _node_allocator.allocate(1);
				_node_allocator.construct(tmp, node());
				_allocator.construct(&tmp->data, __pair);
				return tmp;
			}

			node_pointer\
			_find_insert_position_of( node_pointer __curr, key_type const& __key )
			{
				if (!__curr)
					return (NULL);
				if (__key > (__curr->data).first)
				{
					if (!__curr->right)
						return (__curr);
					return (_find_insert_position_of(__curr->right, __key));
				}
				if (!__curr->left)
					return (__curr);
				return (_find_insert_position_of(__curr->left, __key));
			}

			void\
			_in_order( node_pointer __curr )
			{
				if (!__curr)
					return ;
				_in_order(__curr->left);
				std::cout << __curr->data.first;
				if (__curr->color == red)
					std::cout << "\tred";
				else
					std::cout << "\tblack";
				std::cout << "\tl:: ";
				if (__curr->left) 
					std::cout << __curr->left->data.first; 
				else
					std::cout << "-";
				std::cout << "\tr:: ";
				if (__curr->right)
					std::cout << __curr->right->data.first;
				else
					std::cout << "-";
				std::cout << "\tp:: ";
				if (__curr->parent) 
					std::cout << __curr->parent->data.first;
				else
					std::cout << "-";
				std::cout << std::endl;
				_in_order(__curr->right);
			}
	};

/*	{
		public:
			// typedef RbtIterator<RbtNode<value_type,
			// 	key_compare, allocator_type> *>					iterator;
			// typedef RbtIterator<RbtNode<value_type,
			// 	key_compare, allocator_type> const*>			const_iterator;
			// typedef typename iterator_traits
			// 					<iterator>::difference_type		difference_type;

		private:
			RbtNode<value_type,
				key_compare,
				allocator_type>		*_root;
			std::allocator<RbtNode
				<value_type,
				key_compare,
				allocator_type> >	_allocator;
			// key_compare				_compare;
			size_type				_count;

		public:
			~RedBlackTree() {
				_allocator.destroy(_root);
				_allocator.deallocate(_root, _count);
			}

			explicit RedBlackTree( key_compare const& __comp = key_compare(), 
				allocator_type const& __alloc = allocator_type() )
			: _allocator(__alloc), _compare(__comp), _count(0)
			{}

			template <class InputIterator>
			explicit RedBlackTree( InputIterator __first, InputIterator __last )
			: _allocator(allocator_type()), _compare(key_compare()), _count(0)
			{
				(void)__first;
				(void)__last;
			}

			template <class InputIterator>
			RedBlackTree( RedBlackTree const& __other )
			: _allocator(allocator_type()), _compare(key_compare()), _count(0)
			{
				*this = __other;
			}

			RedBlackTree & operator=( RedBlackTree const& __rhs ) {
				(void)__rhs;
				return *this;
			}

			void	insert( value_type const& __val )
			{
				if (!_count)
				{
					_root = _allocator.allocate(1);
					_allocator.construct(_root, RbtNode<value_type, key_compare, allocator_type>(__val));
					_count++;
				}
			}

			// void	inOrderPrint( void )
			// {

			// }

			// iterator begin( void ) {
			// 	return iterator(_root);
			// }

			// const_iterator begin( void ) const {
			// 	return const_iterator(&(*_root));
			// }

			// iterator end( void ) {
			// 	return iterator(&_data[_size]);
			// }

			// const_iterator end( void ) const {
			// 	return const_iterator(&_data[_size]);
			// }

		private:

	}; */
}
