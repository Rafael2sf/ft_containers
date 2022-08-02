#pragma once

#include "iterators.hpp"

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
			vector_iterator( void ): _p(NULL) {}
			vector_iterator( vector_iterator const & ref ) { *this = ref; }
			vector_iterator( pointer const & ref ): _p(ref) {}

			reference	operator*( void ) { return (*(this->_p)); }
			pointer		operator->( void ) { return (this->_p); }
			reference	operator[](const int n) { return (this->_p + n); }

			bool		operator==( vector_iterator const & rhs ) const { return (this->_p == rhs._p); }
			bool		operator!=( vector_iterator const & rhs ) const { return (this->_p != rhs._p); }
			bool		operator<( vector_iterator const & rhs ) const { return (this->_p < rhs._p); }
			bool		operator>( vector_iterator const & rhs ) const { return (this->_p > rhs._p); }
			bool		operator<=( vector_iterator const & rhs ) const { return (this->_p <= rhs._p); }
			bool		operator>=( vector_iterator const & rhs ) const { return (this->_p >= rhs._p); }

			vector_iterator &	operator=( vector_iterator const & rhs ) { 
				this->_p = rhs._p;
				return (*this);
			}
			vector_iterator &	operator++( void ) {
				this->_p++;
				return (*this);
			}
			vector_iterator		operator++( int ) {
				vector_iterator	tmp(*this);
				this->_p++;
				return (tmp);
			}
			vector_iterator &	operator--( void ) {
				this->_p--;
				return (*this);
			}
			vector_iterator		operator--( int ) {
				vector_iterator	tmp(*this);
				this->_p--;
				return (tmp);
			}
			vector_iterator		operator+( int rhs ) {
				vector_iterator	tmp(*this);
				tmp._p += rhs;
				return (tmp);
			}
			vector_iterator &	operator+=( int rhs ) {
				this->_p += rhs;
				return (*this);
			}
			vector_iterator		operator-( int rhs ) {
				vector_iterator	tmp(*this);
				tmp._p -= rhs;
				return (tmp);
			}
			vector_iterator &	operator-=( int rhs ) {
				this->_p -= rhs;
				return (*this);
			}
			difference_type		operator-( vector_iterator const & rhs ) { return (this->_p - rhs._p); }

		private:
			pointer	_p;
	};

	// template<typename T>
	// vector_iterator<T>	operator+(int lhs, vector_iterator<T> rhs)
	// {
	// 	friend vector_iterator<T>	tmp(rhs);
	// 	rhs._p += lhs;
	// 	return (tmp);
	// }

	/* template<class T>
	class vector_const_iterator
	{
		public:

			typedef std::random_access_iterator_tag iterator_category;
			typedef T								value_type;
			typedef ptrdiff_t						difference_type;
			typedef T *								pointer;
			typedef T &								reference;

			~vector_iterator() {}
			vector_iterator( void ): _p(NULL) {}
			vector_iterator( vector_iterator const & ref ) { *this = ref; }
			vector_iterator( pointer const & ref ): _p(ref) {}

			reference	operator*( void ) { return (*(this->_p)); }
			pointer		operator->( void ) { return (this->_p); }
			reference	operator[](const int n) { return (this->_p + n); }

			bool		operator==( vector_iterator const & rhs ) const { return (this->_p == rhs._p); }
			bool		operator!=( vector_iterator const & rhs ) const { return (this->_p != rhs._p); }
			bool		operator<( vector_iterator const & rhs ) const { return (this->_p < rhs._p); }
			bool		operator>( vector_iterator const & rhs ) const { return (this->_p > rhs._p); }
			bool		operator<=( vector_iterator const & rhs ) const { return (this->_p <= rhs._p); }
			bool		operator>=( vector_iterator const & rhs ) const { return (this->_p >= rhs._p); }

			vector_iterator &	operator=( vector_iterator const & rhs ) { 
				this->_p = rhs._p;
				return (*this);
			}
			vector_iterator &	operator++( void ) {
				this->_p++;
				return (*this);
			}
			vector_iterator		operator++( int ) {
				vector_iterator	tmp(*this);
				this->_p++;
				return (tmp);
			}
			vector_iterator &	operator--( void ) {
				this->_p--;
				return (*this);
			}
			vector_iterator		operator--( int ) {
				vector_iterator	tmp(*this);
				this->_p--;
				return (tmp);
			}
			vector_iterator		operator+( difference_type rhs ) {
				vector_iterator	tmp(rhs);
				tmp._p += rhs;
				return (tmp);
			}
			vector_iterator &	operator+=( difference_type rhs ) {
				this->_p += rhs;
				return (*this);
			}
			vector_iterator		operator-( difference_type rhs ) {
				vector_iterator	tmp(rhs);
				tmp._p -= rhs;
				return (tmp);
			}
			vector_iterator &	operator-=( difference_type rhs ) {
				this->_p -= rhs;
				return (*this);
			}

		private:
			pointer	_p;
	}; */
}
