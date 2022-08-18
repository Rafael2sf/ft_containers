#pragma once

#include <functional>
#include <memory>
#include "utility.hpp"
#include "type_traits.hpp"

namespace ft
{
	template <class Key,
			class T,
			class Compare = std::less<Key>,
			class Alloc = std::allocator< pair<Key const, T> >
	> class RbtNode
	{
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef pair<Key const, T>							value_type;
			typedef Compare										key_compare;
			typedef Compare										value_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef size_t										size_type;

		protected:
			RbtNode *_left;
			RbtNode *_right;
			RbtNode *_prev;

		private:
			value_type	_data;

		public:
			~RbtNode() {}

			RbtNode( void )
			: _left(0), _right(0), _prev(0), _data(key_type(), mapped_type())
			{}

			explicit RbtNode( key_type const& __key, mapped_type const& __value)
			: _left(0), _right(0), _prev(0), _data(__key, __value)
			{}

			RbtNode( RbtNode const& __other )
			{
				*this = __other;
			}

			RbtNode & operator=( RbtNode const& __other )
			{
				_data = __other._value;
				_prev = __other._prev;
				_left = __other._left;
				_right = __other._right;
			}

			value_type	const&	getPair( void ) const {
				return _data;
			}
			void		setPair( value_type const& __pair ) {
				_data(__pair);
			}
	
			key_type	const&	getKey( void ) const {
				return _data.first;
			}

			void		setKey( key_type const& __key ) {
				_data.first = __key;
			}

			mapped_type const&	getValue( void ) const {
				return _data.second;
			}

			void		setValue( mapped_type const& __value ) {
				_data.second = __value;
			}
	};

	template <class Key,
			class T,
			class Compare = std::less<Key>,
			class Alloc = std::allocator< pair< const Key, T> >
	> class RedBlackTree
	{
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef pair<key_type const, mapped_type>			value_type;
			typedef Compare										key_compare;
			typedef Compare										value_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef size_t										size_type;
			// value_compare
			//iterator + difference_type

		private:
			RbtNode<key_type,
				mapped_type, 
				key_compare,
				allocator_type>	*_root;
			size_type			_count;

		public:
			~RedBlackTree();

			RedBlackTree( key_compare const& __comp = key_compare(), 
				allocator_type const& __alloc = allocator_type() );

			template <class InputIterator>
			RedBlackTree( InputIterator __first, InputIterator __last );

			RedBlackTree( RedBlackTree const& __other );

		private:

	};
}
