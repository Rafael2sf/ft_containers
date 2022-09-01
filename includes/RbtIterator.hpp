#pragma once

#include "iterators.hpp"
#include "vector.hpp"
#include <iostream>

namespace ft
{
	template <class T>
	class RbtIterator : iterator_traits<T>
	{
		public:
			typedef std::bidirectional_iterator_tag 				iterator_category;
			typedef typename iterator_traits<T>::value_type			value_type;
			typedef typename iterator_traits<T>::reference			reference;
			typedef typename iterator_traits<T>::pointer			pointer;
			typedef typename iterator_traits<T>::difference_type	difference_type;

		protected:

			pointer 			_pos;

		public:

			pointer 			_n_base;

			~RbtIterator()
			{}

			RbtIterator( void )
			: _pos(NULL), _n_base(NULL)
			{}

			RbtIterator( pointer __p )
			: _pos(__p), _n_base(_n_find_root(__p))
			{}

			RbtIterator( RbtIterator const& __other )
			: _pos(__other.base()), _n_base(_n_find_root(__other.base()))
			{}

			template <class U>
			RbtIterator( RbtIterator<U> const& __other )
			: _pos(__other.base()), _n_base(_n_find_root(__other.base()))
			{}

			RbtIterator & operator=( RbtIterator const& __rhs ) {
				_pos = __rhs._pos;
				_n_base = __rhs._n_base;
				return *this;
			}

			pointer const & base( void ) const {
				return _pos;
			}

			reference	operator*( void ) {
				return *_pos;
			}

			pointer		operator->( void ) {
				return _pos;
			}

			bool
			operator==( RbtIterator const& __rhs )
			{
				return _pos == __rhs._pos;
			}

			bool
			operator!=( RbtIterator const& __rhs )
			{
				return !(*this == __rhs);
			}

			RbtIterator	& operator++( void )
			{
				if (!_pos)
					std::cout << "abc" << '\n';
				if (_pos->right)
				{
					_pos = _pos->right;
					while (_pos->left)
						_pos = _pos->left;
				}
				else if (_pos->parent && _pos == _pos->parent->left)
				{
					_pos = _pos->parent;

				}
				else
				{
					while (_pos->parent && _pos == _pos->parent->right)
						_pos = _pos->parent;
					if (_pos)
						_pos = _pos->parent;
				}
				if (!_pos)
					std::cout << "last elem";
				return *this;
			}

		private:

			pointer
			_n_find_root( pointer __n )
			{
				while (__n->parent)
					__n = __n->parent;
				return __n;
			}
	};
}
