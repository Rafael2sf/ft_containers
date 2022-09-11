#pragma once

#include "iterators.hpp"
#include "vector.hpp"
#include <iostream>
#include <typeinfo>

namespace ft
{
	template <class T>
	struct RbtNode;

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

			typedef RbtNode<value_type>				node;
			typedef RbtNode<value_type> const		const_node;
			typedef RbtNode<value_type> *			node_pointer;
			typedef RbtNode<value_type> const *		const_node_pointer;

			node_pointer *_base;

		public:

			node_pointer _M_node;

			~RbtIterator()
			{}

			RbtIterator( void )
			: _base(NULL), _M_node(NULL)
			{}

			RbtIterator( node_pointer *__root, node_pointer __p = 0)
			: _base(__root), _M_node(__p)
			{}

			RbtIterator( RbtIterator const& __other )
			: _base(__other._base), _M_node(__other._M_node)
			{}

			template <typename U>
			RbtIterator( RbtIterator<U> __other,
				typename enable_if<is_same<value_type,
				typename remove_const<U>::type>::value>::type* = 0 )
			: _base(__other.base()), _M_node(__other._M_node)
			{}

			node_pointer *
			base( void ) const
			{
				return _base;
			}

			RbtIterator & 
			operator=( RbtIterator const& __rhs )
			{
				_M_node = __rhs._M_node;
				_base = __rhs.base();
				return *this;
			}

			typename remove_pointer<pointer>::type &
			operator*( void )
			{
				return _M_node->data;
			}

			void
			typeTest( void )
			{
				std::cout << (is_same<ft::pair<int,int>, value_type>::value ? "true" : "false") << std::endl;
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
