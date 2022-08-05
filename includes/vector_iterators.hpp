#pragma once

#include "iterators.hpp"
#include <iostream>

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

			~vector_iterator() {}

			vector_iterator( void )
			: _p(NULL) {}

			vector_iterator( vector_iterator const & ref )
			: _p(ref._p) {}

			vector_iterator( pointer ref )
			: _p(ref) {}

			pointer const & base( void ) const {
				return (_p);
			}

			reference	operator*( void ) {
				return *_p;
			}

			pointer		operator->( void ) {
				return _p;
			}

			reference	operator[](const int n) {
				return (_p + n);
			}

			bool		operator==( vector_iterator const & rhs ) const { 
				return (_p == rhs._p); 
			}

			bool		operator!=( vector_iterator const & rhs ) const { 
				return (_p != rhs._p); 
			}

			bool		operator<( vector_iterator const & rhs ) const { 
				return (_p < rhs._p); 
			}

			bool		operator>( vector_iterator const & rhs ) const { 
				return (_p > rhs._p); 
			}

			bool		operator<=( vector_iterator const & rhs ) const { 
				return (_p <= rhs._p); 
			}

			bool		operator>=( vector_iterator const & rhs ) const { 
				return (_p >= rhs._p); 
			}

			vector_iterator &	operator=( vector_iterator const & rhs ) {
				_p = rhs._p;
				return (*this);
			}

			vector_iterator &	operator++( void ) {
				_p++;
				return (*this);
			}

			vector_iterator		operator++( int ) {
				vector_iterator	tmp(*this);
				_p++;
				return (tmp);
			}

			vector_iterator &	operator--( void ) {
				_p--;
				return (*this);
			}

			vector_iterator		operator--( int ) {
				vector_iterator	tmp(*this);
				_p--;
				return (tmp);
			}

			vector_iterator		operator+( difference_type rhs ) {
				vector_iterator	tmp(*this);
				tmp._p += rhs;
				return (tmp);
			}

			vector_iterator &	operator+=( difference_type rhs ) {
				_p += rhs;
				return (*this);
			}

			vector_iterator		operator-( difference_type rhs ) {
				vector_iterator	tmp(*this);
				tmp._p -= rhs;
				return (tmp);
			}

			vector_iterator &	operator-=( difference_type rhs ) {
				_p -= rhs;
				return (*this);
			}

			difference_type		operator-( vector_iterator const & rhs ) {
				return (_p - rhs._p);
			}

		private:
			pointer	_p;
	};

	template<typename T>
	vector_iterator<T>	operator+(ptrdiff_t lhs, vector_iterator<T> const & rhs)
	{
		vector_iterator<T>	tmp(rhs);

		tmp += lhs;
		return (tmp);
	}
}
