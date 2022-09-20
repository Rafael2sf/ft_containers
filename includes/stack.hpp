#ifndef STACK_HPP
#define STACK_HPP

#include "../includes/vector.hpp"

namespace ft
{
	template< class T, class Container = ft::vector<T> >
	class stack
	{
		public:
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

		protected:
		Container	c;

		public:
		~stack() {}

		explicit stack( Container const& __cont = Container() )
		: c(__cont)
		{}

		stack( stack const& __other )
		: c(__other.c)
		{}

		stack &
		operator=( stack const& __other )
		{
			c = __other.c;
			return *this;
		}

		reference
		top( void )
		{
			return c.back();
		}

		const_reference
		top( void ) const
		{
			return c.back();
		}

		bool
		empty( void ) const
		{
			return c.empty();
		}

		size_type
		size( void ) const
		{
			return c.size();
		}

		void
		push( value_type const& __value )
		{
			c.push_back(__value);
		}

		void
		pop( void )
		{
			c.pop_back();
		}

		template< class U, class Cont >
		friend bool
		operator==(
			ft::stack<U,Cont> const& __lhs,
			ft::stack<U,Cont> const& __rhs );

		template< class U, class Cont >
		friend bool
		operator<(
			ft::stack<U,Cont> const& __lhs,
			ft::stack<U,Cont> const& __rhs );
	};

	template< class U, class Cont >
	bool
	operator==(
		ft::stack<U,Cont> const& __lhs,
		ft::stack<U,Cont> const& __rhs )
	{
		return __lhs.c == __rhs.c;
	}

	template< class U, class Cont >
	bool
	operator!=(
		ft::stack<U,Cont> const& __lhs,
		ft::stack<U,Cont> const& __rhs )
	{
		return !(__lhs == __rhs);
	}

	template< class U, class Cont >
	bool
	operator<(
		ft::stack<U,Cont> const& __lhs,
		ft::stack<U,Cont> const& __rhs )
	{
		return __lhs.c < __rhs.c;
	}

	template< class U, class Cont >
	bool
	operator>(
		ft::stack<U,Cont> const& __lhs,
		ft::stack<U,Cont> const& __rhs )
	{
		return __rhs < __lhs;
	}

	template< class U, class Cont >
	bool
	operator<=(
		ft::stack<U,Cont> const& __lhs,
		ft::stack<U,Cont> const& __rhs )
	{
		return !(__rhs < __lhs);
	}

	template< class U, class Cont >
	bool
	operator>=(
		ft::stack<U,Cont> const& __lhs,
		ft::stack<U,Cont> const& __rhs )
	{
		return !(__lhs < __rhs);
	}
}

#endif
