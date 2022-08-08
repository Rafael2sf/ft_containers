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
			: _pointer(NULL) {}

			vector_iterator( vector_iterator const & ref )
			: _pointer(ref._pointer) {}

			vector_iterator( pointer ref )
			: _pointer(ref) {}

			pointer const & base( void ) const {
				return _pointer;
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

			bool		operator==( vector_iterator const & rhs ) const { 
				return (_pointer == rhs._pointer); 
			}

			bool		operator!=( vector_iterator const & rhs ) const { 
				return (_pointer != rhs._pointer); 
			}

			bool		operator<( vector_iterator const & rhs ) const { 
				return (_pointer < rhs._pointer); 
			}

			bool		operator>( vector_iterator const & rhs ) const { 
				return (_pointer > rhs._pointer); 
			}

			bool		operator<=( vector_iterator const & rhs ) const { 
				return (_pointer <= rhs._pointer); 
			}

			bool		operator>=( vector_iterator const & rhs ) const { 
				return (_pointer >= rhs._pointer); 
			}

			vector_iterator &	operator=( vector_iterator const & rhs ) {
				_pointer = rhs._pointer;
				return (*this);
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

			vector_iterator		operator+( difference_type rhs ) const {
				vector_iterator	tmp(*this);
				tmp._pointer += rhs;
				return (tmp);
			}

			vector_iterator &	operator+=( difference_type rhs ) {
				_pointer += rhs;
				return (*this);
			}

			vector_iterator		operator-( difference_type rhs ) const {
				vector_iterator	tmp(*this);
				tmp._pointer -= rhs;
				return (tmp);
			}

			vector_iterator &	operator-=( difference_type rhs ) {
				_pointer -= rhs;
				return (*this);
			}

			difference_type		operator-( vector_iterator const & rhs ) {
				return (_pointer - rhs._pointer);
			}

		private:
			pointer	_pointer;
	};

	template<typename T>
	vector_iterator<T>	operator+(ptrdiff_t lhs, vector_iterator<T> const & rhs)
	{
		vector_iterator<T>	tmp(rhs);
		tmp += lhs;
		return (tmp);
	}

	/* Const iterator */

	template<class T>
	class vector_const_iterator: public iterator_traits<T*>
	{
		public:

			typedef typename iterator_traits<T*>::value_type		value_type;
			typedef typename iterator_traits<T*>::reference			reference;
			typedef typename iterator_traits<T*>::pointer			pointer;
			typedef typename iterator_traits<T*>::difference_type	difference_type;

			~vector_const_iterator() {}

			vector_const_iterator( void )
			: _pointer(NULL) {}

			vector_const_iterator( vector_const_iterator const & ref )
			: _pointer(ref._pointer) {}

			vector_const_iterator( pointer ref )
			: _pointer(ref) {}

			pointer const & base( void ) const {
				return _pointer;
			}

			reference const	operator*( void ) const {
				return *_pointer;
			}

			const pointer operator->( void ) const {
				return _pointer;
			}

			reference const	operator[](const int n) const {
				return *(_pointer + n);
			}

			bool		operator==( vector_const_iterator const & rhs ) const { 
				return (_pointer == rhs._pointer); 
			}

			bool		operator!=( vector_const_iterator const & rhs ) const { 
				return (_pointer != rhs._pointer); 
			}

			bool		operator<( vector_const_iterator const & rhs ) const { 
				return (_pointer < rhs._pointer); 
			}

			bool		operator>( vector_const_iterator const & rhs ) const { 
				return (_pointer > rhs._pointer); 
			}

			bool		operator<=( vector_const_iterator const & rhs ) const { 
				return (_pointer <= rhs._pointer); 
			}

			bool		operator>=( vector_const_iterator const & rhs ) const { 
				return (_pointer >= rhs._pointer); 
			}

			vector_const_iterator &	operator=( vector_const_iterator const & rhs ) {
				_pointer = rhs._pointer;
				return (*this);
			}

			vector_const_iterator &	operator++( void ) {
				_pointer++;
				return (*this);
			}

			vector_const_iterator	operator++( int ) {
				vector_const_iterator	tmp(*this);
				_pointer++;
				return (tmp);
			}

			vector_const_iterator &	operator--( void ) {
				_pointer--;
				return (*this);
			}

			vector_const_iterator	operator--( int ) {
				vector_const_iterator	tmp(*this);
				_pointer--;
				return (tmp);
			}

			vector_const_iterator	operator+( difference_type rhs ) const {
				vector_const_iterator	tmp(*this);
				tmp._pointer += rhs;
				return (tmp);
			}

			vector_const_iterator &	operator+=( difference_type rhs ) {
				_pointer += rhs;
				return (*this);
			}

			vector_const_iterator	operator-( difference_type rhs ) const {
				vector_const_iterator	tmp(*this);
				tmp._pointer -= rhs;
				return (tmp);
			}

			vector_const_iterator &	operator-=( difference_type rhs ) {
				_pointer -= rhs;
				return (*this);
			}

			difference_type			operator-( vector_const_iterator const & rhs ) {
				return (_pointer - rhs._pointer);
			}

		private:
			pointer	_pointer;
	};

	template<typename T>
	vector_const_iterator<T>	operator+(ptrdiff_t lhs, vector_const_iterator<T> const & rhs)
	{
		vector_const_iterator<T>	tmp(rhs);
		tmp += lhs;
		return (tmp);
	}
}
