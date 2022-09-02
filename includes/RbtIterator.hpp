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
	class RbtIterator
	{
		public:
			typedef std::bidirectional_iterator_tag iterator_category;
			// typedef T								value_type;
			// typedef T*								reference;
			// typedef T&								pointer;
			// typedef ptrdiff_t						difference_type;
			typedef typename iterator_traits<T>::value_type			value_type;
			typedef typename iterator_traits<T>::reference			reference;
			typedef typename iterator_traits<T>::pointer			pointer;
			typedef typename iterator_traits<T>::difference_type	difference_type;

		protected:

			typedef RbtNode<value_type>				node;
			typedef RbtNode<value_type> const		const_node;
			typedef RbtNode<value_type> *			node_pointer;
			typedef RbtNode<value_type> const *		const_node_pointer;

			node_pointer _pos;

		public:

			node_pointer _Node_Root;

			~RbtIterator()
			{}

			RbtIterator( void )
			: _pos(NULL)
			{}

			RbtIterator( node_pointer __root, node_pointer __p = 0)
			: _pos(__p), _Node_Root(__root)
			{}

			RbtIterator( RbtIterator const& __other )
			: _pos(__other._pos), _Node_Root(__other._Node_Root)
			{}

			template <typename U>
			RbtIterator( RbtIterator<U> const& __other )
			: _pos(__other.base()), _Node_Root(__other._Node_Root)
			{}

			RbtIterator & 
			operator=( RbtIterator const& __rhs )
			{
				_pos = __rhs._pos;
				_Node_Root = __rhs._Node_Root;
				return *this;
			}

			value_type
			operator*( void )
			{
				return (*_pos).data;
			}

			pointer
			operator->( void )
			{
				return _pos->data;
			}

			bool
			operator==( RbtIterator const& __rhs )
			{
				if (!_pos && !__rhs._pos)
					return (_Node_Root == __rhs._Node_Root) && _Node_Root != NULL;
				return _pos == __rhs._pos;
			}

			bool
			operator!=( RbtIterator const& __rhs )
			{
				return !(*this == __rhs);
			}

			RbtIterator	&
			operator++( void )
			{
				if (!_pos)
				{
					_pos = _Node_Root;
					while (_pos && _pos->right)
						_pos = _pos->right;
					return *this;
				}
				if (_pos->right)
				{
					_pos = _pos->right;
					while (_pos->left)
						_pos = _pos->left;
				}
				else if (_pos->parent && _pos == _pos->parent->left)
					_pos = _pos->parent;
				else
				{
					while (_pos->parent && _pos == _pos->parent->right)
						_pos = _pos->parent;
					if (_pos)
						_pos = _pos->parent;
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
				if (!_pos)
				{
					_pos = _Node_Root;
					while (_pos && _pos->right)
						_pos = _pos->right;
					return *this;
				}
				if (_pos->left)
				{
					_pos = _pos->left;
					while (_pos->right)
						_pos = _pos->right;
				}
				else if (_pos->parent 
					&& _pos == _pos->parent->right)
					_pos = _pos->parent;
				else
				{
					while (_pos->parent && _pos == _pos->parent->left)
						_pos = _pos->parent;
					if (_pos)
						_pos = _pos->parent;
				}
				if (!_pos)
				{
					_pos = _Node_Root;
					while (_pos && _pos->right)
						_pos = _pos->right;
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

			node_pointer
			base( void ) const
			{
				return _pos;
			}

		private:

			node_pointer
			_n_find_root( node_pointer __n )
			{
				if (!__n)
					return NULL;
				while (__n->parent)
					__n = __n->parent;
				return __n;
			}

			node_pointer
			_n_max( node_pointer __n )
			{
				if (!__n)
					return NULL;
				while (__n->parent)
					__n = __n->parent;
				return __n;
			}
	};
}
