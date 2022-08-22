#pragma once

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef	T1	first_type;
		typedef	T2	second_type;

		pair( void )
		: first(first_type()), second(second_type())
		{};

		template < class U1, class U2>
		pair( pair<U1, U2> const& __other )
		: first(__other.first), second(__other.second)
		{}

		pair( T1 const& __first, T2 const& __second )
		: first(__first), second(__second)
		{}

		pair & operator=( pair const& __rhs ) {
			this->first =  __rhs.first;
			this->second = __rhs.second;
			return (*this);
		}

		T1	first;
		T2	second;
	};

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 __t, T2 __u)
	{
		return (pair<T1, T2>(__t, __u));
	}
};
