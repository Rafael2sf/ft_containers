#pragma once

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef	T1	first_type;
		typedef	T2	second_type;

		pair( void ) {};
		pair( pair const & p ) {*this = p;}
		pair( T1 const & x, const T2& y ): first(x), second(y) {}
		pair & operator=( const pair & rhs ) {
			this->first = rhs.first;
			this->second = rhs.second;
			return (*this);
		}
		T1	first;
		T2	second;
	};

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 t, T2 u)
	{
		return (pair<T1, T2>(t, u));
	}
};
