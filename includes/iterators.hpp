#pragma once

#include <iterator>
#include <cstddef>
#include <iostream>

namespace ft
{
	template<class T>
	struct iterator_traits
	{
		typedef typename T::iterator_category	iterator_category;
		typedef typename T::value_type			value_type;
		typedef typename T::difference_type		difference_type;
		typedef typename T::pointer				pointer;
		typedef typename T::reference			reference;
	};

	template<class T>
	struct iterator_traits<T *>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T *								pointer;
		typedef T &								reference;
	};

	template<class T>
	struct iterator_traits<T const *>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T const *						pointer;
		typedef T const&						reference;
	};

	template <class Iter>
	class reverse_iterator
	{
		public:

			typedef Iter												iterator_type;
			typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iter>::value_type			value_type;
			typedef typename iterator_traits<Iter>::difference_type		difference_type;
			typedef typename iterator_traits<Iter>::pointer				pointer;
			typedef typename iterator_traits<Iter>::reference			reference;

			~reverse_iterator() {}

			reverse_iterator( void )
			: _current(NULL) {}

			explicit reverse_iterator( iterator_type __iter )
			: _current(__iter) {}

			reverse_iterator( reverse_iterator const& __other ) {
				*this = __other;
			}

			template <class U>
			reverse_iterator( reverse_iterator<U> const& __other )
			: _current(__other.base())
			{}

			iterator_type
			base() const {
				return (_current);
			}

			reference
			operator*( void ) {
				iterator_type tmp(_current);
				return *(--tmp);
			}

			pointer
			operator->( void ) {
				iterator_type tmp(_current);
				return (&*(--tmp));
			}

			reference
			operator[](const int n) {
				return (_current[n - 1]);
			}

			reverse_iterator &
			operator=( reverse_iterator const& __rhs ) {
				_current = __rhs.base();
				return (*this);
			}

			reverse_iterator &
			operator++( void ) {
				_current--;
				return (*this);
			}

			reverse_iterator
			operator++( int ) {
				reverse_iterator tmp(*this);
				_current--;
				return (tmp);
			}

			reverse_iterator &
			operator--( void ) {
				_current++;
				return (*this);
			}

			reverse_iterator
			operator--( int ) {
				reverse_iterator tmp(*this);
				_current++;
				return (tmp);
			}

			reverse_iterator
			operator+( difference_type __rhs ) const {
				reverse_iterator tmp(*this);
				tmp -= __rhs;
				return (tmp);
			}

			reverse_iterator &
			operator+=( difference_type __rhs ) {
				_current -= __rhs;
				return (*this);
			}

			reverse_iterator
			operator-( difference_type __rhs ) const {
				reverse_iterator tmp(*this);
				tmp += __rhs;
				return (tmp);
			}

			reverse_iterator &
			operator-=( difference_type __rhs ) {
				_current += __rhs;
				return (*this);
			}

		protected:

			Iter _current;
	};

	template <class Iter1, class Iter2>
	bool		operator==(
		reverse_iterator<Iter1> const& __lhs,
		reverse_iterator<Iter2> const& __rhs) { 
		return (__lhs.base() == __rhs.base()); 
	}

	template <class Iter1, class Iter2>
	bool		operator!=(
		reverse_iterator<Iter1> const& __lhs,
		reverse_iterator<Iter2> const& __rhs) { 
		return (!(__lhs.base() == __rhs.base())); 
	}

	template <class Iter1, class Iter2>
	bool		operator>(
		reverse_iterator<Iter1> const& __lhs,
		reverse_iterator<Iter2> const& __rhs) { 
		return (__lhs.base() < __rhs.base()); 
	}

	template <class Iter1, class Iter2>
	bool		operator>=(
		reverse_iterator<Iter1> const& __lhs,
		reverse_iterator<Iter2> const& __rhs) { 
		return (__lhs.base() <= __rhs.base()); 
	}

	template <class Iter1, class Iter2>
	bool		operator<(
		reverse_iterator<Iter1> const& __lhs,
		reverse_iterator<Iter2> const& __rhs) { 
		return (__lhs.base() > __rhs.base()); 
	}

	template <class Iter1, class Iter2>
	bool		operator<=(
		reverse_iterator<Iter1> const& __lhs,
		reverse_iterator<Iter2> const& __rhs) { 
		return (__lhs.base() >= __rhs.base()); 
	}

	template <class Iter>
	reverse_iterator<Iter>	operator+(
		typename reverse_iterator<Iter>::difference_type __n,
		reverse_iterator<Iter> const& __rhs)
	{
		reverse_iterator<Iter>	tmp;
		tmp + __n;
		return (tmp); 
	}

	template <class Iter>
	reverse_iterator<Iter>	operator-(
		reverse_iterator<Iter> const& __lhs,
		reverse_iterator<Iter> const& __rhs) {
		return (__rhs.base() - __lhs.base()); 
	}

	template<typename T>
	reverse_iterator<T>	operator+(ptrdiff_t __lhs, reverse_iterator<T> const& __rhs)
	{
		reverse_iterator<T>	tmp(__rhs);
		tmp += __lhs;
		return (tmp);
	}
}
