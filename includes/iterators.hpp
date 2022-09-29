#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include <cstddef>
#include "type_traits.hpp"

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
		typedef ptrdiff_t					difference_type;
		typedef T *								pointer;
		typedef T &								reference;
	};

	template<class T>
	struct iterator_traits<T const *>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t					difference_type;
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
				tmp += __rhs;
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
				tmp -= __rhs;
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
	bool
	operator==(
		reverse_iterator<Iter1> const& __lhs,
		reverse_iterator<Iter2> const& __rhs) { 
		return (__lhs.base() == __rhs.base()); 
	}

	template <class Iter1, class Iter2>
	bool
	operator!=(
		reverse_iterator<Iter1> const& __lhs,
		reverse_iterator<Iter2> const& __rhs) { 
		return (!(__lhs.base() == __rhs.base())); 
	}

	template <class Iter1, class Iter2>
	bool
	operator>(
		reverse_iterator<Iter1> const& __lhs,
		reverse_iterator<Iter2> const& __rhs) { 
		return (__lhs.base() < __rhs.base()); 
	}

	template <class Iter1, class Iter2>
	bool
	operator>=(
		reverse_iterator<Iter1> const& __lhs,
		reverse_iterator<Iter2> const& __rhs) { 
		return (__lhs.base() <= __rhs.base()); 
	}

	template <class Iter1, class Iter2>
	bool
	operator<(
		reverse_iterator<Iter1> const& __lhs,
		reverse_iterator<Iter2> const& __rhs) { 
		return (__lhs.base() > __rhs.base()); 
	}

	template <class Iter1, class Iter2>
	bool
	operator<=(
		reverse_iterator<Iter1> const& __lhs,
		reverse_iterator<Iter2> const& __rhs) { 
		return (__lhs.base() >= __rhs.base()); 
	}

	template <class Iter>
	reverse_iterator<Iter>
	operator+(
		typename reverse_iterator<Iter>::difference_type __n,
		reverse_iterator<Iter> const& __rhs )
	{
		reverse_iterator<Iter>	tmp(__rhs);
		tmp + __n;
		return (tmp); 
	}

	template <class Iter>
	reverse_iterator<Iter>
	operator-( reverse_iterator<Iter> const& __lhs,
			reverse_iterator<Iter> const& __rhs ) {
		return (__rhs.base() - __lhs.base()); 
	}

	template<typename T>
	reverse_iterator<T>
	operator+( ptrdiff_t __lhs,
			reverse_iterator<T> const& __rhs )
	{
		reverse_iterator<T>	tmp(__rhs);
		tmp += __lhs;
		return (tmp);
	}

	template<class T>
	class random_iterator: public ft::iterator_traits<T*>
	{
		public:

		typedef typename ft::iterator_traits<T*>::value_type		value_type;
		typedef typename ft::iterator_traits<T*>::reference			reference;
		typedef typename ft::iterator_traits<T*>::pointer			pointer;
		typedef typename ft::iterator_traits<T*>::difference_type	difference_type;

		private:
			
		pointer _pointer;

		public:

		~random_iterator() {}

		random_iterator( void )
		: _pointer(NULL) {}

		random_iterator( pointer __p )
		: _pointer(__p) {}

		random_iterator( random_iterator const& __other )
		: _pointer(__other.base()) {}

		template <typename U>
		random_iterator( ft::random_iterator<U> const& __other,
			typename ft::enable_if<
				ft::is_same<
					value_type, typename ft::remove_const<U>::type
				>::value && !ft::is_const<U>::value, U
			>::type* = 0 )
		:_pointer(__other.base())
		{}

		pointer
		base( void ) const {
			return _pointer;
		}

		random_iterator &
		operator=( random_iterator const& __rhs ) {
			_pointer = __rhs._pointer;
			return (*this);
		}

		typename remove_pointer<pointer>::type &
		operator*( void ) {
			return *_pointer;
		}

		pointer
		operator->( void ) {
			return _pointer;
		}

		reference
		operator[](const int n) {
			return *(_pointer + n);
		}

		random_iterator &
		operator++( void ) {
			_pointer++;
			return (*this);
		}

		random_iterator
		operator++( int ) {
			random_iterator	tmp(*this);
			_pointer++;
			return (tmp);
		}

		random_iterator &
		operator--( void ) {
			_pointer--;
			return (*this);
		}

		random_iterator
		operator--( int ) {
			random_iterator	tmp(*this);
			_pointer--;
			return (tmp);
		}

		random_iterator
		operator+( difference_type __rhs ) const {
			random_iterator	tmp(*this);
			tmp._pointer += __rhs;
			return (tmp);
		}

		random_iterator &
		operator+=( difference_type __rhs ) {
			_pointer += __rhs;
			return (*this);
		}

		random_iterator
		operator-( difference_type __rhs ) const {
			random_iterator	tmp(*this);
			tmp._pointer -= __rhs;
			return (tmp);
		}

		random_iterator &
		operator-=( difference_type __rhs ) {
			_pointer -= __rhs;
			return (*this);
		}

		difference_type
		operator-( random_iterator const& __rhs ) {
			return (_pointer - __rhs._pointer);
		}
	};

	template<typename T>
	random_iterator<T>	operator+(ptrdiff_t __lhs, random_iterator<T> const& __rhs)
	{
		random_iterator<T>	tmp(__rhs);
		tmp += __lhs;
		return (tmp);
	}

	template <class Iter1, class Iter2>
	bool
	operator==( random_iterator<Iter1> const& __lhs,
		random_iterator<Iter2> const& __rhs )
	{ 
		return (__lhs.base() == __rhs.base()); 
	}

	template <class Iter1, class Iter2>
	bool
	operator!=( random_iterator<Iter1> const& __lhs,
		random_iterator<Iter2> const& __rhs )
	{ 
		return !(__lhs == __rhs); 
	}

	template <class Iter1, class Iter2>
	bool
	operator<( random_iterator<Iter1> const& __lhs,
		random_iterator<Iter2> const& __rhs )
	{ 
		return (__lhs.base() < __rhs.base()); 
	}

	template <class Iter1, class Iter2>
	bool
	operator>( random_iterator<Iter1> const& __lhs,
		random_iterator<Iter2> const& __rhs )
	{ 
		return !(__lhs == __rhs) && !(__lhs < __rhs);
	}

	template <class Iter1, class Iter2>
	bool
	operator<=( random_iterator<Iter1> const& __lhs,
		random_iterator<Iter2> const& __rhs )
	{ 
		return !(__lhs > __rhs);
	}

	template <class Iter1, class Iter2>
	bool
	operator>=( random_iterator<Iter1> const& __lhs,
		random_iterator<Iter2> const& __rhs )
	{ 
		return !(__lhs < __rhs);
	}

	template <class Iter>
	bool
	operator==( random_iterator<Iter> const& __lhs,
		random_iterator<Iter> const& __rhs )
	{ 
		return (__lhs.base() == __rhs.base()); 
	}

	template <class Iter>
	bool
	operator!=( random_iterator<Iter> const& __lhs,
		random_iterator<Iter> const& __rhs )
	{ 
		return !(__lhs == __rhs); 
	}

	template <class Iter>
	bool
	operator<( random_iterator<Iter> const& __lhs,
		random_iterator<Iter> const& __rhs )
	{ 
		return (__lhs.base() < __rhs.base()); 
	}

	template <class Iter>
	bool
	operator>( random_iterator<Iter> const& __lhs,
		random_iterator<Iter> const& __rhs )
	{ 
		return !(__lhs == __rhs) && !(__lhs < __rhs);
	}

	template <class Iter>
	bool
	operator<=( random_iterator<Iter> const& __lhs,
		random_iterator<Iter> const& __rhs )
	{ 
		return !(__lhs > __rhs);
	}

	template <class Iter>
	bool
	operator>=( random_iterator<Iter> const& __lhs,
		random_iterator<Iter> const& __rhs )
	{ 
		return !(__lhs < __rhs);
	}
}

#endif
