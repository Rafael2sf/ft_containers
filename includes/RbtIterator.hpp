#pragma once

#include "iterators.hpp"
#include "vector.hpp"
#include <iostream>
#include <typeinfo>

namespace ft
{
	struct RbBaseNode;

	template <class T>
	struct RbNode : public RbBaseNode;

	template <class T>
	class RbtIterator: public iterator_traits<T*>
	{
		public:
			typedef std::bidirectional_iterator_tag					iterator_category;
			typedef typename iterator_traits<T*>::value_type		value_type;
			typedef typename iterator_traits<T*>::reference			reference;
			typedef typename iterator_traits<T*>::pointer			pointer;
			typedef typename iterator_traits<T*>::difference_type	difference_type;

		protected:

			typedef RbBaseNode										base_node;
			typedef RbBaseNode *									base_node_pointer;
			typedef RbNode<value_type>								node;
			typedef RbNode<value_type> *							node_pointer;

		public:

			base_node_pointer _M_node;

			~RbtIterator()
			{}

			RbtIterator( void )
			: _base(NULL), _M_node(NULL)
			{}

			RbtIterator( base_node_pointer __p )
			: _M_node(__p)
			{}

			RbtIterator( RbtIterator const& __other )
			: _base(__other._base), _M_node(__other._M_node)
			{}

			template <typename U>
			RbtIterator( RbtIterator<U> __other,
				typename enable_if<is_same<value_type,
				typename remove_const<U>::type>::value>::type* = 0 )
			: _base(__other.root_base()), _M_node(__other._M_node)
			{}

			base_node_pointer *
			root_base( void ) const
			{
				return _base;
			}

			pointer
			base( void ) const
			{
				return &_M_node->data;
			}

			RbtIterator & 
			operator=( RbtIterator const& __rhs )
			{
				_M_node = __rhs._M_node;
				_base = __rhs.root_base();
				return *this;
			}

			typename remove_pointer<pointer>::type &
			operator*( void )
			{
				return _M_node->data;
			}

			pointer
			operator->( void )
			{
				return &_M_node->data;
			}

			bool
			operator==( RbtIterator const& __rhs )
			{
				if (!_M_node && !__rhs._M_node)
					return (_base == __rhs._base) && _base != NULL;
				return _M_node == __rhs._M_node;
			}

			bool
			operator!=( RbtIterator const& __rhs )
			{
				return !(*this == __rhs);
			}

			RbtIterator	&
			operator++( void )
			{
				if (!_M_node)
				{
					_M_node = *_base;
					while (_M_node && _M_node->right)
						_M_node = _M_node->right;
					return *this;
				}
				if (_M_node->right)
				{
					_M_node = _M_node->right;
					while (_M_node->left)
						_M_node = _M_node->left;
				}
				else if (_M_node->parent && _M_node == _M_node->parent->left)
					_M_node = _M_node->parent;
				else
				{
					while (_M_node->parent && _M_node == _M_node->parent->right)
						_M_node = _M_node->parent;
					if (_M_node)
						_M_node = _M_node->parent;
				}
				return *this;
			}

			RbtIterator 
			operator++( int )
			{
				RbtIterator	it(*this);

				++(*this);
				return (it);
			}

			RbtIterator	&
			operator--( void )
			{
				if (!_M_node)
				{
					_M_node = *_base;
					while (_M_node && _M_node->right)
						_M_node = _M_node->right;
					return *this;
				}
				if (_M_node->left)
				{
					_M_node = _M_node->left;
					while (_M_node->right)
						_M_node = _M_node->right;
				}
				else if (_M_node->parent 
					&& _M_node == _M_node->parent->right)
					_M_node = _M_node->parent;
				else
				{
					while (_M_node->parent && _M_node == _M_node->parent->left)
						_M_node = _M_node->parent;
					if (_M_node)
						_M_node = _M_node->parent;
				}
				if (!_M_node)
				{
					_M_node = *_base;
					while (_M_node && _M_node->right)
						_M_node = _M_node->right;
				}
				return *this;
			}

			RbtIterator
			operator--( int )
			{
				RbtIterator	it(*this);

				--(*this);
				return (it);
			}
	};
}
