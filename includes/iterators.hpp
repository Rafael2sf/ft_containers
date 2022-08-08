#pragma once

#include <iterator>
#include <cstddef>

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
		typedef T const &						reference;
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

			explicit reverse_iterator( iterator_type ref )
			: _current(ref) {}

			template <class U>
			reverse_iterator( reverse_iterator<U> const & other ) {
				*this = other;
			}

			iterator_type base() const {
				return (_current.base());
			}

			reference	operator*( void ) {
				return *(_current - 1);
			}

			pointer		operator->( void ) {
				return (_current.base() - 1);
			}

			reference	operator[](const int n) {
				return (_current[n - 1]);
			}

			reverse_iterator &	operator=( reverse_iterator const & rhs ) {
				_current = rhs.base();
				return (*this);
			}

			reverse_iterator &	operator++( void ) {
				_current--;
				return (*this);
			}

			reverse_iterator	operator++( int ) {
				reverse_iterator	tmp(*this);
				_current--;
				return (tmp);
			}

			reverse_iterator &	operator--( void ) {
				_current++;
				return (*this);
			}

			reverse_iterator	operator--( int ) {
				reverse_iterator	tmp(*this);
				_current++;
				return (tmp);
			}

			reverse_iterator	operator+( difference_type rhs ) const {
				reverse_iterator	tmp(*this);
				tmp -= rhs;
				return (tmp);
			}

			reverse_iterator &	operator+=( difference_type rhs ) {
				_current -= rhs;
				return (*this);
			}

			reverse_iterator	operator-( difference_type rhs ) const {
				reverse_iterator	tmp(*this);
				tmp += rhs;
				return (tmp);
			}

			reverse_iterator &	operator-=( difference_type rhs ) {
				_current += rhs;
				return (*this);
			}

		protected:

			Iter _current;
	};

	template <class Iter1, class Iter2>
	bool		operator==(
		std::reverse_iterator<Iter1> const & lhs,
		std::reverse_iterator<Iter2> const & rhs) { 
		return (lhs.base() == rhs.base()); 
	}

	template <class Iter1, class Iter2>
	bool		operator!=(
		std::reverse_iterator<Iter1> const & lhs,
		std::reverse_iterator<Iter2> const & rhs) { 
		return (lhs.base() != rhs.base()); 
	}

	template <class Iter1, class Iter2>
	bool		operator>(
		std::reverse_iterator<Iter1> const & lhs,
		std::reverse_iterator<Iter2> const & rhs) { 
		return (lhs.base() > rhs.base()); 
	}

	template <class Iter1, class Iter2>
	bool		operator>=(
		std::reverse_iterator<Iter1> const & lhs,
		std::reverse_iterator<Iter2> const & rhs) { 
		return (lhs.base() >= rhs.base()); 
	}

	template <class Iter1, class Iter2>
	bool		operator<(
		std::reverse_iterator<Iter1> const & lhs,
		std::reverse_iterator<Iter2> const & rhs) { 
		return (lhs.base() < rhs.base()); 
	}

	template <class Iter1, class Iter2>
	bool		operator<=(
		std::reverse_iterator<Iter1> const & lhs,
		std::reverse_iterator<Iter2> const & rhs) { 
		return (lhs.base() <= rhs.base()); 
	}

	template <class Iter>
	reverse_iterator<Iter>	operator+(
		typename std::reverse_iterator<Iter>::difference_type n,
		std::reverse_iterator<Iter> const & rhs)
	{
		reverse_iterator<Iter>	tmp;
		tmp + n;
		return (tmp); 
	}

	template <class Iter>
	reverse_iterator<Iter>	operator-(
		std::reverse_iterator<Iter> const & lhs,
		std::reverse_iterator<Iter> const & rhs) {
		return (rhs.base() - lhs.base()); 
	}

	template<typename T>
	reverse_iterator<T>	operator+(ptrdiff_t lhs, reverse_iterator<T> const & rhs)
	{
		reverse_iterator<T>	tmp(rhs);
		tmp += lhs;
		return (tmp);
	}
}
