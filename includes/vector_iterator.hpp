#pragma once

#include "iterators.hpp"
#include "type_traits.hpp"

namespace ft
{
	template<class T>
	class vector_iterator: public iterator_traits<T*>
	{
		public:

			typedef typename iterator_traits<T*>::value_type		value_type;
			typedef typename iterator_traits<T*>::reference			reference;
			typedef typename iterator_traits<T*>::pointer			pointer;
			typedef typename iterator_traits<T*>::difference_type	difference_type;

		private:
			pointer	_pointer;

		public:
			~vector_iterator() {}

			vector_iterator( void )
			: _pointer(NULL) {}

			vector_iterator( vector_iterator const& __other )
			: _pointer(__other.base()) {}

			template <typename U>
			vector_iterator( vector_iterator<U> const& __other,
				typename enable_if<is_same<value_type,
				typename remove_const<U>::type>::value>::type* = 0 )
			{
				_pointer = const_cast<pointer>(__other.base());
			}

			vector_iterator( pointer __p )
			: _pointer(__p) {}

			pointer base( void ) const {
				return _pointer;
			}

			vector_iterator &	operator=( vector_iterator const& __rhs ) {
				_pointer = __rhs._pointer;
				return (*this);
			}

			reference	operator*( void ) {
				return *_pointer;
			}

			pointer		operator->( void ) {
				return _pointer;
			}

			reference	operator[](const int n) {
				return *(_pointer + n);
			}

			bool		operator==( vector_iterator const& __rhs ) const { 
				return (_pointer == __rhs._pointer); 
			}

			bool		operator!=( vector_iterator const& __rhs ) const { 
				return (_pointer != __rhs._pointer); 
			}

			bool		operator<( vector_iterator const& __rhs ) const { 
				return (_pointer < __rhs._pointer); 
			}

			bool		operator>( vector_iterator const& __rhs ) const { 
				return (_pointer > __rhs._pointer); 
			}

			bool		operator<=( vector_iterator const& __rhs ) const { 
				return (_pointer <= __rhs._pointer); 
			}

			bool		operator>=( vector_iterator const& __rhs ) const { 
				return (_pointer >= __rhs._pointer); 
			}


			vector_iterator &	operator++( void ) {
				_pointer++;
				return (*this);
			}

			vector_iterator		operator++( int ) {
				vector_iterator	tmp(*this);
				_pointer++;
				return (tmp);
			}

			vector_iterator &	operator--( void ) {
				_pointer--;
				return (*this);
			}

			vector_iterator		operator--( int ) {
				vector_iterator	tmp(*this);
				_pointer--;
				return (tmp);
			}

			vector_iterator		operator+( difference_type __rhs ) const {
				vector_iterator	tmp(*this);
				tmp._pointer += __rhs;
				return (tmp);
			}

			vector_iterator &	operator+=( difference_type __rhs ) {
				_pointer += __rhs;
				return (*this);
			}

			vector_iterator		operator-( difference_type __rhs ) const {
				vector_iterator	tmp(*this);
				tmp._pointer -= __rhs;
				return (tmp);
			}

			vector_iterator &	operator-=( difference_type __rhs ) {
				_pointer -= __rhs;
				return (*this);
			}

			difference_type		operator-( vector_iterator const& __rhs ) {
				return (_pointer - __rhs._pointer);
			}
	};

	template<typename T>
	vector_iterator<T>	operator+(ptrdiff_t __lhs, vector_iterator<T> const& __rhs)
	{
		vector_iterator<T>	tmp(__rhs);
		tmp += __lhs;
		return (tmp);
	}
}
