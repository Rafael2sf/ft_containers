#pragma once

#include "iterators.hpp"

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

		private:
			pointer _pointer;

		public:
			~RbtIterator()
			{}

			RbtIterator( void )
			: _pointer(NULL)
			{}

			RbtIterator( pointer __p )
			: _pointer(__p)
			{}

			RbtIterator( RbtIterator const& __other )
			: _pointer(__other.base())
			{}

			template <class U>
			RbtIterator( RbtIterator<U> const& __other )
			: _pointer(__other.base())
			{}

			RbtIterator & operator=( RbtIterator const& __rhs ) {
				_pointer = __rhs._pointer;
				return *this;
			}

			pointer const & base( void ) const {
				return _pointer;
			}

			reference	operator*( void ) {
				return *_pointer;
			}

			pointer		operator->( void ) {
				return _pointer;
			}
	};
}
