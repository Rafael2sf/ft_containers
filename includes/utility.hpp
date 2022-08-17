#pragma once

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef	T1	first_type;
		typedef	T2	second_type;

		pair( void ) {};
		pair( pair const & __p ) {*this = __p;}
		pair( T1 const & __x, const T2& __y ): first(__x), second(__y) {}
		pair & operator=( const pair & __rhs ) {
			this->first = __rhs.first;
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
