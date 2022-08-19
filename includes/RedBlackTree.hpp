#pragma once

#include <functional>
#include <memory>
#include "utility.hpp"
#include "type_traits.hpp"
#include "RbtIterator.hpp"

namespace ft
{
	template <class T,
			class Compare = std::less<T>,
			class Alloc = std::allocator<T>
	> class RbtNode
	{
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef size_t										size_type;
			typedef ptrdiff_t									difference_type;

			RbtNode *left;
			RbtNode *right;
			RbtNode *parent;

		private:
			value_type	_data;
			bool		_is_black;

		public:
			~RbtNode() {}

			explicit RbtNode( value_type const& __val )
			: left(0), right(0), parent(0), _data(__val)
			{}

			RbtNode( RbtNode const& __other )
			{
				*this = __other;
			}

			RbtNode & operator=( RbtNode const& __other )
			{
				_data = __other._data;
				parent = __other.parent;
				left = __other.left;
				right = __other.right;
				return *this;
			}

			reference operator*( void ) {
				return _data;
			}

			pointer operator->( void ) {
				return &_data;
			}

		private:
			RbtNode( void )
			: left(0), right(0), parent(0)
			{}
	};

	template <class Key,
			class T,
			class Compare = std::less<Key>,
			class Alloc = std::allocator<pair<const Key,T> >
	> class RedBlackTree
	{
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef pair<const key_type, mapped_type>			value_type;
			typedef Compare										key_compare;
			typedef Compare										value_compare; /** TODO */
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef size_t										size_type;
			typedef RbtIterator<pointer>						iterator;
			typedef RbtIterator<const_pointer>					const_iterator;
			typedef typename iterator_traits
								<iterator>::difference_type		difference_type;

		private:
			RbtNode<value_type,
				key_compare,
				allocator_type>		*_root;
			std::allocator<RbtNode
				<value_type,
				key_compare,
				allocator_type> >	_allocator;
			size_type				_count;
			key_compare				_compare;

		public:
			~RedBlackTree() {}

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
					_allocator.construct(*_root, RbtNode<value_type, allocator_type>(__val));
					_count++;
				}
			}

			// iterator begin( void ) {
			// 	return iterator(&*_root);
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

	};
}
