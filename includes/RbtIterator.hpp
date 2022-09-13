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
	class RbIterator: public iterator_traits<T*>
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

			base_node_pointer _N_;

			~RbIterator()
			{}

			RbIterator( void )
			: _base(NULL), _N_(NULL)
			{}

			RbIterator( base_node_pointer __p )
			: _N_(__p)
			{}

			RbIterator( RbIterator const& __other )
			: _base(__other._base), _N_(__other._N_)
			{}

			template <typename U>
			RbIterator( RbIterator<U> __other,
				typename enable_if<is_same<value_type,
				typename remove_const<U>::type>::value>::type* = 0 )
			: _base(__other.root_base()), _N_(__other._N_)
			{}

			base_node_pointer *
			root_base( void ) const
			{
				return _base;
			}

			pointer
			base( void ) const
			{
				return &_N_->data;
			}

			RbIterator & 
			operator=( RbIterator const& __rhs )
			{
				_N_ = __rhs._N_;
				_base = __rhs.root_base();
				return *this;
			}

			typename remove_pointer<pointer>::type &
			operator*( void )
			{
				return _N_->data;
			}

			pointer
			operator->( void )
			{
				return &_N_->data;
			}

			bool
			operator==( RbIterator const& __rhs )
			{
				if (!_N_ && !__rhs._N_)
					return (_base == __rhs._base) && _base != NULL;
				return _N_ == __rhs._N_;
			}

			bool
			operator!=( RbIterator const& __rhs )
			{
				return !(*this == __rhs);
			}

			RbIterator	&
			operator++( void )
			{
				if (!_N_)
				{
					_N_ = *_base;
					while (_N_ && _N_->right)
						_N_ = _N_->right;
					return *this;
				}
				if (_N_->right)
				{
					_N_ = _N_->right;
					while (_N_->left)
						_N_ = _N_->left;
				}
				else if (_N_->parent && _N_ == _N_->parent->left)
					_N_ = _N_->parent;
				else
				{
					while (_N_->parent && _N_ == _N_->parent->right)
						_N_ = _N_->parent;
					if (_N_)
						_N_ = _N_->parent;
				}
				return *this;
			}

			RbIterator 
			operator++( int )
			{
				RbIterator	it(*this);

				++(*this);
				return (it);
			}

			RbIterator	&
			operator--( void )
			{
				if (!_N_)
				{
					_N_ = *_base;
					while (_N_ && _N_->right)
						_N_ = _N_->right;
					return *this;
				}
				if (_N_->left)
				{
					_N_ = _N_->left;
					while (_N_->right)
						_N_ = _N_->right;
				}
				else if (_N_->parent 
					&& _N_ == _N_->parent->right)
					_N_ = _N_->parent;
				else
				{
					while (_N_->parent && _N_ == _N_->parent->left)
						_N_ = _N_->parent;
					if (_N_)
						_N_ = _N_->parent;
				}
				if (!_N_)
				{
					_N_ = *_base;
					while (_N_ && _N_->right)
						_N_ = _N_->right;
				}
				return *this;
			}

			RbIterator
			operator--( int )
			{
				RbIterator	it(*this);

				--(*this);
				return (it);
			}
	};
}
